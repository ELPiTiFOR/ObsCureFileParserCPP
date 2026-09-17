#include "hoe_file.hh"

#include <algorithm>
#include <iostream>

#include "fileread/fileread.hh"
#include "filewrite/filewrite.hh"
#include "utils/utils.hh"

/*
**  HOE CHUNK
*/

HoeChunk::HoeChunk(HoeChunkType chunk_type)
    : chunk_type_(chunk_type)
{}

HoeChunk::~HoeChunk()
{}

HoeChunkType HoeChunk::getChunkType()
{
    return chunk_type_;
}

/*
**  HOE CONSTANT
*/

HoeConstant::HoeConstant(std::int32_t int_value)
    : constant_type_(HoeConstantType::INT)
    , int_value_(int_value)
{}

HoeConstant::HoeConstant(float float_value)
    : constant_type_(HoeConstantType::FLOAT)
    , float_value_(float_value)
{}

HoeConstant::HoeConstant(const HoeConstant& other)
    : constant_type_(other.constant_type_)
    , int_value_(other.int_value_)
    , float_value_(other.float_value_)
{}

HoeConstant::HoeConstant(HoeConstantType constant_type)
    : constant_type_(constant_type)
{}

HoeConstantType HoeConstant::getConstantType() const
{
    return constant_type_;
}

std::int32_t HoeConstant::getIntValue() const
{
    return int_value_;
}

float HoeConstant::getFloatValue() const
{
    return float_value_;
}

void HoeConstant::setConstantType(HoeConstantType constant_type)
{
        constant_type_ = constant_type;
}

void HoeConstant::setIntValue(std::int32_t int_value)
{
    int_value_ = int_value;
}

void HoeConstant::setFloatValue(float float_value)
{
    float_value_ = float_value;
}

/*
**  HOE EVENT
*/

HoeEvent::HoeEvent()
    : HoeChunk(HoeChunkType::EVENT)
{}

void HoeEvent::parseHoeConstant(std::ifstream& file)
{
    HoeConstantType constant_type = static_cast<HoeConstantType>(
        fileread::read4ByteMsb(file)
    );

    HoeConstant constant(constant_type);

    if (constant_type == HoeConstantType::INT)
    {
        constant.setIntValue(fileread::read4ByteMsb(file));
    }
    else
    {
        constant.setFloatValue(fileread::readFloatMsb(file));
    }

    hoe_constants_.push_back(constant);
}

void HoeEvent::parseHoeScript(std::ifstream& file)
{
    CurrentEvent::setCurrentEvent(this);
    bool mask = !!fileread::read4ByteMsb(file);
    HoeScript* script = new HoeScript();
    if (mask)
    {
        script->parseHoeMask(file);
    }

    if (script->parseHoeScript(file))
    {
        auto pos = file.tellg();
        delete script;
        script = nullptr;
        auto debug_offset = DebugOffset::getOffset();
    }
    CurrentEvent::setCurrentEvent(nullptr);

    // script->setEvent(this);
    script_ = script;
}

std::string HoeEvent::getHoeVariableName(size_t index)
{
    std::vector<std::string> globals;
    globals.push_back("gCurrentState");
    globals.push_back("gCurrentSubState");
    globals.push_back("gIsAttacking");
    globals.push_back("delay");
    globals.push_back("gPlayerDetected");
    globals.push_back("isBlocked");
    globals.push_back("isMoving");
    globals.push_back("gCurrentMord");
    globals.push_back("gRunLighting");
    globals.push_back("gIsRespawn");
    globals.push_back("isTurning");
    globals.push_back("gPlayerDetectedSpec");
    globals.push_back("gKinState");
    globals.push_back("gCanFight");
    globals.push_back("gCamState");
    globals.push_back("gCanJump");
    globals.push_back("gIsAlive");
    globals.push_back("gHelpRespawn");
    globals.push_back("gCanBite");

    // We check all the globals in lstrings_ first
    int globals_in_lstrings = 0;
    for (std::string& lstring : lstrings_)
    {
        if (std::find(globals.begin(), globals.end(), lstring) != globals.end())
        {
            globals_in_lstrings++;
        }
    }

    if (lstrings_.size() != uk_int2_ + globals_in_lstrings)
    {
        return "";
    }

    size_t i = 0;
    for (std::string& lstring : lstrings_)
    {
        if (std::find(globals.begin(), globals.end(), lstring) != globals.end())
        {
            continue;
        }

        if (i == index)
        {
            return lstring;
        }

        i++;
    }

    return "";
}

