/*  RAVI WOODS - CACHE SIMULATOR - EE2-13 CWORK 2 - 22/01/2016 */
/*  Includes all libraries used, as well as defining some functions to print debug info */

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

#define DEBUG 0

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
