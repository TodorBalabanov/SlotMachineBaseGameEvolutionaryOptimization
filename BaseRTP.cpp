#include <map>
#include <cmath>
#include <vector>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <sstream>
#include <iostream>

#include <mpi.h>
#include <unistd.h>

#include "Common.h"
#include "Constants.h"
#include "GeneticAlgorithm.h"
#include "GeneticAlgorithmOptimizer.h"

static int rank = -1;
static int size = 0;

/*
 * Receive buffer.
 */
static char buffer[RECEIVE_BUFFER_SIZE];

static std::vector<double> targets;

static SlotModel model;

static void master() {
	unsigned long counter = 0;

	if(rank != ROOT_NODE) {
		return;
	}

	GeneticAlgorithm global;
	std::map<int,GeneticAlgorithm> populations;
	do {
		std::cout << "Round : " << (counter+1) << std::endl;

		for(int r=0; r<size; r++) {
			/*
			 * Root node is not included.
			 */
			if(r == ROOT_NODE) {
				continue;
			}

			if(counter == 0) {
				GeneticAlgorithmOptimizer::addRandomReels(global, model, targets
						, LOCAL_POPULATION_SIZE*size);
				GeneticAlgorithm ga;
				global.subset(ga, LOCAL_POPULATION_SIZE);
				populations[r] = ga;
			} else {
				//TODO Find better way to control this probability.
				if(rand()%(NUMBER_OF_BROADCASTS/10) == 0) {
					GeneticAlgorithm ga;
					global.subset(ga, LOCAL_POPULATION_SIZE);
					populations[r] = ga;
				}
			}
			const std::string &value = populations[r].toString();
			MPI_Send(value.c_str(), value.size(), MPI_BYTE, r, DEFAULT_TAG, MPI_COMM_WORLD);
		}

		/*
		 * Collect results from all other nodes.
		 */
		for(int r=0; r<size; r++) {
			/*
			 * Root node is not included.
			 */
			if(r == ROOT_NODE) {
				continue;
			}

			GeneticAlgorithm ga;
			MPI_Recv(buffer, RECEIVE_BUFFER_SIZE, MPI_BYTE, r, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			ga.fromString(buffer);
			populations[r] = ga;
			if(ga.getBestFitness() < global.getBestFitness()) {
				global.setChromosome( ga.getBestChromosome() );
			}
			std::cout << "Worker " << r << " : " << ga.getBestChromosome().fitness << std::endl;
		}

		std::cout << "Global : " << global.getBestChromosome().fitness << std::endl;


		counter++;
	} while(counter < NUMBER_OF_BROADCASTS);
}

static void slave() {
	unsigned long counter = 0;

	if(rank == ROOT_NODE) {
		return;
	}

	do {
		GeneticAlgorithm ga;
		MPI_Recv(buffer, RECEIVE_BUFFER_SIZE, MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		ga.fromString(buffer);

		/*
		 * Calculate as regular node.
		 */
		GeneticAlgorithmOptimizer::optimize(ga, model, targets, LOCAL_OPTIMIZATION_EPOCHES);

		std::string result = ga.toString();
		MPI_Send(result.c_str(), result.size(), MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD);

		counter++;
	} while(counter < NUMBER_OF_BROADCASTS);
}

int main(int argc, char **argv) {
	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand( time(NULL)^getpid() );

	targets.push_back(0.65);
	targets.push_back(0.09);
	targets.push_back(0.03);
	targets.push_back(0.01);
	targets.push_back(0.08);
	targets.push_back(0.04);
	targets.push_back(0.01);

	/*
	 * Firs process will distribute the working tasks.
	 */
	master();
	slave();

	MPI_Finalize();

	return( EXIT_SUCCESS );
}
