#include "sav_file.hh"

#include <cstdlib>
#include <cstdio>

#include "fileread/fileread.hh"
#include "filewrite/filewrite.hh"
#include "utils/utils.hh"

SavHeader::SavHeader(std::uint32_t index, std::uint8_t room,
    std::uint32_t play_time, std::uint8_t times_saved, oci::DiffMode diff_mode)
    : index_(index)
    , room_(room)
    , play_time_(play_time)
    , times_saved_(times_saved)
    , diff_mode_(diff_mode)
{}

SavHeader::SavHeader()
    : index_(0)
    , room_(0)
    , play_time_(0)
    , times_saved_(0)
    , diff_mode_(oci::DiffMode(0))
{}

std::uint32_t SavHeader::getIndex()
{
    return index_;
}

std::uint8_t SavHeader::getRoom()
{
    return room_;
}

std::uint32_t SavHeader::getPlayTime()
{
    return play_time_;
}

std::uint8_t SavHeader::getTimesSaved()
{
    return times_saved_;
}

std::uint16_t SavHeader::getUk1()
{
    return uk1_;
}

oci::DiffMode SavHeader::getDiffMode()
{
    return diff_mode_;
}

oci::DiffMode* SavHeader::getDiffModePtr()
{
    return &diff_mode_;
}

std::uint16_t SavHeader::getUk2()
{
    return uk2_;
}

std::uint16_t SavHeader::getItemsCharactersLength()
{
    return items_characters_length_;
}

void SavHeader::setIndex(std::uint32_t index)
{
    index_ = index;
}

void SavHeader::setRoom(std::uint8_t room)
{
    room_ = room;
}

void SavHeader::setPlayTime(std::uint32_t play_time)
{
    play_time_ = play_time;
}

void SavHeader::setTimesSaved(std::uint8_t times_saved)
{
    times_saved_ = times_saved;
}

void SavHeader::setUk1(std::uint16_t uk1)
{
    uk1_ = uk1;
}

void SavHeader::setDiffMode(oci::DiffMode diff_mode)
{
    diff_mode_ = diff_mode;
}

void SavHeader::setUk2(std::uint16_t uk2)
{
    uk2_ = uk2;
}

void SavHeader::setItemsCharactersLength(std::uint16_t items_characters_length)
{
    items_characters_length_ = items_characters_length;
}


SavItems::SavItems()
    : length_(0)
    , inventory_capacity_(0)
{}

SavItems::SavItems(std::uint16_t length, std::uint8_t inventory_capacity)
    : length_(length)
    , inventory_capacity_(inventory_capacity)
{}

std::uint16_t SavItems::getLength()
{
    return length_;
}

std::uint8_t SavItems::getInventoryCapacity()
{
    return inventory_capacity_;
}

std::vector<SavInventoryElement>& SavItems::getItems()
{
    return items_;
}

void SavItems::setLength(std::uint16_t length)
{
    length_ = length;
}

void SavItems::setInventoryCapacity(std::uint8_t inventory_capacity)
{
    inventory_capacity_ = inventory_capacity;
}

void SavItems::pushItem(SavInventoryElement element)
{
    int i = 0;
    while (i < inventory_capacity_)
    {
        if (items_.at(i).type == InventoryElementType::ITEM
            && items_.at(i).item.uid == 0)
        {
            break;
        }
        ++i;
    }

    if (i == inventory_capacity_)
    {
        return;
    }

    items_.at(i) = element;
}

void SavItems::removeItem(int index)
{
    SavInventoryElement null_element(
        InventoryElementType::ITEM,
        SavItem(0, 0, 0)
    );

    items_.at(index) = null_element;

    // TODO: optimization, stop when we the first null element is reached
    for (int i = index; i < inventory_capacity_ - 1; i++)
    {
        items_.at(i) = items_.at(i + 1);
    }

    items_.at(inventory_capacity_ - 1) = null_element;
}

void SavFile::parseHeader(std::ifstream& file)
{
    // Ignoring CRC32
    fileread::read4ByteLsb(file);

    // Ignoring unknown 0x06 field
    fileread::read1Byte(file);

    std::uint32_t index = fileread::read4ByteLsb(file);
    std::uint8_t room = fileread::read1Byte(file);
    std::uint32_t play_time = fileread::read4ByteLsb(file);
    std::uint8_t times_saved = fileread::read1Byte(file);
    std::uint16_t uk1 = fileread::read2ByteLsb(file);
    std::uint8_t diff_mode = fileread::read1Byte(file);
    std::uint16_t uk2 = fileread::read2ByteLsb(file);
    std::uint16_t items_characters_length = fileread::read2ByteLsb(file);

    header_.setIndex(index);
    header_.setRoom(room);
    header_.setPlayTime(play_time);
    header_.setTimesSaved(times_saved);
    header_.setUk1(uk1);
    header_.setDiffMode(oci::DiffMode(diff_mode));
    header_.setUk2(uk2);
    header_.setItemsCharactersLength(items_characters_length);
}