HoeConstant* HoeEvent::getHoeConstant(size_t index)
{
    if (index >= hoe_constants_.size())
    {
        return nullptr;
    }

    return &(hoe_constants_.at(index));
}

float HoeEvent::getMagicNumber()
{
    return magic_number_;
}

std::string& HoeEvent::getName()
{
    return name_;
}

const std::string& HoeEvent::getName() const
{
    return name_;
}

std::uint32_t HoeEvent::getUkInt1() const
{
    return uk_int1_;
}

std::uint32_t HoeEvent::getUkInt2() const
{
    return uk_int2_;
}

std::uint32_t HoeEvent::getUkInt3() const
{
    return uk_int3_;
}

std::vector<std::uint32_t>& HoeEvent::getUkInts()
{
    return uk_ints_;
}

std::vector<std::string>& HoeEvent::getLStrings()
{
    return lstrings_;
}

std::vector<HoeConstant>& HoeEvent::getHoeConstants()
{
    return hoe_constants_;
}

std::vector<std::int32_t>& HoeEvent::getM1()
{
    return m1_;
}

const std::vector<std::uint32_t>& HoeEvent::getUkInts() const
{
    return uk_ints_;
}

const std::vector<std::string>& HoeEvent::getLStrings() const
{
    return lstrings_;
}

const std::vector<HoeConstant>& HoeEvent::getHoeConstants() const
{
    return hoe_constants_;
}

const std::vector<std::int32_t>& HoeEvent::getM1() const
{
    return m1_;
}

HoeScript* HoeEvent::getScript() const
{
    return script_;
}

void HoeEvent::setMagicNumber(float magic_number)
{
    magic_number_ = magic_number;
}

void HoeEvent::setName(std::string name)
{
    name_ = name;
}

void HoeEvent::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}

void HoeEvent::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}

void HoeEvent::setUkInt3(std::uint32_t uk_int3)
{
    uk_int3_ = uk_int3;
}

/*
**  HOE COLISSION CELL
*/

HoeCollisionCell::HoeCollisionCell(const HoeCollisionCell& other)
    : uk_int1_(other.uk_int1_)
    , uk_int2_(other.uk_int2_)
    , uk_float_(other.uk_float_)
    , flags_and_index_(other.flags_and_index_)
    , uk_byte1_(other.uk_byte1_)
    , uk_byte2_(other.uk_byte2_)
{}

std::uint32_t HoeCollisionCell::getUkInt1()
{
    return uk_int1_;
}

std::uint32_t HoeCollisionCell::getUkInt2()
{
    return uk_int2_;
}

float HoeCollisionCell::getUkFloat()
{
    return uk_float_;
}

size_t HoeCollisionCell::getIndex()
{
    return static_cast<size_t>(flags_and_index_ & 0x3FFF);
}

bool HoeCollisionCell::getUkBool1()
{
    return flags_and_index_ & 0x8000 != 0;
}

bool HoeCollisionCell::getUkBool2()
{
    return flags_and_index_ & 0x4000 != 0;
}
std::uint16_t HoeCollisionCell::getFlagsAndIndex()
{
    return flags_and_index_;
}

std::uint8_t HoeCollisionCell::getUkByte1()
{
    return uk_byte1_;
}

std::uint8_t HoeCollisionCell::getUkByte2()
{
    return uk_byte2_;
}

void HoeCollisionCell::setUkInt1(std::uint32_t  uk_int1)
{
    uk_int1_ = uk_int1;
}

void HoeCollisionCell::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}

