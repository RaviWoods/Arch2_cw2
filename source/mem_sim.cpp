#include "mem_sim_libs.hpp"
#include "mem_sim_classes.hpp"
#include "mem_sim_functions.hpp"
using namespace std;

int main(int argc, const char * argv[]){
	if( argc < 8 ){
		cout << "Less than 8 inputs." << endl;
		exit( EXIT_FAILURE );
	}
	
	Parameters P = Parameters(argv);
	string inputString;
	DataStructure cacheData;
	CacheStructure cacheVect(P.setPerCache);
	
	while(getline(cin, inputString)) {
		string instrString;
		string outputString;
		unsigned address;
		string data;
		istringstream line(inputString);
		line >> instrString;
		if (instrString == "flush-req") {
			SOUT("FLUSH");
			outputString = flushCommand(cacheVect,P);
		} else if (instrString == "debug-req") {
			SOUT("DEBUG");
			outputString  = debugCommand(cacheVect,P);
		} else if (instrString == "read-req") { 
			SOUT("READ");
			line >> address;
			outputString = readOrWriteCommand(cacheData,cacheVect,P,address,0);
        } else if (instrString == "write-req") {
        	SOUT("WRITE");
        	line >> address >> data;
        	cacheData[address] = data;
        	outputString = readOrWriteCommand(cacheData,cacheVect,P,address,1);
        } 
        else { 
        	SOUT("NOTHING");
        }
        cout << outputString;
	}
	return 0;
}