void SavFile::parseItem(std::ifstream& file)
{
    std::uint8_t first_byte = fileread::read1Byte(file);
    if (static_cast<AmmoType>(first_byte) == AmmoType::SHOTGUN
        || static_cast<AmmoType>(first_byte) == AmmoType::HANDGUN)
    {
        // we ignore the next 3 bytes
        fileread::read2ByteLsb(file);
        fileread::read1Byte(file);
        std::uint8_t quantity_msb = fileread::read1Byte(file);
        std::uint32_t quantity = fileread::read4ByteLsb(file);
        this->getItems().getItems().push_back(SavInventoryElement(
            InventoryElementType::AMMO,
            SavAmmo(first_byte, quantity)
        ));
        return;
    }

    std::uint8_t second_byte = fileread::read1Byte(file);
    std::uint8_t third_byte = fileread::read1Byte(file);
    std::uint8_t fourth_byte = fileread::read1Byte(file);

    // Recontructing UID
    std::uint32_t uid = first_byte | (second_byte << 8) | (third_byte << 16)
        | (fourth_byte << 24);

    std::uint8_t quantity = fileread::read1Byte(file);
    std::uint32_t extra_info = fileread::read4ByteLsb(file);
    // if (!uid)
    // {
    //     return;
    // }

    this->getItems().getItems().push_back(SavInventoryElement(
        InventoryElementType::ITEM,
        SavItem(uid, quantity, extra_info)
    ));
}

SavInventoryElement::SavInventoryElement(InventoryElementType t,
    SavItem i)
    : type(t)
    , item(i)
{}

SavInventoryElement::SavInventoryElement(InventoryElementType t,
    SavAmmo a)
    : type(t)
    , ammo(a)
{}

SavInventoryElement::SavInventoryElement(const SavInventoryElement& other)
    : type(other.type)
{
    if (type == InventoryElementType::ITEM)
    {
        item = other.item;
    }
    else
    {
        ammo = other.ammo;
    }
}

SavAmmo::SavAmmo(std::uint8_t t, std::uint32_t q)
    : type(t)
    , quantity_msb(utils::lsbOf(quantity))
    , quantity(q)
{
    quantity_msb &= 0xFF000000;
}

SavItem::SavItem(std::uint32_t u, std::uint8_t q, std::uint32_t ei)
    : uid(u)
    , quantity(q)
    , extra_info(ei)
{}

void SavFile::parseItems(std::ifstream& file)
{
    std::uint16_t length = fileread::read2ByteLsb(file);
    std::uint8_t inventory_capacity = fileread::read1Byte(file);
    
    this->items_.setLength(length);
    this->items_.setInventoryCapacity(inventory_capacity);
    for (int i = 0; i < inventory_capacity; i++)
    {
        this->parseItem(file);
    }
}

SavFile* SavFile::makeFile(std::filesystem::path path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return nullptr;
    }

    auto sav_file = new SavFile();

    sav_file->parseHeader(file);
    sav_file->parseItems(file);

    // TODO: for now we assume the items inventory does not need to be resized
    // we are ignoring the lengths for now

    sav_file->rest_content_ = nullptr;
    sav_file->rest_content_len_ = 0;
    while (file)
    {
        std::uint8_t c = fileread::read1Byte(file);
        if (!file)
        {
            break;
        }
        sav_file->rest_content_ = static_cast<char*>(realloc(sav_file->rest_content_,
            ++sav_file->rest_content_len_));
        sav_file->rest_content_[sav_file->rest_content_len_ - 1] = c;
    }

    file.close();
    return sav_file;
}

void SavFile::serialize(std::filesystem::path path)
{
    std::ofstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return;
    }

    // CRC32
    filewrite::write4ByteLsb(file, 0);
    filewrite::write1Byte(file, 0x06);
    filewrite::write4ByteLsb(file, header_.getIndex());
    filewrite::write1Byte(file, header_.getRoom());
    filewrite::write4ByteLsb(file, header_.getPlayTime());
    filewrite::write1Byte(file, header_.getTimesSaved());
    filewrite::write2ByteLsb(file, header_.getUk1());
    filewrite::write1Byte(file, header_.getDiffMode().getFlags());
    filewrite::write2ByteLsb(file, header_.getUk2());
    filewrite::write2ByteLsb(file, header_.getItemsCharactersLength());

    filewrite::write2ByteLsb(file, items_.getLength());
    int inventory_capacity = items_.getInventoryCapacity();
    filewrite::write1Byte(file, inventory_capacity);
    std::vector<SavInventoryElement>& items = items_.getItems();
    for (int i = 0; i < inventory_capacity; i++)
    {
        if (items.at(i).type == InventoryElementType::ITEM)
        {
            filewrite::write4ByteLsb(file, items.at(i).item.uid);
            filewrite::write1Byte(file, items.at(i).item.quantity);
            filewrite::write4ByteLsb(file, items.at(i).item.extra_info);
            continue;
        }

        filewrite::write1Byte(file, items.at(i).ammo.type);
        filewrite::write4ByteLsb(file, items.at(i).ammo.quantity_msb);
        filewrite::write4ByteLsb(file, items.at(i).ammo.quantity);
    }

    for (int i = 0; i < rest_content_len_; i++)
    {
        filewrite::write1Byte(file, rest_content_[i]);
    }

    file.close();
    SavFile::correctCrc32(path);
}

SavHeader& SavFile::getHeader()
{
    return header_;
}

SavItems& SavFile::getItems()
{
    return items_;
}

void SavFile::correctCrc32(std::filesystem::path path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return;
    }

    // we skip the first 4 bytes
    fileread::read4ByteMsb(file);
    std::uint32_t crc = utils::crc32(file);

    file.close();

    // TODO: do this in the C++ style
    std::string path_str = path.string();
    FILE* file_ptr = fopen(path_str.data(), "rb+");
    if (!file_ptr)
    {
        return;
    }

    unsigned char towrite[4] = {0};
    void *towrite_v = towrite;
    unsigned int *towrite_u = static_cast<unsigned int*>(towrite_v);
    towrite_u[0] = crc;

    fwrite(towrite, 1, 4, file_ptr);

    fclose(file_ptr);
    return;
}