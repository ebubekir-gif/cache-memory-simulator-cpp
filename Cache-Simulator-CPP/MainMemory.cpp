#include "MainMemory.h"

#include <fstream>
#include <array>
#include <iostream>
#include <string>
#include <format>

MainMemory::MainMemory()
{
	// Allocate memory region
	memory = std::make_unique<std::array<uint8_t, MAIN_MEMORY_SIZE>>();

	// Fill main memory with zeros
	memory.get()->fill(0x00);
}

MainMemory::~MainMemory()
{
}

void MainMemory::Read(uint32_t startAdress, uint8_t size, uint8_t* destination)
{
	std::string message = std::format(
		"Transfer from main memory to cache (address: 0x{:x})", startAdress);

	std::cout << message << std::endl;

	// Read the requested amount of memory and copy destination
	std::memcpy(destination, &memory.get()->at(startAdress), size);
}

void MainMemory::Write(uint32_t startAdress, uint8_t size, uint8_t* source)
{
	std::string message = std::format(
		"Writing to main memory (address: 0x{:x})", startAdress);

	std::cout << message << std::endl;

	// Copy the requested amount of memory from the source to main memory
	std::memcpy(&memory.get()->at(startAdress), source, size);
}

void MainMemory::Print()
{

	uint8_t ROWS = 48;
	uint8_t COLUMNS = 26;
	for (uint8_t row = 0; row < ROWS; row++)
	{
		for (uint8_t column = 0; column < COLUMNS; column++)
		{
			std::cout << std::format("0x{:02x}  ", memory.get()->at(row * COLUMNS + column));
		}
		std::cout << std::endl;
	}

	//	FİLE SAVE
	/* 
	std::string line;
	// Print a slice of the memory region (for debug)
	std::ofstream dosya("MainMemory0.csv");

	if (dosya.is_open()) {
		line = std::format("{: ^12};{: ^12}\n", "Address", "Data");
		dosya << line;
		for (uint32_t i = 0x00;i <= 0xffff;i++) {
			line = std::format("{: ^12};{: ^12}\n", std::format("0x{:04x}",i), std::format("=\"{:08b}\"", memory.get()->at(i)));
			dosya << line;
		}
	}
	dosya.close();
	*/
}