void HoeCollisionCell::setUkFloat(float uk_float)
{
    uk_float_ = uk_float;
}

void HoeCollisionCell::setIndex(size_t index)
{
    if (index > 0x3FFF)
    {
        return;
    }

    // we only keep the flags
    flags_and_index_ &= 0xC000;

    // we apply the new index
    flags_and_index_ += index;
}

void HoeCollisionCell::setUkBool1(bool uk_bool1)
{
    flags_and_index_ ^= 0x8000;
}

void HoeCollisionCell::setUkBool2(bool uk_bool2)
{
    flags_and_index_ ^= 0x4000;
}

void HoeCollisionCell::setFlagsAndIndex(std::uint16_t flags_and_index)
{
    flags_and_index_ = flags_and_index;
}

void HoeCollisionCell::setUkByte1(std::uint8_t uk_byte1)
{
    uk_byte1_ = uk_byte1;
}

void HoeCollisionCell::setUkByte2(std::uint8_t uk_byte2)
{
    uk_byte2_ = uk_byte2;
}

/*
**  HOE COLLISIONS POST MAP
*/

HoeCollisionsPostMap::HoeCollisionsPostMap(const HoeCollisionsPostMap& other)
    : uk_int1_(other.uk_int1_)
    , uk_int2_(other.uk_int2_)
    , uk_int3_(other.uk_int3_)
    , uk_int4_(other.uk_int4_)
    , uk_int5_(other.uk_int5_)
    , uk_ints_(other.uk_ints_)
{}

std::uint32_t HoeCollisionsPostMap::getUkInt1()
{
    return uk_int1_;
}

std::uint32_t HoeCollisionsPostMap::getUkInt2()
{
    return uk_int2_;
}

std::uint32_t HoeCollisionsPostMap::getUkInt3()
{
    return uk_int3_;
}

std::uint32_t HoeCollisionsPostMap::getUkInt4()
{
    return uk_int4_;
}

std::uint32_t HoeCollisionsPostMap::getUkInt5()
{
    return uk_int5_;
}

std::vector<std::uint32_t>& HoeCollisionsPostMap::getUkInts()
{
    return uk_ints_;
}

void HoeCollisionsPostMap::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}

void HoeCollisionsPostMap::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}

void HoeCollisionsPostMap::setUkInt3(std::uint32_t uk_int3)
{
    uk_int3_ = uk_int3;
}

void HoeCollisionsPostMap::setUkInt4(std::uint32_t uk_int4)
{
    uk_int4_ = uk_int4;
}

void HoeCollisionsPostMap::setUkInt5(std::uint32_t uk_int5)
{
    uk_int5_ = uk_int5;
}

/*
**  HOE COLLISIONS MAP
*/

HoeCollisionsMap::HoeCollisionsMap(uint32_t index)
    : index_(index)
{}

HoeCollisionsMap::HoeCollisionsMap(const HoeCollisionsMap& other)
    : index_(other.index_)
    , cells_(other.cells_)
    , width_(other.width_)
    , height_(other.height_)
    , uk_float1_(other.uk_float1_)
    , uk_float2_(other.uk_float2_)
    , uk_float3_(other.uk_float3_)
    , uk_float4_(other.uk_float4_)
    , uk_float5_(other.uk_float5_)
    , uk_float6_(other.uk_float6_)
    , uk_float7_(other.uk_float7_)
    , uk_float8_(other.uk_float8_)
    , post_maps_(other.post_maps_)
{}

