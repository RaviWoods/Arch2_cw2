#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

int main(int argc, const char * argv[]){


	if( argc < 8 ){
		cout << "Less than 8 inputs." << endl;
		exit( EXIT_FAILURE );
	}
	
	unsigned addressLength = stoi(argv[1]);
	unsigned bytePerWord	= stoi(argv[2]);
	unsigned wordPerBlock	= stoi(argv[3]);
	unsigned blockPerSet	= stoi(argv[4]);
	unsigned setPerCache	= stoi(argv[5]);
	unsigned hitTime 	= stoi(argv[6]);
	unsigned readTime	= stoi(argv[7]);
	unsigned writeTime	= stoi(argv[8]);
	string input;
	map <long, int> cacheData;
	while(getline(cin, input)) {
		string buffer;
		unsigned address;
		unsigned data;
		istringstream sstr(input);
		sstr >> buffer;
		if (input == "flush-req") {
			cout << "flush" << endl;
		} else if (input == "debug-req") {
			cout << "debug" << endl;
		} else if (buffer == "read-req") { 
			cout << "READ" << endl;
			sstr >> address;
			if (cacheData.count(address) == 1) {
				cout << hex << cacheData.find(address)->second << endl;
			} else {
				cout << 0 << endl;
			}
			
        } else if (buffer == "write-req") {
        	cout << "WRITE" << endl;
        	sstr >> address >> hex >> data;
        	cacheData[address] = data;
        } 
        else { 
        	cout << "NOTHING" << endl;
        }
	}

}
