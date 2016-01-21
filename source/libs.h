#ifndef LIBS
#define LIBS

#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <list>

#define DEBUG 0

#if DEBUG == 1
	#define VOUT(x) std::cout << #x << " = " << x << std::endl
#else 
	#define VOUT(x)
#endif

#if DEBUG == 1
	#define SOUT(x) std::cout << x << std::endl
#else 
	#define SOUT(x)
#endif


template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	typename std::vector<T>::const_iterator it;
	for(it = v.begin(); it != (v.end()-1); ++it) {
		os << *it << ", ";
	}
	os << *it;
	return os;
}


#endif