void HoeCollisionsMap::parseCollisionCell(std::ifstream& file)
{
    HoeCollisionCell cell;
    cell.setUkInt1(fileread::read4ByteLsb(file));
    cell.setUkInt2(fileread::read4ByteLsb(file));
    cell.setUkFloat(fileread::readFloatLsb(file));
    cell.setFlagsAndIndex(fileread::read2ByteLsb(file));
    cell.setUkByte1(fileread::read1Byte(file));
    cell.setUkByte2(fileread::read1Byte(file));
    cells_.push_back(cell);
}
void HoeCollisionsMap::parseCollisionsPostMap(std::ifstream& file)
{
    HoeCollisionsPostMap post_map;
    post_map.setUkInt1(fileread::read4ByteMsb(file));
    post_map.setUkInt2(fileread::read4ByteMsb(file));
    post_map.setUkInt3(fileread::read4ByteMsb(file));
    post_map.setUkInt4(fileread::read4ByteMsb(file));
    post_map.setUkInt5(fileread::read4ByteMsb(file));
    std::uint32_t nb_uk_ints = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_uk_ints; i++)
    {
        post_map.getUkInts().push_back(fileread::read4ByteMsb(file));
    }

    post_maps_.push_back(post_map);
}

std::uint32_t HoeCollisionsMap::getIndex()
{
    return index_;
}

std::uint32_t HoeCollisionsMap::getWidth()
{
    return width_;
}

std::uint32_t HoeCollisionsMap::getHeight()
{
    return height_;
}

float HoeCollisionsMap::getUkFloat1()
{
    return uk_float1_;
}

float HoeCollisionsMap::getUkFloat2()
{
    return uk_float2_;
}

float HoeCollisionsMap::getUkFloat3()
{
    return uk_float3_;
}

float HoeCollisionsMap::getUkFloat4()
{
    return uk_float4_;
}

float HoeCollisionsMap::getUkFloat5()
{
    return uk_float5_;
}

float HoeCollisionsMap::getUkFloat6()
{
    return uk_float6_;
}

float HoeCollisionsMap::getUkFloat7()
{
    return uk_float7_;
}

float HoeCollisionsMap::getUkFloat8()
{
    return uk_float8_;
}

// uint32_t HoeCollisionsMap::getNbCells()
// {
//     return nb_cells_;
// }

std::vector<HoeCollisionCell>& HoeCollisionsMap::getCells()
{
    return cells_;
}

void HoeCollisionsMap::setIndex(uint32_t index)
{
    index_ = index;
}

void HoeCollisionsMap::setWidth(uint32_t width)
{
    width_ = width;
}

void HoeCollisionsMap::setHeight(uint32_t height)
{
    height_ = height;
}

void HoeCollisionsMap::setUkFloat1(float uk_float1)
{
    uk_float1_ = uk_float1;
}

void HoeCollisionsMap::setUkFloat2(float uk_float2)
{
    uk_float2_ = uk_float2;
}

void HoeCollisionsMap::setUkFloat3(float uk_float3)
{
    uk_float3_ = uk_float3;
}

void HoeCollisionsMap::setUkFloat4(float uk_float4)
{
    uk_float4_ = uk_float4;
}

void HoeCollisionsMap::setUkFloat5(float uk_float5)
{
    uk_float5_ = uk_float5;
}

void HoeCollisionsMap::setUkFloat6(float uk_float6)
{
    uk_float6_ = uk_float6;
}

void HoeCollisionsMap::setUkFloat7(float uk_float7)
{
    uk_float7_ = uk_float7;
}

void HoeCollisionsMap::setUkFloat8(float uk_float8)
{
    uk_float8_ = uk_float8;
}

// void HoeCollisionsMap::setNbCells(uint32_t nb_cells)
// {
//     nb_cells_ = nb_cells;
// }

/*
** HOE POST COLLISIONS
*/

HoePostCollisions::HoePostCollisions(const HoePostCollisions& other)
    : uk_float1_(other.uk_float1_)
    , uk_float2_(other.uk_float2_)
    , uk_float3_(other.uk_float3_)
    , uk_float4_(other.uk_float4_)
    , uk_float5_(other.uk_float5_)
    , uk_float6_(other.uk_float6_)
{}

float HoePostCollisions::getUkFloat1() const
{
    return uk_float1_;
}

float HoePostCollisions::getUkFloat2() const
{
    return uk_float2_;
}

float HoePostCollisions::getUkFloat3() const
{
    return uk_float3_;
}

float HoePostCollisions::getUkFloat4() const
{
    return uk_float4_;
}

float HoePostCollisions::getUkFloat5() const
{
    return uk_float5_;
}

