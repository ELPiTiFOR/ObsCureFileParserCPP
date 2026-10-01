#include "bytecounter.hh"

std::map<std::string, std::uint32_t> ByteCounter::counters_;

void ByteCounter::startCounter(std::string key)
{
    counters_[key] = 0;
}
std::uint32_t ByteCounter::getCounter(std::string key)
{
    return counters_[key];
}
void ByteCounter::addToCounters(std::uint32_t n)
{
    for (auto const& [key, value] : counters_)
    {
        counters_[key] += n;
    }
}
void ByteCounter::stopCounter(std::string key)
{
    counters_.erase(key);
}