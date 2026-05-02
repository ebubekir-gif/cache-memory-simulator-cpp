# Cache Memory Simulator in C++

This repository contains a low-level C++ simulation of a CPU Cache and Main Memory architecture. It features a 4-way set-associative cache design and successfully implements the LRU (Least Recently Used) replacement policy from scratch.

## 🚀 Key Features
* **Main Memory Simulation:** 4MB byte-addressable simulated RAM initialized with zero-fill.
* **Cache Architecture:** 64-byte cache lines, 64 sets, 4-way set-associative mapping.
* **Replacement Policy:** Custom LRU (Least Recently Used) logic for cache eviction.
* **Write Policy:** Write-through cache (immediately writes modified data to main memory).
* **Statistics Tracker:** Tracks cache hits, cache accesses, and dynamically calculates the hit rate.

## 📁 Project Structure
* `main.cpp` - Entry point demonstrating simulated memory read/write operations.
* `Cache.h` / `Cache.cpp` - Core cache logic, handling tag extraction, set management, and hit/miss evaluation.
* `MainMemory.h` / `MainMemory.cpp` - Simulation of the underlying RAM block and data transfer routines.
* `Processor.h` / `Processor.cpp` - MemorySystem wrapper that serves as an interface between the CPU and the memory hierarchy.
* `ReplacementAlgorithms.h` / `ReplacementAlgorithms.cpp` - Matrix/Array-based LRU stack implementation.

## 🛠️ How to Compile and Run
Since this is a standard C++ project without external dependencies, you can compile it using `g++` or any standard C++ compiler.

1. Clone the repository:
   ```bash
   git clone [https://github.com/ebubekir-gif/cache-memory-simulator-cpp.git](https://github.com/ebubekir-gif/cache-memory-simulator-cpp.git)