float HoePostCollisions::getUkFloat6() const
{
    return uk_float6_;
}

void HoePostCollisions::setUkFloat1(float uk_float)
{
    uk_float1_ = uk_float;
}

void HoePostCollisions::setUkFloat2(float uk_float)
{
    uk_float2_ = uk_float;
}

void HoePostCollisions::setUkFloat3(float uk_float)
{
    uk_float3_ = uk_float;
}

void HoePostCollisions::setUkFloat4(float uk_float)
{
    uk_float4_ = uk_float;
}

void HoePostCollisions::setUkFloat5(float uk_float)
{
    uk_float5_ = uk_float;
}

void HoePostCollisions::setUkFloat6(float uk_float)
{
    uk_float6_ = uk_float;
}

/*
**  HOE COLLISIONS
*/

HoeCollisions::HoeCollisions()
    : HoeChunk(HoeChunkType::COLLISIONS)
{}

std::uint32_t HoeCollisions::getLength()
{
    return length_;
}

std::uint32_t HoeCollisions::getUkInt1()
{
    return uk_int1_;
}


std::string& HoeCollisions::getRoomId()
{
    return room_id_;
}


std::uint32_t HoeCollisions::getUkInt2()
{
    return uk_int2_;
}


float HoeCollisions::getUkFloat1()
{
    return uk_float1_;
}


float HoeCollisions::getUkFloat2()
{
    return uk_float2_;
}


float HoeCollisions::getUkFloat3()
{
    return uk_float3_;
}

std::vector<HoeCollisionsMap>& HoeCollisions::getMaps()
{
    return maps_;
}

std::uint32_t HoeCollisions::getWidth()
{
    return width_;
}

std::uint32_t HoeCollisions::getHeight()
{
    return height_;
}

float HoeCollisions::getUkFloat4()
{
    return uk_float4_;
}

float HoeCollisions::getUkFloat5()
{
    return uk_float5_;
}

float HoeCollisions::getUkFloat6()
{
    return uk_float6_;
}

float HoeCollisions::getUkFloat7()
{
    return uk_float7_;
}

float HoeCollisions::getUkFloat8()
{
    return uk_float8_;
}

float HoeCollisions::getUkFloat9()
{
    return uk_float9_;
}

std::uint32_t HoeCollisions::getUkInt3()
{
    return uk_int3_;
}

std::uint32_t HoeCollisions::getUkInt4()
{
    return uk_int4_;
}

std::uint32_t HoeCollisions::getUkInt5()
{
    return uk_int5_;
}

std::uint32_t HoeCollisions::getUkInt6()
{
    return uk_int6_;
}

std::uint32_t HoeCollisions::getUkInt7()
{
    return uk_int7_;
}

std::uint32_t HoeCollisions::getUkInt8()
{
    return uk_int8_;
}

std::uint32_t HoeCollisions::getUkInt9()
{
    return uk_int9_;
}

std::vector<HoePostCollisions>& HoeCollisions::getPostCollisions()
{
    return post_collisions_;
}

const std::vector<HoePostCollisions>& HoeCollisions::getPostCollisions() const
{
    return post_collisions_;
}

void HoeCollisions::setLength(std::uint32_t length)
{
    length_ = length;
}

void HoeCollisions::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}

void HoeCollisions::setRoomId(std::string room_id)
{
    room_id_ = room_id;
}

void HoeCollisions::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}

void HoeCollisions::setUkFloat1(float uk_float1)
{
    uk_float1_ = uk_float1;
}

void HoeCollisions::setUkFloat2(float uk_float2)
{
    uk_float2_ = uk_float2;
}

void HoeCollisions::setUkFloat3(float uk_float3)
{
    uk_float3_ = uk_float3;
}

void HoeCollisions::setWidth(std::uint32_t width)
{
    width_ = width;
}

void HoeCollisions::setHeight(std::uint32_t height)
{
    height_ = height;
}

void HoeCollisions::setUkFloat4(float uk_float4)
{
    uk_float4_ = uk_float4;
}

