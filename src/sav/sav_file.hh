#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

#include "oci/diff_mode.hh"

class SavHeader
{
public:
    SavHeader();
    SavHeader(std::uint32_t index, std::uint8_t room, std::uint32_t play_time,
        std::uint8_t times_saved, oci::DiffMode diff_mode);
    std::uint32_t getIndex();
    std::uint8_t getRoom();
    std::uint32_t getPlayTime();
    std::uint8_t getTimesSaved();
    std::uint16_t getUk1();
    oci::DiffMode getDiffMode();
    oci::DiffMode* getDiffModePtr();
    std::uint16_t getUk2();
    std::uint16_t getItemsCharactersLength();

    void setIndex(std::uint32_t index);
    void setRoom(std::uint8_t room);
    void setPlayTime(std::uint32_t play_time);
    void setTimesSaved(std::uint8_t times_saved);
    void setUk1(std::uint16_t uk1);
    void setDiffMode(oci::DiffMode diff_mode);
    void setUk2(std::uint16_t uk2);
    void setItemsCharactersLength(std::uint16_t items_characters_length);
private:
    std::uint32_t index_;
    std::uint8_t room_;
    std::uint32_t play_time_;
    std::uint8_t times_saved_;
    std::uint16_t uk1_;
    oci::DiffMode diff_mode_;
    std::uint16_t uk2_;
    std::uint16_t items_characters_length_;
};

struct SavItem
{
    SavItem(std::uint32_t u, std::uint8_t q, std::uint32_t ei);
    std::uint32_t uid;
    std::uint8_t quantity;
    std::uint32_t extra_info;
};

enum class AmmoType
{
    SHOTGUN = 0x06,
    HANDGUN = 0x07
};

struct SavAmmo
{
    SavAmmo(std::uint8_t t, std::uint32_t q);
    std::uint8_t type;
    std::uint32_t quantity_msb;
    std::uint32_t quantity;
};

enum class InventoryElementType
{
    ITEM,
    AMMO
};

struct SavInventoryElement
{
    SavInventoryElement(InventoryElementType t, SavItem i);
    SavInventoryElement(InventoryElementType t, SavAmmo a);
    SavInventoryElement(const SavInventoryElement& other);
    InventoryElementType type;
    union
    {
        SavItem item;
        SavAmmo ammo;
    };
};

class SavItems
{
public:
    SavItems();
    SavItems(std::uint16_t length, std::uint8_t inventory_capacity);
    std::uint16_t getLength();
    std::uint8_t getInventoryCapacity();
    std::vector<SavInventoryElement>& getItems();
    void setLength(std::uint16_t length);
    void setInventoryCapacity(std::uint8_t inventory_capacity);
    void pushItem(SavInventoryElement element);
    void removeItem(int index);
private:
    std::uint16_t length_;
    std::uint8_t inventory_capacity_;
    std::vector<SavInventoryElement> items_;
};

class SavFile
{
public:
    SavFile() = default;
    static SavFile* makeFile(std::filesystem::path path);
    void serialize(std::filesystem::path path);
    SavHeader& getHeader();
    SavItems& getItems();
    static void correctCrc32(std::filesystem::path path);
private:
    SavHeader header_;
    SavItems items_;
    int rest_content_len_;
    char* rest_content_;
    void parseHeader(std::ifstream& file);
    void parseItems(std::ifstream& file);
    void parseItem(std::ifstream& file);
};