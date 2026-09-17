#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <stdexcept>

// TODO: this class needs a rework, the constructor should not fail, the loading
// of a config file should be a function used on an already created object
// Also I might want to have a ApplicationConfig or something, by that I mean
// that a Config class that lets you have key-value pairs, read files, etc is
// one thing, and a class that stores THE SPECIFIC SETTINGS THE PROGRAM NEEDS
// is another thing
// Does that make sense? Or maybe this is just Entreprise Java-like reasoning
class Config
{
public:
    Config();
    Config(const std::string& path);
    Config(const std::filesystem::path& path);
    std::string getValue(const std::string& key) const;
    bool hasKey(const std::string& key) const;
    std::string getValueOrDefault(const std::string& key, 
        const std::string& default_value = "") const;
    const std::unordered_map<std::string, std::string>& getPairs() const;
    void setValue(const std::string& key, const std::string& value);
    void print() const;
    
private:
    std::unordered_map<std::string, std::string> pairs_;
    void loadFromFile(const std::filesystem::path& path);
    void parseLine(const std::string& line);
};