void HoeCollisions::setUkFloat5(float uk_float5)
{
    uk_float5_ = uk_float5;
}

void HoeCollisions::setUkFloat6(float uk_float6)
{
    uk_float6_ = uk_float6;
}

void HoeCollisions::setUkFloat7(float uk_float7)
{
    uk_float7_ = uk_float7;
}

void HoeCollisions::setUkFloat8(float uk_float8)
{
    uk_float8_ = uk_float8;
}

void HoeCollisions::setUkFloat9(float uk_float9)
{
    uk_float9_ = uk_float9;
}

void HoeCollisions::setUkInt3(std::uint32_t uk_int3)
{
    uk_int3_ = uk_int3;
}

void HoeCollisions::setUkInt4(std::uint32_t uk_int4)
{
    uk_int4_ = uk_int4;
}

void HoeCollisions::setUkInt5(std::uint32_t uk_int5)
{
    uk_int5_ = uk_int5;
}

void HoeCollisions::setUkInt6(std::uint32_t uk_int6)
{
    uk_int6_ = uk_int6;
}

void HoeCollisions::setUkInt7(std::uint32_t uk_int7)
{
    uk_int7_ = uk_int7;
}

void HoeCollisions::setUkInt8(std::uint32_t uk_int8)
{
    uk_int8_ = uk_int8;
}

void HoeCollisions::setUkInt9(std::uint32_t uk_int9)
{
    uk_int9_ = uk_int9;
}


void HoeCollisions::parseCollisionsMap(std::ifstream& file)
{
    uint32_t index = fileread::read4ByteMsb(file);
    HoeCollisionsMap map(index);

    uint32_t nb_cells = fileread::read4ByteMsb(file);
    for (uint32_t i = 0; i < nb_cells; i++)
    {
        map.parseCollisionCell(file);
    }

    // TODO: finish this
    map.setWidth(fileread::read4ByteMsb(file));
    map.setHeight(fileread::read4ByteMsb(file));
    map.setUkFloat1(fileread::readFloatMsb(file));
    map.setUkFloat2(fileread::readFloatMsb(file));
    map.setUkFloat3(fileread::readFloatMsb(file));
    map.setUkFloat4(fileread::readFloatMsb(file));
    map.setUkFloat5(fileread::readFloatMsb(file));
    map.setUkFloat6(fileread::readFloatMsb(file));
    map.setUkFloat7(fileread::readFloatMsb(file));
    map.setUkFloat8(fileread::readFloatMsb(file));

    for (int i = 0; i < 4; i++)
    {
        map.parseCollisionsPostMap(file);
    }

    maps_.push_back(map);
}

/*
**  HOE FILE
*/

