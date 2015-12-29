#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

namespace std {
template < typename T > std::string to_string( const T& n ) {
	std::ostringstream stm;
	stm << n ;
	return stm.str() ;
}
}

#endif
