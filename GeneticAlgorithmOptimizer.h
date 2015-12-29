#ifndef GENETICALGORITHMOPTIMIZER_H_INCLUDED
#define GENETICALGORITHMOPTIMIZER_H_INCLUDED

#include "SlotModel.h"

class GeneticAlgorithmOptimizer {
private:
//	static double evaluate(const SlotModel &model, const std::vector<std::vector<int> > &reels) {
//		return( model.execute(reels) );
//	}

	GeneticAlgorithmOptimizer() {
	}

public:
//	static void addRandomReels(GeneticAlgorithm &ga, const SlotModel &model, int populationSize=0) {
//		for(int p=0; p<populationSize; p++) {
//			std::vector<std::vector<int> > reels = random();
//			ga.setChromosome( Chromosome(reels,INVALID_FITNESS_VALUE) );
//			ga.setFitness(evaluate(modle, reels));
//		}
//	}

//	static void optimize(GeneticAlgorithm &ga, const SlotModel &model, std::vector<std::vector<int> > &reels, long epoches=0) {
//		for(long e=0L; e<epoches*ga.size(); e++) {
//			ga.selection();
//			ga.crossover();
//			ga.mutation();
//			int index = ga.getResultIndex();
//			ga.setFitness(evaluate(model, ga.getChromosome(index).reels), index);
//		}
//
//		reels = ga.getChromosome(ga.getBestIndex()).reels;
//	}
};

#endif
