#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "mem_sim_libs.hpp"
#include "mem_sim_classes.hpp"

std::string flushCommand (CacheStructure& cacheVect, const Parameters& P);
std::string debugCommand (CacheStructure& cacheVect, const Parameters& P);
std::string readOrWriteCommand (DataStructure& cacheData, CacheStructure& cacheVect, const Parameters& P, unsigned address, bool write);
std::string makeReadOutput(DataStructure& cacheData, unsigned address, const Parameters& P, int setIndex, bool hit, int accessTime);
std::string makeWriteOutput(int setIndex, bool hit, int accessTime);

#endif
