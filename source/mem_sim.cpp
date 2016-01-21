#include "libs.h"
using namespace std;

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
		friend ostream& operator<< (std::ostream & out, Block const& data) {
    		out << "B" << data.bAddress << " dirtyBit = " << data.dirtyBit << endl;
		}
};

string readOrWrite (map<long, string>& cacheData, vector<list<Block>>& cacheVect, const Parameters& P, unsigned address, bool write);
string makeReadOutput(map<long, string>& cacheData, unsigned address, const Parameters& P, int setIndex, bool hit, int accessTime);
string makeWriteOutput(int setIndex, bool hit, int accessTime);

int main(int argc, const char * argv[]){
	if( argc < 8 ){
		cout << "Less than 8 inputs." << endl;
		exit( EXIT_FAILURE );
	}
	
	Parameters P = Parameters(argv);
	string input;
	map <long, string> cacheData;
	vector<list<Block>> cacheVect(P.setPerCache);
	
	while(getline(cin, input)) {
		string buffer;
		string outputString;
		unsigned address;
		string data;
		istringstream sstr(input);
		sstr >> buffer;
		if (input == "flush-req") {
			int accessTime = 0;
			SOUT("FLUSH");
			for (vector<list<Block>>::iterator v_it = cacheVect.begin() ; v_it != cacheVect.end(); ++v_it) {
				for(list<Block>::iterator l_it = v_it->begin(); l_it != v_it->end(); ++l_it) {
					if(l_it->dirtyBit == 1) {
			 			accessTime += P.writeTime;
						l_it->dirtyBit = 0;
					}
				}
			}

			stringstream ss;
			ss << "flush-ack " << accessTime << endl;
			outputString = ss.str();
		} else if (input == "debug-req") {
			SOUT("DEBUG");
			stringstream ss;
			ss << "debug-ack-begin" << endl;
			for (vector<list<Block>>::iterator v_it = cacheVect.begin() ; v_it != cacheVect.end(); ++v_it) {
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
			outputString = ss.str();
		} else if (buffer == "read-req") { 
			SOUT("READ");
			sstr >> address;
			outputString = readOrWrite(cacheData,cacheVect,P,address,0);
        } else if (buffer == "write-req") {
        	SOUT("WRITE");
        	sstr >> address >> data;
        	cacheData[address] = data;
        	outputString = readOrWrite(cacheData,cacheVect,P,address,1);
        } 
        else { 
        	SOUT("NOTHING");
        }
        cout << outputString;
	}

}

string readOrWrite (map<long, string>& cacheData, vector<list<Block>>& cacheVect, const Parameters& P, unsigned address, bool write) {
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

string makeReadOutput(map<long, string>& cacheData, unsigned address, const Parameters& P, int setIndex, bool hit, int accessTime) {
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

