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

static void master1() {
	unsigned long counter = 0;

	if(rank != ROOT_NODE) {
		return;
	}

	/*
	 * Send ... to all other nodes.
	 */{
//		const std::string &value = .toString();
		for(int r=0; r<size; r++) {
			/*
			 * Root node is not included.
			 */
			if(r == ROOT_NODE) {
				continue;
			}

//			MPI_Send(value.c_str(), value.size(), MPI_BYTE, r, DEFAULT_TAG, MPI_COMM_WORLD);
		}
	}

	std::map<int,GeneticAlgorithm> populations;
	do {
		std::cout << "Round : " << (counter+1) << std::endl;

		/*
		 * Send GA population to all other nodes.
		 */
		for(int r=0; r<size; r++) {
			/*
			 * Root node is not included.
			 */
			if(r == ROOT_NODE) {
				continue;
			}

			GeneticAlgorithm ga;
			if(counter == 0) {
//				GeneticAlgorithmOptimizer::addRandomReels(ga, , , LOCAL_POPULATION_SIZE);
				populations[r] = ga;
			} else {
				/*
				 * Ring migration strategy.
				 */
				int next = (r+1) % size;
				while(next == ROOT_NODE) {
					next = (next+1) % size;
				}

				if(RANDOM_TRAVELER == true) {
					populations[r].replaceWorst(populations[next].getRandomChromosome());
				} else {
					populations[r].replaceWorst(populations[next].getBestChromosome());
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
			std::cout << "Worker " << r << " : " << ga.getBestChromosome().fitness << std::endl;
		}

		counter++;
	} while(counter < NUMBER_OF_BROADCASTS);
}

static void master2() {
	unsigned long counter = 0;

	if(rank != ROOT_NODE) {
		return;
	}

	/*
	 * Send ... to all other nodes.
	 */{
//		const std::string &value = .toString();
		for(int r=0; r<size; r++) {
			/*
			 * Root node is not included.
			 */
			if(r == ROOT_NODE) {
				continue;
			}

//			MPI_Send(value.c_str(), value.size(), MPI_BYTE, r, DEFAULT_TAG, MPI_COMM_WORLD);
		}
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
//				GeneticAlgorithmOptimizer::addRandomReels(global, , , LOCAL_POPULATION_SIZE*size);
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

static void slave1() {
	unsigned long counter = 0;

	if(rank == ROOT_NODE) {
		return;
	}

	MPI_Recv(buffer, RECEIVE_BUFFER_SIZE, MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	.fromString(buffer);

	do {
		GeneticAlgorithm ga;
		MPI_Recv(buffer, RECEIVE_BUFFER_SIZE, MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		ga.fromString(buffer);

		/*
		 * Calculate as regular node.
		 */
//		GeneticAlgorithmOptimizer::optimize(ga, , , LOCAL_OPTIMIZATION_EPOCHES);

		std::string result = ga.toString();
		MPI_Send(result.c_str(), result.size(), MPI_BYTE, ROOT_NODE, DEFAULT_TAG, MPI_COMM_WORLD);

		counter++;
	} while(counter < NUMBER_OF_BROADCASTS);
}

static void slave2() {
	slave1();
}

int main(int argc, char **argv) {
	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand( time(NULL)^getpid() );

	/*
	 * Firs process will distribute the working tasks.
	 */
	master1();
	slave1();
	master2();
	slave2();

	MPI_Finalize();

	return( EXIT_SUCCESS );
}
