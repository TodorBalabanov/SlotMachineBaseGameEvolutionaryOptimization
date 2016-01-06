#ifndef CHROMOSOME_H_INCLUDED
#define CHROMOSOME_H_INCLUDED

class Chromosome {
private:

	static void copy(std::vector<std::vector<int> > &a, const std::vector<std::vector<int> > &b) {
		a.clear();

		a.resize(b.size());
		for(int i=0; i<a.size(); i++) {
			a[i].resize( b[i].size() );

			for(int j=0; j<a[i].size(); j++) {
				a[i][j] = b[i][j];
			}
		}
	}

public:
	double fitness;
	std::vector<std::vector<int> > reels;

	Chromosome(const std::vector<std::vector<int> > &reels, double fitness) {
		copy(this->reels, reels);
		this->fitness = fitness;
	}

	Chromosome(const Chromosome &chromosome) {
		(*this) = chromosome;
	}

	Chromosome() {
		this->fitness = INVALID_FITNESS_VALUE;
	}

	Chromosome& operator=(const Chromosome &chromosome) {
		copy(this->reels, chromosome.reels);
		this->fitness = chromosome.fitness;

		return *this;
	}
};

#endif
