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
#include <map>
#include <list>

#define DEBUG 1

#if DEBUG == 1
	#define VOUT(x) std::cerr << #x << " = " << x << std::endl
#else 
	#define VOUT(x)
#endif

#if DEBUG == 1
	#define SOUT(x) std::cerr << x << std::endl
#else 
	#define SOUT(x)
#endif

#endif
