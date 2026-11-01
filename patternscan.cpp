#include "patternscan.h"

bool PatternScan::Initialize(uintptr_t address)
{
    buffer.clear();
    buffer.resize(max_size);

    size_t numChunks = (max_size + chunkSize - 1) / chunkSize;

    for (size_t chunkIndex = 0; chunkIndex < numChunks; chunkIndex++)
    {
        size_t chunkOffset = chunkIndex * chunkSize;
        size_t currentChunkSize = chunkSize;

        if (chunkOffset + chunkSize > max_size)
        {
            currentChunkSize = max_size - chunkOffset;
        }

        //  printf("[+] Reading Chunk, Address: %llx\n", address + chunkOffset);

        if (!ReadBuffer(address + chunkOffset, buffer.data() + chunkOffset, currentChunkSize))
        {
            //  printf("[-] Failed to Read Chunk, Address: %llx\n", address + chunkOffset);
            //  return false;
        }
    }

    return true;
}

uintptr_t PatternScan::Scan(Pattern pattern, bool debug)
{
    auto hex_char_to_byte = [](char c) -> uint8_t
        {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'A' && c <= 'F') return c - 'A' + 10;
            if (c >= 'a' && c <= 'f') return c - 'a' + 10;
            return 0;
        };

    auto pattern_to_bytes = [&](const std::string& pattern) -> std::vector<uint8_t>
        {
            std::vector<uint8_t> bytes;
            for (size_t i = 0; i < pattern.length(); i += 3)
            {
                char c1 = pattern[i];
                char c2 = pattern[i + 1];
                if (c1 == '?' && c2 == '?')
                {
                    bytes.push_back(0x00); // Treat ?? as the wildcard
                }
                else
                {
                    uint8_t byte = (hex_char_to_byte(c1) << 4) | hex_char_to_byte(c2);
                    bytes.push_back(byte);
                }
            }
            return bytes;
        };

    std::vector<uint8_t> pattern_bytes = pattern_to_bytes(pattern.pattern);

    for (size_t address_offset = 0; address_offset < buffer.size() - pattern_bytes.size(); ++address_offset)
    {
        bool found = true;
        for (size_t i = 0; i < pattern_bytes.size(); ++i)
        {
            if (pattern_bytes[i] != 0x00 && pattern_bytes[i] != buffer[address_offset + i])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            uintptr_t address = mem.game_base_address + address_offset;

            if (debug)
            {
                std::cout << "[+] Pattern found at address: 0x" << std::hex << address << " - Bytes: ";
                for (size_t i = 0; i < pattern_bytes.size(); ++i) {
                    std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[address_offset + i]) << " ";
                }
                std::cout << std::endl;
            }

            std::vector<uint8_t> extracted_bytes;
            for (size_t i = 0; i < pattern_bytes.size() && i < pattern.offset_size; ++i)
            {
                extracted_bytes.push_back(buffer[address_offset + i + pattern.offset_start]);
            }

            if (debug)
            {
                std::cout << "[+] Extracted Bytes: ";
            }

            for (uint8_t byte : extracted_bytes)
            {
                std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;

            uintptr_t reversed_bytes = 0;
            for (int i = extracted_bytes.size() - 1; i >= 0; --i)
            {
                reversed_bytes = (reversed_bytes << 8) | extracted_bytes[i];
            }
            if (debug)
            {
                std::cout << "[+] Reversed Bytes: 0x" << std::hex << reversed_bytes << std::endl;
            }

            if (pattern.displacement)
            {
                std::cout << "\n";
                return reversed_bytes;
            }

            uintptr_t final_address = address + reversed_bytes + pattern.instruction_size;

            if (debug)
            {
                std::cout << "[+] Final Address: " << final_address << "\n" << std::endl;
            }

            return final_address;
        }
    }
    return 0;
}

bool PatternScan::ClearBuffer()
{
    std::vector<uint8_t>().swap(buffer);
    return true;
}