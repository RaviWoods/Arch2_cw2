/*  RAVI WOODS - CACHE SIMULATOR - EE2-13 CWORK 2 - 22/01/2016 */
/*  Defines classes used in the project, as well as useful typedefs on those classes */

#ifndef MYCLASSES_HPP
#define MYCLASSES_HPP

#include "mem_sim_libs.hpp"


class Parameters {

	public:
		Parameters(const char * parameters[]) {
				addressLength = atoi(parameters[1]);
				bytePerWord	= atoi(parameters[2] );
				wordPerBlock	= atoi(parameters[3]);
				blockPerSet	= atoi(parameters[4]);
				setPerCache	= atoi(parameters[5]);
				hitTime 	= atoi(parameters[6]);
				readTime	= atoi(parameters[7]);
				writeTime	= atoi(parameters[8]);
		}

		unsigned addressLength;
		unsigned bytePerWord;
		unsigned wordPerBlock;
		unsigned blockPerSet;
		unsigned setPerCache;
		unsigned hitTime;
		unsigned readTime;
		unsigned writeTime;
};

class Block {
	public:
		Block() {};
		Block(unsigned bAddressIn, bool dirtyBitIn) : bAddress(bAddressIn), dirtyBit(dirtyBitIn) {};
		unsigned bAddress;
		bool dirtyBit;
		friend std::ostream& operator<< (std::ostream & out, Block const& data) {
    		out << "B" << data.bAddress << " dirtyBit = " << data.dirtyBit << std::endl;
		}
};

typedef std::map<long, std::string> DataStructure;
typedef std::vector< std::list<Block>> CacheStructure;

#endif
