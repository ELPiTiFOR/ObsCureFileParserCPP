#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <stdexcept>

class Config
{
public:
    Config(const std::string& path);
    Config(const std::filesystem::path& path);
    std::string getValue(const std::string& key) const;
    bool hasKey(const std::string& key) const;
    std::string getValueOrDefault(const std::string& key, 
        const std::string& default_value = "") const;
    const std::unordered_map<std::string, std::string>& getPairs() const;
    void print() const;
    
private:
    std::unordered_map<std::string, std::string> pairs_;
    void loadFromFile(const std::filesystem::path& path);
    void parseLine(const std::string& line);
};