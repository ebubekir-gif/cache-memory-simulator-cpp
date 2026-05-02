#include "ReplacementAlgorithms.h"

void LRUreplacement::setWays(uint8_t numOfWays)
{
    ways = numOfWays;
}

void LRUreplacement::updateLRU(uint8_t LRU[], uint8_t way)
{
    uint8_t index;
    for (index = 0;index < ways;index++) 
    {
        if (LRU[index] == way)
        {
            break;
        }
    }
    for (index;index < ways-1;index++) 
    {
        LRU[index] = LRU[index + 1];
    }
    LRU[ways - 1] = way;
}

uint8_t LRUreplacement::getVictim(uint8_t LRU[])
{
    uint8_t victim = LRU[0];
    uint8_t index;
    for (index = 0;index < ways - 1;index++)LRU[index] = LRU[index + 1];
    LRU[ways - 1] = victim;
    return victim;
}
