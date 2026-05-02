#include "Processor.h"
#include <iostream>

int main() {
    MemorySystem memory;

    uint32_t addresses[] = { 0x80, 0x1080, 0x2080, 0x3080, 0x4080, 0x5080 };
    for (uint8_t i = 0; i < 4;i++)
    {
        memory.Read(addresses[i]);
    }
    memory.Read(addresses[0]);
    memory.Read(addresses[5]);

    return 0;
}