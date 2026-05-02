#pragma once

#include <cstdint>
//#include <iodtream>
#include <array>

class LRUreplacement
{
public:
	void setWays(uint8_t numOfWays);
	uint8_t getVictim(uint8_t LRU[]);
	void updateLRU(uint8_t LRU[], uint8_t way);

private:
	uint8_t ways = 0;
};