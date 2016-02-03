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
			std::cerr << rank << " Test point 1 ..." << std::endl;
			/*
			 * Root node is not included.
			 */
			if(r == ROOT_NODE) {
				continue;
			}
			std::cerr << rank << " Test point 2 ..." << std::endl;

			if(counter == 0) {
				std::cerr << rank << " Test point 3 ..." << std::endl;
				GeneticAlgorithmOptimizer::addRandomReels(global, model, targets
						, LOCAL_POPULATION_SIZE*size);
				std::cerr << rank << " Test point 4 ..." << std::endl;
				GeneticAlgorithm ga;
				std::cerr << rank << " Test point 5 ..." << std::endl;
				global.subset(ga, LOCAL_POPULATION_SIZE);
				std::cerr << rank << " Test point 6 ..." << std::endl;
				populations[r] = ga;
				std::cerr << rank << " Test point 7 ..." << std::endl;
			} else {
				//TODO Find better way to control this probability.
				std::cerr << rank << " Test point 8 ..." << std::endl;
				if(rand()%(NUMBER_OF_BROADCASTS/10) == 0) {
					std::cerr << rank << " Test point 9 ..." << std::endl;
					GeneticAlgorithm ga;
					std::cerr << rank << " Test point 10 ..." << std::endl;
					global.subset(ga, LOCAL_POPULATION_SIZE);
					std::cerr << rank << " Test point 11 ..." << std::endl;
					populations[r] = ga;
					std::cerr << rank << " Test point 12 ..." << std::endl;
				}
				std::cerr << rank << " Test point 13 ..." << std::endl;
			}
			std::cerr << rank << " Test point 14 ..." << std::endl;
			const std::string &value = populations[r].toString();
			std::cerr << rank << " Test point 15 ..." << std::endl;
			MPI_Send(value.c_str(), value.size(), MPI_BYTE, r, DEFAULT_TAG, MPI_COMM_WORLD);
			std::cerr << rank << " Test point 16 ..." << std::endl;
		}
		std::cerr << rank << " Test point 17 ..." << std::endl;

		/*
		 * Collect results from all other nodes.
		 */
		std::cerr << rank << " Test point 18 ..." << std::endl;
		for(int r=0; r<size; r++) {
			std::cerr << rank << " Test point 19 ..." << std::endl;
			/*
			 * Root node is not included.
			 */
			std::cerr << rank << " Test point 20 ..." << std::endl;
			if(r == ROOT_NODE) {
				continue;
			}
			std::cerr << rank << " Test point 21 ..." << std::endl;

			GeneticAlgorithm ga;
			std::cerr << rank << " Test point 22 ..." << std::endl;
			MPI_Recv(buffer, RECEIVE_BUFFER_SIZE, MPI_BYTE, r, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::cerr << rank << " Test point 23 ..." << std::endl;
			ga.fromString(buffer);
			std::cerr << rank << " Test point 24 ..." << std::endl;
			populations[r] = ga;
			std::cerr << rank << " Test point 25 ..." << std::endl;
			if(ga.getBestFitness() < global.getBestFitness()) {
				std::cerr << rank << " Test point 26 ..." << std::endl;
				global.setChromosome( ga.getBestChromosome() );
			}
			std::cerr << rank << " Test point 27 ..." << std::endl;
			std::cout << "Worker " << r << " : " << ga.getBestChromosome().fitness << std::endl;
		}
		std::cerr << rank << " Test point 28 ..." << std::endl;

		std::cout << "Global : " << global.getBestChromosome().fitness << std::endl;

		counter++;
		std::cerr << rank << " Test point 29 ..." << std::endl;
	} while(counter < NUMBER_OF_BROADCASTS);
	std::cerr << rank << " Test point 30 ..." << std::endl;
}

static void slave() {
	unsigned long counter = 0;

	if(rank == ROOT_NODE) {
		return;
	}

	std::cerr << rank << " Test point 31 ..." << std::endl;
	do {
		std::cerr << rank << " Test point 32 ..." << std::endl;
		GeneticAlgorithm ga;
		std::cerr << rank << " Test point 33 ..." << std::endl;
		MPI_Recv(buffer, RECEIVE_BUFFER_SIZE, MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cerr << rank << " Test point 34 ..." << std::endl;
		ga.fromString(buffer);

		/*
		 * Calculate as regular node.
		 */
		std::cerr << rank << " Test point 35 ..." << std::endl;
		std::cerr << rank << ga << std::endl;
		std::cerr << rank << model << std::endl;
		//std::cerr << rank << targets << std::endl;
		GeneticAlgorithmOptimizer::optimize(ga, model, targets, LOCAL_OPTIMIZATION_EPOCHES);

		std::cerr << rank << " Test point 36 ..." << std::endl;
		std::string result = ga.toString();
		std::cerr << rank << " Test point 37 ..." << std::endl;
		MPI_Send(result.c_str(), result.size(), MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD);

		std::cerr << rank << " Test point 38 ..." << std::endl;
		counter++;
		std::cerr << rank << " Test point 39 ..." << std::endl;
	} while(counter < NUMBER_OF_BROADCASTS);
	std::cerr << rank << " Test point 40 ..." << std::endl;
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
