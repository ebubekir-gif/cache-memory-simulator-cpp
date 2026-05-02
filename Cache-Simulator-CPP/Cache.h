#pragma once

#include "MainMemory.h"
#include "ReplacementAlgorithms.h"
#include <array>

const uint8_t MEMORY_ADDRESS_SIZE = 32;							// 32-bit memory address
const uint8_t CACHE_LINE_SIZE = 64;								// 64-bytes cache lines
const uint32_t CACHE_SETS = 64;									// Cache with 64 sets
const uint8_t CACHE_WAYS = 4;									// 4-way set-associative cache

const uint8_t CACHE_LINE_BYTE_OFFSET_SIZE = 6;					// log2(64) = 6 bits for line offset
const uint8_t CACHE_LINE_SET_INDEX_SIZE = 6;					// log2(64) = 6 bits for set index
const uint8_t CACHE_LINE_TAG_SIZE = 20;							//(MEMORY_ADDRESS_SIZE - CACHE_LINE_BYTE_OFFSET_SIZE - CACHE_LINE_SET_INDEX_SIZE) Remaining bits for tag

struct CacheLine
{
	uint32_t tag = 0;											// 20 bits address tag
	std::array<uint8_t, CACHE_LINE_SIZE> data;					// 64-bytes cache line data
	bool valid = false;											// line is valid/invalid
};

struct AddressParts
{
	uint32_t tag;
	uint8_t setIndex;
	uint8_t byteOffset;

	AddressParts(uint32_t address)
	{
		byteOffset = address & ((1 << CACHE_LINE_BYTE_OFFSET_SIZE) - 1);
		setIndex = (address >> CACHE_LINE_BYTE_OFFSET_SIZE) & ((1 << CACHE_LINE_SET_INDEX_SIZE) - 1);
		tag = address >> (CACHE_LINE_BYTE_OFFSET_SIZE + CACHE_LINE_SET_INDEX_SIZE);
	}
};

struct cacheStatistics 
{
	uint32_t cacheAccesses;			// Number of times the cache was accessed
	uint32_t cacheHits;				// Number of cache hits

	float_t GetHitRate()
	{
		return (static_cast<float_t>(cacheHits) / cacheAccesses);
	}
};

class CacheSet
{
public:
	CacheSet();
	~CacheSet();

	CacheLine* Find(uint32_t tag);
	CacheLine* Replece(uint32_t tag, uint8_t* sourceData);
	void updateLRU();
	uint8_t getVictim();

private:
	std::array<CacheLine, CACHE_WAYS> lines;		// Array of cache lines
	LRUreplacement replacement;						// Random replecement algorithm
	uint8_t LRU[CACHE_WAYS];						// LRU array ways
	uint8_t way;
};

class Cache
{
public:
	void Initialize(MainMemory* memory);
	uint32_t Read(uint32_t address);
	void Write(uint32_t address, uint32_t data);

	cacheStatistics GetStatistics() const;
	void ResetStatistics();
private:
	std::array<CacheSet, CACHE_SETS> sets;			// Array of cache sets
	MainMemory* mainMemory;							// Link to main memory
	cacheStatistics statistics;
};