/*  RAVI WOODS - CACHE SIMULATOR - EE2-13 CWORK 2 - 22/01/2016 */
/*  Source file for defining instruction functions */

#include "mem_sim_libs.hpp"
#include "mem_sim_functions.hpp"
#include "mem_sim_classes.hpp"
using namespace std;

string flushCommand (CacheStructure& cacheVect, const Parameters& P) {

	int accessTime = 0;
	for (CacheStructure::iterator v_it = cacheVect.begin() ; v_it != cacheVect.end(); ++v_it) {
		for(list<Block>::iterator l_it = v_it->begin(); l_it != v_it->end(); ++l_it) {
			if(l_it->dirtyBit == 1) {
	 			accessTime += P.writeTime;
				l_it->dirtyBit = 0;
			}
		}
	}

	stringstream ss;
	ss << "flush-ack " << accessTime << endl;
	
	return(ss.str());
}
string debugCommand (CacheStructure& cacheVect, const Parameters& P) {
	stringstream ss;
	ss << "debug-ack-begin" << endl;
	for (CacheStructure::iterator v_it = cacheVect.begin() ; v_it != cacheVect.end(); ++v_it) {
		ss << "Set " << v_it - cacheVect.begin() << ":" << endl << endl;
		bool empty = true;
		for(list<Block>::iterator l_it = v_it->begin(); l_it != v_it->end(); ++l_it) {
			empty = false;
			ss << *l_it << endl;
		}
		if (empty == true) {
			ss << "EMPTY" << endl;
		}
	}
	ss << "debug-ack-end" << endl;
	return(ss.str());
}

string readOrWriteCommand (DataStructure& cacheData, CacheStructure& cacheVect, const Parameters& P, unsigned address, bool write) {
	int accessTime = 0;

	accessTime += P.hitTime;
	
	unsigned currentbAddress = address/(P.bytePerWord*P.wordPerBlock);
	unsigned setIndex = currentbAddress % P.setPerCache;
	bool hit = 0;
	list<Block>::iterator it;
	Block blockToWrite(currentbAddress,write);
	for(it = cacheVect[setIndex].begin(); it != cacheVect[setIndex].end(); ++it) {
		if (it->bAddress == currentbAddress) {
			hit = 1;
			break;
		}
	}
	if (hit == 1) {
		if (it->dirtyBit == 0) {
			it->dirtyBit = write;
		}
		cacheVect[setIndex].splice(cacheVect[setIndex].begin(), cacheVect[setIndex], it);
	} else {
		if (cacheVect[setIndex].size() == P.blockPerSet) {
			--it;
			if(it->dirtyBit == 1) {
				accessTime += P.writeTime;				
			}
			cacheVect[setIndex].erase(it);
		}
		if (!(write == true && P.wordPerBlock == 1)) {
			accessTime += P.readTime;
		}
		
		cacheVect[setIndex].push_front(blockToWrite);
	}
	VOUT(accessTime);


	string outputString;
	if (write) {
		outputString = makeWriteOutput(setIndex,hit,accessTime);
	} else {
		outputString = makeReadOutput(cacheData,address,P,setIndex,hit,accessTime);
	}
	return outputString;

}	

string makeReadOutput(DataStructure& cacheData, unsigned address, const Parameters& P, int setIndex, bool hit, int accessTime) {
	string hitString;
	stringstream ss;
	string data;
	if(hit == 1) {
		hitString = "hit";
	} else {
		hitString = "miss";
	}
	if (cacheData.count(address) == 1) {
		data = cacheData.find(address)->second;
	} else {
		data = "0";
	}
	ss << "read-ack " << setIndex << " " << hitString << " " << accessTime << " " << uppercase << setfill('0') << setw(2*P.bytePerWord) << data << endl;
	return ss.str();
}


string makeWriteOutput(int setIndex, bool hit, int accessTime) {
	string hitString;
	stringstream ss;
	if(hit == 1) {
		hitString = "hit";
	} else {
		hitString = "miss";
	}
	ss << "write-ack " << setIndex << " " << hitString << " " << accessTime << endl;
	return ss.str();
}
