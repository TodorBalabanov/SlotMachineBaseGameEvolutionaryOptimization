#ifndef CHROMOSOME_H_INCLUDED
#define CHROMOSOME_H_INCLUDED

class Chromosome {
public:
	double fitness;
	std::vector<std::vector<int> > reels;

	Chromosome(const std::vector<std::vector<int> > &reels, double fitness) {
		this->reels = reels;
		this->fitness = fitness;
	}

	Chromosome(const Chromosome &chromosome) {
		(*this) = chromosome;
	}

	Chromosome() {
		this->fitness = INVALID_FITNESS_VALUE;
	}

	void operator=(const Chromosome &chromosome) {
		this->reels = chromosome.reels;
		this->fitness = chromosome.fitness;
	}
};

#endif
