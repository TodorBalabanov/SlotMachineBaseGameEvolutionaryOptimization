#ifndef GENETICALGORITHMOPTIMIZER_H_INCLUDED
#define GENETICALGORITHMOPTIMIZER_H_INCLUDED

#include "SlotModel.h"

class GeneticAlgorithmOptimizer {
private:
	static double evaluate(SlotModel &model, const std::vector<double> &targets, const std::vector<std::vector<int> > &reels) {
		std::vector<double> parameters;

		model.load(reels);
		model.init();
		model.calculate(parameters);

		double sum = 0.0;
		for(int i=0; i<targets.size() && i<parameters.size(); i++) {
			sum += (targets[i]-parameters[i]) * (targets[i]-parameters[i]);
		}

		return sum;
	}

	GeneticAlgorithmOptimizer() {
	}

public:
	static void addRandomReels(GeneticAlgorithm &ga, SlotModel &model, const std::vector<double> &targets, int populationSize=0) {
		for(int p=0; p<populationSize; p++) {
			std::vector<std::vector<int> > reels;
			reels.resize(REELS_SIZE);
			for(int i=0, value; i<reels.size(); i++) {
				for(int j=0; j<REEL_SIZE; j++) {
					do {
						value = rand() % model.symbols.size();
					} while(model.symbols[value] == "EMPTY");

					reels[i].push_back(value);
				}
			}

			ga.setChromosome( Chromosome(reels,INVALID_FITNESS_VALUE) );
			ga.setFitness(evaluate(model, targets, reels));
		}
	}

	static void optimize(GeneticAlgorithm &ga, SlotModel &model, const std::vector<double> &targets, long epoches=0) {
		for(long e=0L; e<epoches*ga.size(); e++) {
			ga.selection();
			ga.crossover();
			ga.mutation();
			int index = ga.getResultIndex();
			ga.setFitness(evaluate(model, targets, ga.getChromosome(index).reels), index);
		}
	}
};

#endif
