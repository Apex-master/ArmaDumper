#include "includes.h"
#include "memory.h"

class PatternScan
{
    std::vector<uint8_t> buffer;
    size_t max_size = 0x1990000;
    const size_t chunkSize = 4096;

public:
    struct Pattern
    {
        std::string pattern;
        size_t offset_start;
        size_t offset_size;
        size_t instruction_size;
        bool displacement;
    };

	bool Initialize(uintptr_t address);
    uintptr_t Scan(Pattern pattern, bool debug);
    bool ClearBuffer();
}; 