#ifndef SLOTMODEL_H_INCLUDED
#define SLOTMODEL_H_INCLUDED

class SlotModel {
public:

	std::vector<std::string> symbols;

	std::vector<std::string> types;

	std::vector<std::vector<int> > paytable;

	std::vector<int> multipliers;

	std::vector<std::vector<int> > lines;

private:

	std::vector<std::vector<int> > reels;

	std::vector<int> stops;

	std::vector<int> line;

public:

	SlotModel() {
		if(symbols.size() <= 0) {
			symbols.push_back("EMPTY");
			symbols.push_back("SYM01");
			symbols.push_back("EMPTY");
			symbols.push_back("SYM03");
			symbols.push_back("SYM04");
			symbols.push_back("SYM05");
			symbols.push_back("SYM06");
			symbols.push_back("SYM07");
			symbols.push_back("SYM08");
			symbols.push_back("SYM09");
			symbols.push_back("SYM10");
			symbols.push_back("SYM11");
			symbols.push_back("SYM12");
			symbols.push_back("EMPTY");
			symbols.push_back("EMPTY");
			symbols.push_back("SYM16");
			symbols.push_back("SYM16");
		}

		if(types.size() <= 0) {
			types.push_back("UNUSED");
			types.push_back("WILD");
			types.push_back("UNUSED");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("REGULAR");
			types.push_back("UNUSED");
			types.push_back("UNUSED");
			types.push_back("BONUS");
			types.push_back("SCATTER");
		}

		if(paytable.size() <= 0) {
			paytable.resize(6);

			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);
			paytable[0].push_back(0);

			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);
			paytable[1].push_back(0);

			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(30);
			paytable[2].push_back(20);
			paytable[2].push_back(4);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);
			paytable[2].push_back(0);

			paytable[3].push_back(0);
			paytable[3].push_back(0);
			paytable[3].push_back(0);
			paytable[3].push_back(150);
			paytable[3].push_back(75);
			paytable[3].push_back(50);
			paytable[3].push_back(40);
			paytable[3].push_back(5);
			paytable[3].push_back(4);
			paytable[3].push_back(4);
			paytable[3].push_back(3);
			paytable[3].push_back(3);
			paytable[3].push_back(2);
			paytable[3].push_back(0);
			paytable[3].push_back(0);
			paytable[3].push_back(0);
			paytable[3].push_back(0);

			paytable[4].push_back(0);
			paytable[4].push_back(0);
			paytable[4].push_back(0);
			paytable[4].push_back(250);
			paytable[4].push_back(100);
			paytable[4].push_back(100);
			paytable[4].push_back(75);
			paytable[4].push_back(50);
			paytable[4].push_back(40);
			paytable[4].push_back(20);
			paytable[4].push_back(6);
			paytable[4].push_back(5);
			paytable[4].push_back(4);
			paytable[4].push_back(0);
			paytable[4].push_back(0);
			paytable[4].push_back(0);
			paytable[4].push_back(0);

			paytable[5].push_back(0);
			paytable[5].push_back(0);
			paytable[5].push_back(0);
			paytable[5].push_back(500);
			paytable[5].push_back(250);
			paytable[5].push_back(175);
			paytable[5].push_back(150);
			paytable[5].push_back(100);
			paytable[5].push_back(50);
			paytable[5].push_back(30);
			paytable[5].push_back(25);
			paytable[5].push_back(15);
			paytable[5].push_back(10);
			paytable[5].push_back(0);
			paytable[5].push_back(0);
			paytable[5].push_back(0);
			paytable[5].push_back(0);
		}

		if(multipliers.size() <= 0) {
			multipliers.push_back(0);
			multipliers.push_back(0);
			multipliers.push_back(0);
			multipliers.push_back(1);
			multipliers.push_back(2);
			multipliers.push_back(3);
		}

		if(lines.size() <= 0) {
			lines.resize(50);

			lines[0].push_back(1);
			lines[0].push_back(1);
			lines[0].push_back(1);
			lines[0].push_back(1);
			lines[0].push_back(1);
			lines[1].push_back(0);
			lines[1].push_back(0);
			lines[1].push_back(0);
			lines[1].push_back(0);
			lines[1].push_back(0);
			lines[2].push_back(2);
			lines[2].push_back(2);
			lines[2].push_back(2);
			lines[2].push_back(2);
			lines[2].push_back(2);
			lines[3].push_back(0);
			lines[3].push_back(1);
			lines[3].push_back(2);
			lines[3].push_back(1);
			lines[3].push_back(0);
			lines[4].push_back(2);
			lines[4].push_back(1);
			lines[4].push_back(0);
			lines[4].push_back(1);
			lines[4].push_back(2);
			lines[5].push_back(0);
			lines[5].push_back(0);
			lines[5].push_back(1);
			lines[5].push_back(2);
			lines[5].push_back(2);
			lines[6].push_back(2);
			lines[6].push_back(2);
			lines[6].push_back(1);
			lines[6].push_back(0);
			lines[6].push_back(0);
			lines[7].push_back(1);
			lines[7].push_back(0);
			lines[7].push_back(1);
			lines[7].push_back(2);
			lines[7].push_back(1);
			lines[8].push_back(1);
			lines[8].push_back(2);
			lines[8].push_back(1);
			lines[8].push_back(0);
			lines[8].push_back(1);
			lines[9].push_back(0);
			lines[9].push_back(1);
			lines[9].push_back(1);
			lines[9].push_back(1);
			lines[9].push_back(2);
			lines[10].push_back(2);
			lines[10].push_back(1);
			lines[10].push_back(1);
			lines[10].push_back(1);
			lines[10].push_back(0);
			lines[11].push_back(1);
			lines[11].push_back(0);
			lines[11].push_back(0);
			lines[11].push_back(1);
			lines[11].push_back(2);
			lines[12].push_back(1);
			lines[12].push_back(2);
			lines[12].push_back(2);
			lines[12].push_back(1);
			lines[12].push_back(0);
			lines[13].push_back(1);
			lines[13].push_back(1);
			lines[13].push_back(0);
			lines[13].push_back(1);
			lines[13].push_back(2);
			lines[14].push_back(1);
			lines[14].push_back(1);
			lines[14].push_back(2);
			lines[14].push_back(1);
			lines[14].push_back(0);
			lines[15].push_back(0);
			lines[15].push_back(1);
			lines[15].push_back(0);
			lines[15].push_back(1);
			lines[15].push_back(2);
			lines[16].push_back(2);
			lines[16].push_back(1);
			lines[16].push_back(2);
			lines[16].push_back(1);
			lines[16].push_back(0);
			lines[17].push_back(2);
			lines[17].push_back(1);
			lines[17].push_back(0);
			lines[17].push_back(0);
			lines[17].push_back(1);
			lines[18].push_back(0);
			lines[18].push_back(1);
			lines[18].push_back(2);
			lines[18].push_back(2);
			lines[18].push_back(1);
			lines[19].push_back(0);
			lines[19].push_back(1);
			lines[19].push_back(1);
			lines[19].push_back(2);
			lines[19].push_back(1);
			lines[20].push_back(0);
			lines[20].push_back(1);
			lines[20].push_back(0);
			lines[20].push_back(1);
			lines[20].push_back(0);
			lines[21].push_back(2);
			lines[21].push_back(1);
			lines[21].push_back(2);
			lines[21].push_back(1);
			lines[21].push_back(2);
			lines[22].push_back(0);
			lines[22].push_back(2);
			lines[22].push_back(0);
			lines[22].push_back(2);
			lines[22].push_back(0);
			lines[23].push_back(2);
			lines[23].push_back(0);
			lines[23].push_back(2);
			lines[23].push_back(0);
			lines[23].push_back(2);
			lines[24].push_back(0);
			lines[24].push_back(0);
			lines[24].push_back(2);
			lines[24].push_back(0);
			lines[24].push_back(0);
			lines[25].push_back(2);
			lines[25].push_back(2);
			lines[25].push_back(0);
			lines[25].push_back(2);
			lines[25].push_back(2);
			lines[26].push_back(0);
			lines[26].push_back(2);
			lines[26].push_back(2);
			lines[26].push_back(2);
			lines[26].push_back(0);
			lines[27].push_back(2);
			lines[27].push_back(0);
			lines[27].push_back(0);
			lines[27].push_back(0);
			lines[27].push_back(2);
			lines[28].push_back(1);
			lines[28].push_back(0);
			lines[28].push_back(2);
			lines[28].push_back(0);
			lines[28].push_back(1);
			lines[29].push_back(1);
			lines[29].push_back(2);
			lines[29].push_back(0);
			lines[29].push_back(2);
			lines[29].push_back(1);
			lines[30].push_back(0);
			lines[30].push_back(0);
			lines[30].push_back(0);
			lines[30].push_back(1);
			lines[30].push_back(2);
			lines[31].push_back(2);
			lines[31].push_back(2);
			lines[31].push_back(2);
			lines[31].push_back(1);
			lines[31].push_back(0);
			lines[32].push_back(2);
			lines[32].push_back(0);
			lines[32].push_back(1);
			lines[32].push_back(0);
			lines[32].push_back(2);
			lines[33].push_back(0);
			lines[33].push_back(2);
			lines[33].push_back(1);
			lines[33].push_back(2);
			lines[33].push_back(0);
			lines[34].push_back(1);
			lines[34].push_back(2);
			lines[34].push_back(1);
			lines[34].push_back(2);
			lines[34].push_back(1);
			lines[35].push_back(1);
			lines[35].push_back(0);
			lines[35].push_back(1);
			lines[35].push_back(0);
			lines[35].push_back(1);
			lines[36].push_back(0);
			lines[36].push_back(0);
			lines[36].push_back(0);
			lines[36].push_back(2);
			lines[36].push_back(2);
			lines[37].push_back(2);
			lines[37].push_back(2);
			lines[37].push_back(2);
			lines[37].push_back(0);
			lines[37].push_back(0);
			lines[38].push_back(0);
			lines[38].push_back(1);
			lines[38].push_back(1);
			lines[38].push_back(1);
			lines[38].push_back(0);
			lines[39].push_back(2);
			lines[39].push_back(1);
			lines[39].push_back(1);
			lines[39].push_back(1);
			lines[39].push_back(2);
			lines[40].push_back(1);
			lines[40].push_back(2);
			lines[40].push_back(2);
			lines[40].push_back(2);
			lines[40].push_back(1);
			lines[41].push_back(1);
			lines[41].push_back(0);
			lines[41].push_back(0);
			lines[41].push_back(0);
			lines[41].push_back(1);
			lines[42].push_back(0);
			lines[42].push_back(0);
			lines[42].push_back(2);
			lines[42].push_back(2);
			lines[42].push_back(2);
			lines[43].push_back(2);
			lines[43].push_back(2);
			lines[43].push_back(0);
			lines[43].push_back(0);
			lines[43].push_back(0);
			lines[44].push_back(1);
			lines[44].push_back(1);
			lines[44].push_back(0);
			lines[44].push_back(1);
			lines[44].push_back(1);
			lines[45].push_back(1);
			lines[45].push_back(1);
			lines[45].push_back(2);
			lines[45].push_back(1);
			lines[45].push_back(1);
			lines[46].push_back(2);
			lines[46].push_back(0);
			lines[46].push_back(1);
			lines[46].push_back(0);
			lines[46].push_back(1);
			lines[47].push_back(0);
			lines[47].push_back(2);
			lines[47].push_back(1);
			lines[47].push_back(2);
			lines[47].push_back(1);
			lines[48].push_back(1);
			lines[48].push_back(0);
			lines[48].push_back(2);
			lines[48].push_back(2);
			lines[48].push_back(0);
			lines[49].push_back(1);
			lines[49].push_back(2);
			lines[49].push_back(0);
			lines[49].push_back(0);
			lines[49].push_back(2);
		}
	}

	void load(const std::vector<std::vector<int> > &values) {
		reels.clear();

		reels.resize( values.size() );
		for(int i=0; i<values.size(); i++) {
			for(int j=0; j<values[i].size(); i++) {
				reels[i].push_back( values[i][j] );
			}
		}
	}

	long combinations() {
		unsigned long result = 1;

		for(int i=0; i<reels.size(); i++) {
			result *= reels[i].size();
		}

		return result;
	}

	void init() {
		/*
		 * Initialize stops of the reels in the beginning.
		 */
		stops.clear();
		for(int i=0; i<reels.size(); i++) {
			stops.push_back(0);
		}

		line.clear();
		for(int i=0; i<reels.size(); i++) {
			line.push_back( reels[i][stops[i]] );
		}
	}

	void next() {
		stops[reels.size()-1] += 1;

		for(int i=reels.size()-1; i>0; i--) {
			if(stops[i] >= reels[i].size()) {
				stops[i] = 0;
				stops[i-1] += 1;
			}
		}

		if(stops[0] >= reels[0].size()) {
			stops[0] = 0;
		}

		line.clear();
		for(int i=0; i<reels.size(); i++) {
			line.push_back( reels[i][stops[i]] );
		}
	}

	int win() {
		int symbol = line[0];

		for (int i=0; i<line.size(); i++) {
			if(symbol != 1) {
				break;
			}

			symbol = line [i];
		}

        for (int i = 0; i<line.size(); i++) {
            if (line[i] == 1) {
                line[i] = symbol;
            }
        }

        int counter = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == symbol) {
                counter++;
            } else {
                break;
            }
        }

        return paytable[counter][symbol];
	}

	int scatters() {
		int counter = 0;

		for(int i=0; i<reels.size(); i++) {
			for(int j=0; j<ROWS_SIZE; j++) {
				if(reels[i][(stops[i]+j)%reels[i].size()] == 16) {
					counter++;
				}
			}
		}

		return counter;
	}

	int bonus() {
		int counter = 0;

		for(int i=0; i<reels.size(); i++) {
			for(int j=0; j<ROWS_SIZE; j++) {
				if(reels[i][(stops[i]+j)%reels[i].size()] == 15) {
					counter++;
				}
			}
		}

		return counter;
	}

	void calculate(std::vector<double> &result) {
		result.clear();
		result.resize(7);

		/*
		 * RTP.
		 */
		result[0] = 0;

		/*
		 * Free games frequency (scatters as activator).
		 * Activation can be from 3, 4 or 5 scatters.
		 */
		result[1] = 0;
		result[2] = 0;
		result[3] = 0;

		/*
		 * Bonus game frequency (bonus symbols as activator).
		 * Activation can be from 3, 4 or 5 bonus symbols.
		 */
		result[4] = 0;
		result[5] = 0;
		result[6] = 0;

		/*
		 * Check all possible combinations.
		 */
		for(long g=combinations()-1; g>=0; g--) {
			result[0] += win();

			/*
			 * Scatters have win equal to bet by scatter multiplier.
			 */
			switch(scatters()) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				result[1] += 1;
				result[0] += multipliers[3];
				break;
			case 4:
				result[2] += 1;
				result[0] += multipliers[4];
				break;
			case 5:
				result[3] += 1;
				result[0] += multipliers[5];
				break;
			default:
				//std::cerr<<"More than 5 scatters!"<<std::endl;
				result[0] += INVALID_REELS_PENALTY;
				break;
			}

			switch(bonus()) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				result[4] += 1;
				break;
			case 4:
				result[5] += 1;
				break;
			case 5:
				result[6] += 1;
				break;
			default:
				//std::cerr<<"More than 5 bonus symbols!"<<std::endl;
				result[0] += INVALID_REELS_PENALTY;
				break;
			}

			next();
		}

		for(int i=0; i<result.size(); i++) {
			result[i] /= combinations();
		}
	}
};

#endif