void HoeFile::parseCollisions(std::ifstream& file)
{
    auto collisions_chunk = new HoeCollisions();

    collisions_chunk->setLength(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt1(fileread::read4ByteMsb(file));
    collisions_chunk->setRoomId(fileread::readLString(file));
    collisions_chunk->setUkInt2(fileread::read4ByteMsb(file));
    collisions_chunk->setUkFloat1(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat2(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat3(fileread::readFloatMsb(file));
    std::uint32_t nb_maps = fileread::read4ByteMsb(file);

    for (std::uint32_t i = 0; i < nb_maps; i++)
    {
        collisions_chunk->parseCollisionsMap(file);
    }

    collisions_chunk->setWidth(fileread::read4ByteMsb(file));
    collisions_chunk->setHeight(fileread::read4ByteMsb(file));
    collisions_chunk->setUkFloat4(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat5(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat6(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat7(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat8(fileread::readFloatMsb(file));
    collisions_chunk->setUkFloat9(fileread::readFloatMsb(file));
    collisions_chunk->setUkInt3(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt4(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt5(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt6(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt7(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt8(fileread::read4ByteMsb(file));
    collisions_chunk->setUkInt9(fileread::read4ByteMsb(file));
    std::uint32_t nb_post_collisions = fileread::read4ByteMsb(file);

    for (std::uint32_t i = 0; i < nb_post_collisions; i++)
    {
        HoePostCollisions post_collisions;
        post_collisions.setUkFloat1(fileread::readFloatMsb(file));
        post_collisions.setUkFloat2(fileread::readFloatMsb(file));
        post_collisions.setUkFloat3(fileread::readFloatMsb(file));
        post_collisions.setUkFloat4(fileread::readFloatMsb(file));
        post_collisions.setUkFloat5(fileread::readFloatMsb(file));
        post_collisions.setUkFloat6(fileread::readFloatMsb(file));
        collisions_chunk->getPostCollisions().push_back(post_collisions);
    }

    chunks_.push_back(collisions_chunk);
}

int HoeFile::parseEvent(std::ifstream& file)
{
    auto event_chunk = new HoeEvent();

    event_chunk->setMagicNumber(fileread::readFloatMsb(file));
    event_chunk->setName(fileread::readLString(file));
    event_chunk->setUkInt1(fileread::read4ByteMsb(file));
    event_chunk->setUkInt2(fileread::read4ByteMsb(file));
    event_chunk->setUkInt3(fileread::read4ByteMsb(file));
    std::uint32_t nb_uk_ints = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_uk_ints; i++)
    {
        event_chunk->getUkInts().push_back(fileread::read4ByteMsb(file));
    }

    std::uint32_t nb_lstrings = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_lstrings; i++)
    {
        event_chunk->getLStrings().push_back(fileread::readLString(file));
    }

    std::uint32_t nb_constants = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_constants; i++)
    {
        event_chunk->parseHoeConstant(file);
    }

    std::uint32_t nb_m1 = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_m1; i++)
    {
        event_chunk->getM1().push_back(fileread::read4ByteMsb(file));
    }

    event_chunk->parseHoeScript(file);

    if (event_chunk->getScript() == nullptr)
    {
        return 1;
    }

    chunks_.push_back(event_chunk);
    return 0;
}

// TODO: return nullptr if the parsing of a chunk fails
HoeFile* HoeFile::makeFile(std::filesystem::path path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return nullptr;
    }

    auto hoe_file = new HoeFile();

    hoe_file->magic_number_ = fileread::readFloatMsb(file);

    uint32_t chunk_type_u = fileread::read4ByteMsb(file);
    HoeChunkType next_chunk_type = static_cast<HoeChunkType>(chunk_type_u);
    // For now we are going to skip certain sections
    std::uint32_t to_skip = 0;
    while (next_chunk_type != HoeChunkType::END)
    {
        switch (next_chunk_type)
        {
        case HoeChunkType::COLLISIONS:
            hoe_file->parseCollisions(file);
            break;
        case HoeChunkType::IMPORTS:
            // For now, we skip the IMPORTS section
            to_skip = fileread::read4ByteMsb(file);
            fileread::skipBytes(file, to_skip - 4);
            break;
        case HoeChunkType::EVENT:
            if (hoe_file->parseEvent(file))
            {
                file.close();
                delete hoe_file;
                return nullptr;
            }
            break;
        case HoeChunkType::INSTANCE:
            // For now, we skip the INSTANCE sections
            // We skip the first byte in order to access the length of the
            // instance
            fileread::read1Byte(file);
            to_skip = fileread::read4ByteMsb(file);
            fileread::skipBytes(file, to_skip - 4);
            break;
        default:
            file.close();
            // return hoe_file;
            return nullptr;
        }
        chunk_type_u = fileread::read4ByteMsb(file);
        next_chunk_type = static_cast<HoeChunkType>(chunk_type_u);
    }

    file.close();
    return hoe_file;
}

float HoeFile::getMagicNumber() const
{
    return magic_number_;
}

std::vector<HoeChunk*>& HoeFile::getChunks()
{
    return chunks_;
}

const std::vector<HoeChunk*>& HoeFile::getChunks() const
{
    return chunks_;
}

HoeCollisions* HoeFile::getCollisions()
{
    for (HoeChunk* chunk: chunks_)
    {
        HoeCollisions* collisions = static_cast<HoeCollisions*>(chunk);
        if (collisions)
        {
            return collisions;
        }
    }

    return nullptr;
}

HoeEvent* HoeFile::getEvent(const std::string& name)
{
    for (HoeChunk* chunk: chunks_)
    {
        HoeEvent* event = static_cast<HoeEvent*>(chunk);
        if (event && event->getName() == name)
        {
            return event;
        }
    }

    return nullptr;
}

/*
** << OPERATOR
*/

std::ostream& operator<<(std::ostream& os, const HoeFile& hoe_file)
{
    os << "HoeFile {" << std::endl;
    Indent::increaseIndent();

    Indent::printIndent(os);
    os << "MagicNumber: " << hoe_file.getMagicNumber() << std::endl;

    if (hoe_file.getChunks().size() != 0)
    {
        for (HoeChunk* chunk : hoe_file.getChunks())
        {
            Indent::printIndent(os);
            os << *chunk << std::endl;
        }
    }

    Indent::decreaseIndent();
    Indent::printIndent(os);
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeCollisions& collisions)
{
    os << "[Check .ppm file]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeCollisionsMap& map)
{
    return os;
}

std::ostream& operator<<(std::ostream& os,
    const HoeCollisionsPostMap& post_map)
{
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeCollisionCell& cell)
{
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeEvent& event)
{
    os << "HoeEvent " << event.getName() << " {" << std::endl;
    Indent::increaseIndent();

    Indent::printIndent(os);
    os << "UkInt1: " << event.getUkInt1() << std::endl;
    Indent::printIndent(os);
    os << "UkInt2: " << event.getUkInt2() << std::endl;
    Indent::printIndent(os);
    os << "UkInt3: " << event.getUkInt3() << std::endl;

    if (event.getUkInts().size() != 0)
    {
        Indent::printIndent(os);
        os << "UkInts:" << std::endl;
        Indent::increaseIndent();
        for (std::uint32_t uk_int : event.getUkInts())
        {
            Indent::printIndent(os);
            os << uk_int << std::endl;
        }
        Indent::decreaseIndent();
    }

    if (event.getLStrings().size() != 0)
    {
        Indent::printIndent(os);
        os << "LStrings:" << std::endl;
        Indent::increaseIndent();
        for (std::string lstring : event.getLStrings())
        {
            Indent::printIndent(os);
            os << lstring << std::endl;
        }
        Indent::decreaseIndent();
    }

    if (event.getHoeConstants().size() != 0)
    {
        Indent::printIndent(os);
        os << "HoeConstants:" << std::endl;
        Indent::increaseIndent();
        // TODO: isn't this dirty? to copy the constants instead of taking
        // just the reference
        for (HoeConstant constant : event.getHoeConstants())
        {
            Indent::printIndent(os);
            os << constant << std::endl;
        }
        Indent::decreaseIndent();
    }

    if (event.getM1().size() != 0)
    {
        Indent::printIndent(os);
        os << "M1:" << std::endl;
        Indent::increaseIndent();
        for (std::int32_t m1 : event.getM1())
        {
            Indent::printIndent(os);
            os << m1 << std::endl;
        }
        Indent::decreaseIndent();
    }

    if (event.getScript())
    {
        Indent::printIndent(os);
        os << "Script:" << std::endl;
        Indent::increaseIndent();
        Indent::printIndent(os);
        os << *(event.getScript()) << std::endl;
        Indent::decreaseIndent();
    }

    Indent::decreaseIndent();
    Indent::printIndent(os);
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeConstant& constant)
{
    if (constant.getConstantType() == HoeConstantType::INT)
    {
        os << constant.getIntValue();
        return os;
    }

    os << constant.getFloatValue();
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeChunk& chunk)
{
    const HoeEvent* event = dynamic_cast<const HoeEvent*>(&chunk);
    if (event)
    {
        os << *event;
        return os;
    }

    const HoeCollisions* collisions = dynamic_cast<const HoeCollisions*>(
        &chunk
    );
    if (collisions)
    {
        os << *collisions;
        return os;
    }

    return os;
}
