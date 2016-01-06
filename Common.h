#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

namespace std {
template < typename T > std::string to_string( const T& n ) {
	std::ostringstream stm;
	stm << n ;
	return stm.str() ;
}
}

class Common {
public:
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
};

#endif
