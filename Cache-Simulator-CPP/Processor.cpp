#include "Processor.h"
#include <iostream>
#include <string>
#include <format>

MemorySystem::MemorySystem()
{
	cache.Initialize(&mainMemory);
}

MemorySystem::~MemorySystem()
{
}
uint32_t MemorySystem::Read(uint32_t address)
{
	return cache.Read(address);
}
void MemorySystem::Write(uint32_t address, uint32_t data)
{
	cache.Write(address, data);
}
void MemorySystem::PrintMainMemory()
{
	mainMemory.Print();
}

cacheStatistics MemorySystem::GetCacheStatistics() const
{
	return cache.GetStatistics();
}

void MemorySystem::ResetCacheStatistics()
{
	cache.ResetStatistics();
}
