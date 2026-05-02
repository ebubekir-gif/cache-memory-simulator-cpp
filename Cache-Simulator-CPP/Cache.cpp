#include "Cache.h"
#include "Processor.h"
#include <iostream>
#include <format>
#include <string>

CacheSet::CacheSet()
{
	// Set the number of cache ways in the replecement algorithm
	replacement.setWays(CACHE_WAYS);
	for (uint8_t i = 0;i < CACHE_WAYS;i++)
	{
		LRU[i] = i;
	}
}

CacheSet::~CacheSet()
{
}

CacheLine* CacheSet::Find(uint32_t tag)
{
	// Find the cache line based on the given tag
	for (way = 0; way < CACHE_WAYS; way++)
	{
		if(lines[way].valid && lines[way].tag == tag)
		{
			return &lines[way];
		}
	}

	// Cache line wasn't found
	return nullptr;
}

CacheLine* CacheSet::Replece(uint32_t tag, uint8_t* sourceData)
{
	// Choose a victim line to replece
	uint8_t victim = getVictim();

	std::string message = std::format("ways: {}", victim);

	std::cout << message << std::endl;

	// Set new cache line attributes
	lines[victim].valid = true;
	lines[victim].tag = tag;

	// Copy 64 byte data from main memory to cache 
	std::memcpy(lines[victim].data.data(), sourceData, CACHE_LINE_SIZE);

	return &lines[victim];
}

void CacheSet::updateLRU()
{
	replacement.updateLRU(LRU, way);
}

uint8_t CacheSet::getVictim()
{
	uint8_t victim = LRU[0];
	for (way = 0;way < CACHE_WAYS - 1;way++)LRU[way] = LRU[way + 1];
	LRU[CACHE_WAYS-1] = victim;
	return victim;
}

void Cache::Initialize(MainMemory* memory)
{
	mainMemory = memory;
}

uint32_t Cache::Read(uint32_t address)
{
	AddressParts addressParts(address);

	// Find the requested cache line
	CacheLine* line = sets[addressParts.setIndex].Find(addressParts.tag);

	// Update cache statistics (cache accessed)
	statistics.cacheAccesses += 1; 

	if (line) // cache hit
	{
		std::string message = std::format(
			"Reading from cache (address: 0x{:x}, set: {}, tag: {})",
			address, addressParts.setIndex, addressParts.tag);

		std::cout << message << std::endl;

		// Update cache statistics (cache hits)
		statistics.cacheHits += 1;

		// Update the LRU stack
		sets[addressParts.setIndex].updateLRU();

		// Reinterpret the memory as a 32-bit integer
		return *reinterpret_cast<uint32_t*>(&line->data[addressParts.byteOffset]);
	}
	else	  // cache miss
	{
		// Find the beginnig of the cache line
		uint32_t lineStart = address & ~(CACHE_LINE_SIZE - 1);

		// Allocate data buffer 
		std::array<uint8_t, CACHE_LINE_SIZE> buffer;

		// Read the requisted data from main memory
		mainMemory->Read(lineStart, CACHE_LINE_SIZE, buffer.data());

		// Replece in the cache line in the set 
		CacheLine* newLine = sets[addressParts.setIndex].Replece(addressParts.tag, buffer.data());

		std::string message = std::format(
			"Reading from cache (address: 0x{:x}, set: {}, tag: {})",
			address, addressParts.setIndex, addressParts.tag);

		std::cout << message << std::endl;
		
		// Reinterpret the memory as a 32-bit integer and return it
		return *reinterpret_cast<uint32_t*>(&newLine->data[addressParts.byteOffset]);
	}

	return 0;
}

void Cache::Write(uint32_t address, uint32_t data)
{
	AddressParts addressParts(address);

	// Find the requested line in the cache

	CacheLine* line = sets[addressParts.setIndex].Find(addressParts.tag);

	// Update cache statistics (cache accessed)
	statistics.cacheAccesses += 1;

	if (line) // Cache hit
	{
		std::string message = std::format(
			"Write to cache (address: 0x{:x}, set: {}, tag: {}, value: 0x{:x})",
			address, addressParts.setIndex, addressParts.tag, data);

		std::cout << message << std::endl;

		// Update cache statistics (cache hits)
		statistics.cacheHits += 1;

		sets[addressParts.setIndex].updateLRU();

		// Reinterpret the cache memory as a 32-bit integer and write the data
		*reinterpret_cast<uint32_t*>(&line->data[addressParts.byteOffset]) = data;
	}

	// Write-trought cache (immediately write modified data to main memory)
	mainMemory->Write(address, sizeof(uint32_t), reinterpret_cast<uint8_t*>(&data));
}

cacheStatistics Cache::GetStatistics() const
{
	return statistics;
}

void Cache::ResetStatistics()
{
	statistics.cacheAccesses = 0;
	statistics.cacheHits = 0;
}


