#ifndef GENETICALGORITHM_H_INCLUDED
#define GENETICALGORITHM_H_INCLUDED

#include "Chromosome.h"

class GeneticAlgorithm {
private:
	std::vector<Chromosome> population;
	int resultIndex;
	int firstIndex;
	int secondIndex;
	int bestIndex;
	int worstIndex;

	void selectRandom() {
		do {
			resultIndex = rand() % population.size();
			firstIndex = rand() % population.size();
			secondIndex = rand() % population.size();
		} while(resultIndex==firstIndex || resultIndex==secondIndex || (resultIndex == bestIndex && KEEP_ELITE==true));
	}

	friend std::ostream& operator<< (std::ostream &out, const GeneticAlgorithm &ga);

public:
	static const bool KEEP_ELITE = true;

public:
	GeneticAlgorithm(int populationSize=0) {
		if(populationSize < 0) {
			populationSize = 0;
		}
		population.resize(populationSize);
		resultIndex = 0;
		firstIndex = 0;
		secondIndex = 0;
		bestIndex = 0;
		worstIndex = 0;
	}

	GeneticAlgorithm(const GeneticAlgorithm &ga) {
		(*this) = ga;
	}

	int getResultIndex() {
		return( resultIndex );
	}

	int getBestIndex() {
		return( bestIndex );
	}

	void setChromosome(Chromosome chromosome, int index=-1) {
		if(index < -1) {
			return;
		}

		if(index == -1) {
			population.push_back( chromosome );
			index = population.size() - 1;
		} else if(index < population.size()) {
			population[index] = chromosome;
		}

		if(population[index].fitness < population[bestIndex].fitness) {
			bestIndex = index;
		}
		if(population[index].fitness > population[worstIndex].fitness) {
			worstIndex = index;
		}
	}

	const Chromosome& getChromosome(int index) const {
		if(population.size() <= index || index <= -1) {
			//TODO Handle exception.
		}

		return( population[index] );
	}

	const Chromosome& getBestChromosome() const {
		return( population[bestIndex] );
	}

	const Chromosome& getRandomChromosome() const {
		return( population[rand()%population.size()] );
	}

	const Chromosome& getWorstChromosome() const {
		return( population[worstIndex] );
	}

	void replaceWorst(const Chromosome& chromosome) {
		population[worstIndex] = chromosome;

		bestIndex = 0;
		worstIndex = 0;
		for(int i=0; i<population.size(); i++) {
			if(population[i].fitness < population[bestIndex].fitness) {
				bestIndex = i;
			}
			if(population[i].fitness > population[worstIndex].fitness) {
				worstIndex = i;
			}
		}
	}

	void setFitness(double fitness, int index=-1) {
		if(index == -1) {
			index = population.size()-1;
		}

		if(population.size() <= index) {
			//TODO Handle exception.
			return;
		}

		population[index].fitness = fitness;
		if(fitness < population[bestIndex].fitness) {
			bestIndex = index;
		}
		if(fitness > population[worstIndex].fitness) {
			worstIndex = index;
		}
	}

	double getFitness(int index) {
		if(population.size() <= index || index <= -1) {
			//TODO Handle exception.
			return( INVALID_FITNESS_VALUE );
		}

		return( population[index].fitness );
	}

	double getBestFitness() const {
		return( population[bestIndex].fitness );
	}

	int size() {
		return( population.size() );
	}

	void subset(GeneticAlgorithm &ga, const int size) const {
		if(population.size() <= 0) {
			return;
		}

		for(int i=0; i<size; i++) {
			ga.setChromosome( population[ rand()%population.size() ] );
		}
	}

