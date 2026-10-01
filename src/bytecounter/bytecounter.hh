#pragma once

#include <cstdint>
#include <map>
#include <string>

class ByteCounter
{
public:
    static void startCounter(std::string key);
    static std::uint32_t getCounter(std::string key);
    static void addToCounters(std::uint32_t n);
    static void stopCounter(std::string key);
private:
    static std::map<std::string, std::uint32_t> counters_;
};