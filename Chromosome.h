#ifndef CHROMOSOME_H_INCLUDED
#define CHROMOSOME_H_INCLUDED

class Chromosome {
public:
	double fitness;
	std::vector<std::vector<int> > reels;

	Chromosome(const std::vector<std::vector<int> > &reels, double fitness) {
		Common::copy(this->reels, reels);
		this->fitness = fitness;
	}

	Chromosome(const Chromosome &chromosome) {
		(*this) = chromosome;
	}

	Chromosome() {
		this->fitness = INVALID_FITNESS_VALUE;
	}

	Chromosome& operator=(const Chromosome &chromosome) {
		Common::copy(this->reels, chromosome.reels);
		this->fitness = chromosome.fitness;

		return *this;
	}
};

#endif