	void selection() {
		static const int CROSSOVER_RESULT_INTO_BEST_PERCENT = 1;
		static const int CROSSOVER_RESULT_INTO_MIDDLE_PERCENT = 9;
		static const int CROSSOVER_RESULT_INTO_WORST_PERCENT = 90;

		static int percent = -1;
		percent = rand()
				  % (CROSSOVER_RESULT_INTO_WORST_PERCENT
					 + CROSSOVER_RESULT_INTO_MIDDLE_PERCENT
					 + CROSSOVER_RESULT_INTO_BEST_PERCENT);

		if (percent < CROSSOVER_RESULT_INTO_WORST_PERCENT) {
			do {
				selectRandom();
			} while (population[resultIndex].fitness < population[firstIndex].fitness
					 || population[resultIndex].fitness < population[secondIndex].fitness);
		} else if (percent
				   < (CROSSOVER_RESULT_INTO_WORST_PERCENT
					  + CROSSOVER_RESULT_INTO_MIDDLE_PERCENT)) {
			do {
				selectRandom();
			} while (population[resultIndex].fitness < population[firstIndex].fitness
					 || population[resultIndex].fitness > population[secondIndex].fitness);
		} else if (percent
				   < (CROSSOVER_RESULT_INTO_WORST_PERCENT
					  + CROSSOVER_RESULT_INTO_MIDDLE_PERCENT
					  + CROSSOVER_RESULT_INTO_BEST_PERCENT)) {
			do {
				selectRandom();
			} while (population[resultIndex].fitness > population[firstIndex].fitness
					 || population[resultIndex].fitness > population[secondIndex].fitness);
		}
	}

	void crossover() {
		std::vector<std::vector<int> > &a = population[firstIndex].reels;
		std::vector<std::vector<int> > &b = population[secondIndex].reels;
		std::vector<std::vector<int> > &c = population[resultIndex].reels;

		for(int i=0; i<a.size() && i<b.size() && i<c.size(); i++) {
			for(int j=0; j<a[i].size() && j<b[i].size() && i<c[i].size(); j++) {
				if(rand() % 2 == 0) {
					c[i][j] = a[i][j];
				} else {
					c[i][j] = b[i][j];
				}
			}
		}

		population[resultIndex].fitness = INVALID_FITNESS_VALUE;
	}

	void mutation() {
		int index = rand() % population.size();
		int i = rand() % population[resultIndex].reels.size();
		int j = rand() % population[resultIndex].reels[i].size();

		population[resultIndex].reels[i][j] = population[index].reels[i][j];

		population[resultIndex].fitness = INVALID_FITNESS_VALUE;
	}

	const std::string& toString() {
		static std::string result;
		result = "";

		/*
		 * Keep population size.
		 */
		result += std::to_string(population.size());
		result += " ";

		for(int p=0; p<population.size(); p++) {
			result += std::to_string(population[p].fitness);
			result += " ";

			result += std::to_string(population[p].reels.size());
			result += " ";

			for(int i=0; i<population[p].reels.size(); i++) {
				result +=std::to_string( population[p].reels[i].size());
				result += " ";

				for(int j=0; j<population[p].reels[i].size(); j++) {
					result += std::to_string(population[p].reels[i][j]);
					result += " ";
				}
			}

			result += " ";
		}

		/*
		 * Trim spaces.
		 */
		result.erase(result.size()-1, 1);
		result += '\0';

		return result;
	}

	void fromString(const char text[]) {
		std::string buffer(text);
		std::istringstream in(buffer);

		population.clear();
		bestIndex = 0;
		worstIndex = 0;

		int size = 0;
		in >> size;

		for(int p=0; p<size; p++) {
			double fitness;
			in >> fitness;

			int width, height;
			std::vector<std::vector<int> > reels;

			in >> width;
			reels.resize(width);

			for(int i=0; i<width; i++) {
				in >> height;
				reels[i].resize(height);

				for(int j=0; j<height; j++) {
					in >> reels[i][j];
				}
			}

			setChromosome(Chromosome(reels,fitness));

			if(population[bestIndex].fitness > population[p].fitness) {
				bestIndex = p;
			}
			if(population[worstIndex].fitness < population[p].fitness) {
				worstIndex = p;
			}
		}
	}

	void operator=(const GeneticAlgorithm &ga) {
		this->population.clear();

		this->population = ga.population;
		this->resultIndex = ga.resultIndex;
		this->firstIndex = ga.firstIndex;
		this->secondIndex = ga.secondIndex;
		this->bestIndex = ga.bestIndex;
		this->worstIndex = ga.worstIndex;
	}
};

std::ostream& operator<< (std::ostream &out, const GeneticAlgorithm &ga) {
	for(int p=0; p<ga.population.size(); p++) {
		out << ga.population[p].fitness;
		out << std::endl;
		for(int i=0; i<ga.population[p].reels.size(); i++) {
			for(int j=0; j<ga.population[p].reels[i].size(); j++) {
				out << ga.population[p].reels[i][j];
				out << " ";
			}
			out << std::endl;
		}
		out << std::endl;
	}

	return out;
}

#endif
