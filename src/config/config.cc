#include "config.hh"

#include <iostream>
#include <sstream>

Config::Config(const std::string& path)
    : Config(std::filesystem::path(path))
{}

Config::Config(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open config file: " + path.string());
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        
        parseLine(line);
    }
}

void Config::parseLine(const std::string& line)
{
    size_t pos = line.find('=');
    if (pos == std::string::npos)
    {
        throw std::runtime_error("Invalid config line (no '='): " + line);
    }
    
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    
    pairs_[key] = value;
}

std::string Config::getValue(const std::string& key) const
{
    auto it = pairs_.find(key);
    if (it == pairs_.end())
    {
        return "";
    }

    return it->second;
}

bool Config::hasKey(const std::string& key) const
{
    return pairs_.find(key) != pairs_.end();
}

std::string Config::getValueOrDefault(const std::string& key, 
    const std::string& default_value) const
{
    auto it = pairs_.find(key);
    if (it == pairs_.end())
    {
        return default_value;
    }

    return it->second;
}

const std::unordered_map<std::string, std::string>& Config::getPairs() const
{
    return pairs_;
}

void Config::print() const
{
    for (const auto& [key, value] : pairs_)
    {
        std::cout << key << " = " << value << '\n';
    }
}
