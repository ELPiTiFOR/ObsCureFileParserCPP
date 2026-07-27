#include "it_file.hh"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "fileread/fileread.hh"
#include "filewrite/filewrite.hh"
#include "utils/utils.hh"

#include "oci/item.hh"

/*
**  ItItem
*/

ItItem::ItItem(std::uint32_t type, std::uint32_t uid,
    std::uint32_t extra_info, int multiplier, oci::DiffMode diff_mode)
    : item_type_(type)
    , item_uid_(uid)
    , extra_info_(extra_info)
    , multiplier_(multiplier)
    , diff_mode_(diff_mode)
{}

std::uint32_t ItItem::getItemType() const
{
    return item_type_;
}

std::uint32_t& ItItem::getItemType()
{
    return item_type_;
}

std::uint32_t ItItem::getItemUid() const
{
    return item_uid_;
}

std::uint32_t ItItem::getExtraInfo() const
{
    return extra_info_;
}

std::uint32_t& ItItem::getExtraInfo()
{
    return extra_info_;
}

int ItItem::getMultiplier() const
{
    return multiplier_;
}

oci::DiffMode ItItem::getDiffMode() const
{
    return diff_mode_;
}

oci::DiffMode& ItItem::getDiffMode()
{
    return diff_mode_;
}

void ItItem::setItemType(std::uint32_t item_type)
{
    item_type_ = item_type;
}

void ItItem::setItemUid(std::uint32_t item_uid)
{
    item_uid_ = item_uid;
}

void ItItem::setExtraInfo(std::uint32_t extra_info)
{
    extra_info_ = extra_info;
}

void ItItem::setMultiplier(int multiplier)
{
    multiplier_ = multiplier;
}

void ItItem::setDiffMode(oci::DiffMode diff_mode)
{
    diff_mode_ = diff_mode;
}

std::ostream& operator<<(std::ostream& os, const ItItem& item)
{
    try
    {
        const oci::Item& oci_item = oci::Item::searchItemType(item.getItemType());
        os << "(type=" << oci_item.name << ", ";

    }
    catch (std::exception& e)
    {
        os << "(type=0x" << std::hex << item.getItemType() << ", ";
    }

    os << "UID=0x" << item.getItemUid() << ", ";

    try
    {
        const oci::ExtraInfo& extra_info = oci::ExtraInfo::searchExtraInfoId(item.getExtraInfo());
        if (extra_info.name == "NO_EXTRA_INFO")
        {
            throw std::invalid_argument("");
        }

        os << "Extra Info=" << extra_info.name << ", ";

    }
    catch (std::exception& e)
    {
        os << "Extra Info=0x" << item.getExtraInfo() << ", ";
    }

    os << "Multiplier=" << item.getMultiplier() << ", ";
    os << "DiffMode=" << item.getDiffMode() << ")";
    return os;
}

bool operator==(const ItItem& item1, const ItItem& item2)
{
    if (item1.getItemType() != item2.getItemType())
    {
        return 0;
    }
    else if (item1.getItemUid() != item2.getItemUid())
    {
        return 0;
    }
    else if (item1.getExtraInfo() != item2.getExtraInfo())
    {
        return 0;
    }
    else if (item1.getMultiplier() != item2.getMultiplier())
    {
        return 0;
    }
    else if (item1.getDiffMode().getFlags()
        != item2.getDiffMode().getFlags())
    {
        return 0;
    }

    return 1;
}

/*
**  ItFile
*/

ItFile* ItFile::makeFile(std::filesystem::path path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return nullptr;
    }

    auto it_file = new ItFile();
    while (file)
    {
        std::uint32_t item_type = fileread::read4ByteMsb(file);
        if (!file)
        {
            break;
        }

        std::uint32_t item_uid = fileread::read4ByteMsb(file);
        if (!file)
        {
            delete it_file;
            return nullptr;
        }

        std::uint32_t extra_info = fileread::read4ByteMsb(file);
        if (!file)
        {
            delete it_file;
            return nullptr;
        }

        std::uint32_t multiplier = fileread::read4ByteMsb(file);
        if (!file)
        {
            delete it_file;
            return nullptr;
        }
        std::uint32_t diff_mode = fileread::read4ByteMsb(file);
        if (!file)
        {
            delete it_file;
            return nullptr;
        }

        it_file->items_.push_back(ItItem(item_type, item_uid, extra_info, multiplier, oci::DiffMode(diff_mode)));
    }

    file.close();
    return it_file;
}

void ItFile::serialize(std::filesystem::path path)
{
    std::ofstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return;
    }

    for (ItItem& my_item : items_)
    {
        filewrite::write4ByteMsb(file, my_item.getItemType());
        filewrite::write4ByteMsb(file, my_item.getItemUid());
        filewrite::write4ByteMsb(file, my_item.getExtraInfo());
        filewrite::write4ByteMsb(file, my_item.getMultiplier());
        filewrite::write4ByteMsb(file, my_item.getDiffMode().getFlags());
    }

    file.close();
}

const std::vector<ItItem>& ItFile::getItems() const
{
    return items_;
}

std::vector<ItItem>& ItFile::getItems()
{
    return items_;
}

std::ostream& operator<<(std::ostream& os, const ItFile& it_file)
{
    os << "ItFile:" << std::endl;
    int i = 0;
    for (const ItItem& item : it_file.getItems())
    {
        os << "    Item" << i << item << std::endl;
        i++;
    }

    return os;
}

bool operator==(const ItFile& it_file1, const ItFile& it_file2)
{
    return it_file1.getItems() == it_file2.getItems();
}