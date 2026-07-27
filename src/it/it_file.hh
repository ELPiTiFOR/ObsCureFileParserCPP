#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

#include "oci/diff_mode.hh"

class ItItem
{
public:
    ItItem(std::uint32_t type, std::uint32_t uid,
        std::uint32_t extra_info, int multiplier, oci::DiffMode diff_mode);
    std::uint32_t getItemType() const;
    std::uint32_t& getItemType();
    std::uint32_t getItemUid() const;
    std::uint32_t getExtraInfo() const;
    std::uint32_t& getExtraInfo();
    int getMultiplier() const;
    oci::DiffMode getDiffMode() const;
    oci::DiffMode& getDiffMode();
    void setItemType(std::uint32_t item_type);
    void setItemUid(std::uint32_t item_uid);
    void setExtraInfo(std::uint32_t extra_info);
    void setMultiplier(int multiplier);
    void setDiffMode(oci::DiffMode diff_mode);
private:
    std::uint32_t item_type_;
    std::uint32_t item_uid_;
    std::uint32_t extra_info_;
    int multiplier_;
    oci::DiffMode diff_mode_;
};

class ItFile
{
public:
    ItFile() = default;
    static ItFile* makeFile(std::filesystem::path path);
    void serialize(std::filesystem::path path);
    const std::vector<ItItem>& getItems() const;
    std::vector<ItItem>& getItems();
private:
    std::vector<ItItem> items_;

};

std::ostream& operator<<(std::ostream& os, const ItItem& item);
std::ostream& operator<<(std::ostream& os, const ItFile& it_file);
bool operator==(const ItItem& item1, const ItItem& item2);
bool operator==(const ItFile& it_file1, const ItFile& it_file2);