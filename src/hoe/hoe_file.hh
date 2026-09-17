#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "hoe_script.hh"

enum class HoeChunkType
{
    COLLISIONS = 0x02,
    IMPORTS = 0x03,
    END = 0x04,
    EVENT = 0x05,
    INSTANCE = 0x06,
};

class HoeChunk
{
public:
    HoeChunk(HoeChunkType chunk_type);
    virtual ~HoeChunk();
    HoeChunkType getChunkType();
private:
    HoeChunkType chunk_type_;
};

enum class HoeConstantType
{
    INT = 0x1,
    FLOAT = 0x2
};

class HoeConstant
{
public:
    HoeConstant() = default;
    HoeConstant(float float_value);
    HoeConstant(std::uint32_t int_value);
    HoeConstant(HoeConstantType constant_type);
    HoeConstant(const HoeConstant& other);
    HoeConstantType getConstantType() const;
    std::uint32_t getIntValue() const;
    float getFloatValue() const;

    void setConstantType(HoeConstantType constant_type);
    void setIntValue(std::uint32_t int_value);
    void setFloatValue(float float_value);
private:
    HoeConstantType constant_type_;
    std::uint32_t int_value_;
    float float_value_;
};

class HoeEvent : public HoeChunk
{
public:
    HoeEvent();
    void parseHoeConstant(std::ifstream& file);
    void parseHoeScript(std::ifstream& file);
    std::string getHoeVariableName(size_t index);
    HoeConstant* getHoeConstant(size_t index);
    float getMagicNumber();
    std::string& getName();
    const std::string& getName() const;
    std::uint32_t getUkInt1() const;
    std::uint32_t getUkInt2() const;
    std::uint32_t getUkInt3() const;
    std::vector<std::uint32_t>& getUkInts();
    std::vector<std::string>& getLStrings();
    std::vector<HoeConstant>& getHoeConstants();
    std::vector<std::uint32_t>& getM1();
    const std::vector<std::uint32_t>& getUkInts() const;
    const std::vector<std::string>& getLStrings() const;
    const std::vector<HoeConstant>& getHoeConstants() const;
    const std::vector<std::uint32_t>& getM1() const;
    HoeScript* getScript() const;

    void setMagicNumber(float magic_number);
    void setName(std::string name);
    void setUkInt1(std::uint32_t uk_int1);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkInt3(std::uint32_t uk_int3);
private:
    float magic_number_;
    std::string name_;
    std::uint32_t uk_int1_;
    std::uint32_t uk_int2_;
    std::uint32_t uk_int3_;
    std::vector<std::uint32_t> uk_ints_;
    std::vector<std::string> lstrings_;
    std::vector<HoeConstant> hoe_constants_;
    std::vector<std::uint32_t> m1_;
    HoeScript* script_;
};

class HoeCollisionCell
{
public:
    HoeCollisionCell() = default;
    HoeCollisionCell(const HoeCollisionCell& other);
    std::uint32_t getUkInt1();
    std::uint32_t getUkInt2();
    float getUkFloat();
    size_t getIndex();
    bool getUkBool1();
    bool getUkBool2();
    std::uint16_t getFlagsAndIndex();
    std::uint8_t getUkByte1();
    std::uint8_t getUkByte2();

    void setUkInt1(std::uint32_t  uk_int1);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkFloat(float uk_float);
    void setIndex(size_t index);
    void setUkBool1(bool uk_bool1);
    void setUkBool2(bool uk_bool2);
    void setFlagsAndIndex(std::uint16_t flags_and_index);
    void setUkByte1(std::uint8_t uk_byte1);
    void setUkByte2(std::uint8_t uk_byte2);
private:
    uint32_t uk_int1_;
    uint32_t uk_int2_;
    float uk_float_;
    uint16_t flags_and_index_;
    uint8_t uk_byte1_;
    uint8_t uk_byte2_;
};

class HoeCollisionsPostMap
{
public:
    HoeCollisionsPostMap() = default;
    HoeCollisionsPostMap(const HoeCollisionsPostMap& other);
    std::uint32_t getUkInt1();
    std::uint32_t getUkInt2();
    std::uint32_t getUkInt3();
    std::uint32_t getUkInt4();
    std::uint32_t getUkInt5();
    std::vector<std::uint32_t>& getUkInts();

    void setUkInt1(std::uint32_t uk_int1);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkInt3(std::uint32_t uk_int3);
    void setUkInt4(std::uint32_t uk_int4);
    void setUkInt5(std::uint32_t uk_int5);
private:
    std::uint32_t uk_int1_;
    std::uint32_t uk_int2_;
    std::uint32_t uk_int3_;
    std::uint32_t uk_int4_;
    std::uint32_t uk_int5_;
    std::vector<std::uint32_t> uk_ints_;
};

class HoeCollisionsMap
{
public:
    HoeCollisionsMap(uint32_t index);
    HoeCollisionsMap(const HoeCollisionsMap& other);
    void parseCollisionCell(std::ifstream& file);
    void parseCollisionsPostMap(std::ifstream& file);
    std::uint32_t getIndex();
    std::uint32_t getWidth();
    std::uint32_t getHeight();
    float getUkFloat1();
    float getUkFloat2();
    float getUkFloat3();
    float getUkFloat4();
    float getUkFloat5();
    float getUkFloat6();
    float getUkFloat7();
    float getUkFloat8();
    std::vector<HoeCollisionCell>& getCells();

    void setIndex(std::uint32_t index);
    void setWidth(std::uint32_t width);
    void setHeight(std::uint32_t height);
    void setUkFloat1(float uk_float1);
    void setUkFloat2(float uk_float2);
    void setUkFloat3(float uk_float3);
    void setUkFloat4(float uk_float4);
    void setUkFloat5(float uk_float5);
    void setUkFloat6(float uk_float6);
    void setUkFloat7(float uk_float7);
    void setUkFloat8(float uk_float8);
private:
    std::uint32_t index_;
    std::vector<HoeCollisionCell> cells_;
    std::uint32_t width_;
    std::uint32_t height_;
    float uk_float1_;
    float uk_float2_;
    float uk_float3_;
    float uk_float4_;
    float uk_float5_;
    float uk_float6_;
    float uk_float7_;
    float uk_float8_;
    std::vector<HoeCollisionsPostMap> post_maps_;
};

// This is a struct/class that takes 0x18 bytes (24 bytes)
class HoePostCollisions
{
public:
    HoePostCollisions() = default;
    HoePostCollisions(const HoePostCollisions& other);
    float getUkFloat1() const;
    float getUkFloat2() const;
    float getUkFloat3() const;
    float getUkFloat4() const;
    float getUkFloat5() const;
    float getUkFloat6() const;

    void setUkFloat1(float uk_float);
    void setUkFloat2(float uk_float);
    void setUkFloat3(float uk_float);
    void setUkFloat4(float uk_float);
    void setUkFloat5(float uk_float);
    void setUkFloat6(float uk_float);
private:
    float uk_float1_;
    float uk_float2_;
    float uk_float3_;
    float uk_float4_;
    float uk_float5_;
    float uk_float6_;
};

class HoeCollisions : public HoeChunk
{
public:
    HoeCollisions();
    void parseCollisionsMap(std::ifstream& file);
    std::uint32_t getLength();
    std::uint32_t getUkInt1();
    std::string& getRoomId();
    std::uint32_t getUkInt2();
    float getUkFloat1();
    float getUkFloat2();
    float getUkFloat3();
    std::vector<HoeCollisionsMap>& getMaps();

    std::uint32_t getWidth();
    std::uint32_t getHeight();
    float getUkFloat4();
    float getUkFloat5();
    float getUkFloat6();
    float getUkFloat7();
    float getUkFloat8();
    float getUkFloat9();
    std::uint32_t getUkInt3();
    std::uint32_t getUkInt4();
    std::uint32_t getUkInt5();
    std::uint32_t getUkInt6();
    std::uint32_t getUkInt7();
    std::uint32_t getUkInt8();
    std::uint32_t getUkInt9();
    std::vector<HoePostCollisions>& getPostCollisions();
    const std::vector<HoePostCollisions>& getPostCollisions() const;

    void setLength(std::uint32_t length);
    void setUkInt1(std::uint32_t uk_int1);
    void setRoomId(std::string room_id);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkFloat1(float uk_float1);
    void setUkFloat2(float uk_float2);
    void setUkFloat3(float uk_float3);

    void setWidth(std::uint32_t width);
    void setHeight(std::uint32_t height);
    void setUkFloat4(float uk_float4);
    void setUkFloat5(float uk_float5);
    void setUkFloat6(float uk_float6);
    void setUkFloat7(float uk_float7);
    void setUkFloat8(float uk_float8);
    void setUkFloat9(float uk_float9);
    void setUkInt3(std::uint32_t uk_int3);
    void setUkInt4(std::uint32_t uk_int4);
    void setUkInt5(std::uint32_t uk_int5);
    void setUkInt6(std::uint32_t uk_int6);
    void setUkInt7(std::uint32_t uk_int7);
    void setUkInt8(std::uint32_t uk_int8);
    void setUkInt9(std::uint32_t uk_int9);
private:
    std::uint32_t length_;
    std::uint32_t uk_int1_;
    std::string room_id_;
    std::uint32_t uk_int2_;
    float uk_float1_;
    float uk_float2_;
    float uk_float3_;
    // TODO: remove nb_maps_
    std::vector<HoeCollisionsMap> maps_;

    std::uint32_t width_;
    std::uint32_t height_;
    float uk_float4_;
    float uk_float5_;
    float uk_float6_;
    float uk_float7_;
    float uk_float8_;
    float uk_float9_;
    std::uint32_t uk_int3_;
    std::uint32_t uk_int4_;
    std::uint32_t uk_int5_;
    std::uint32_t uk_int6_;
    std::uint32_t uk_int7_;
    std::uint32_t uk_int8_;
    std::uint32_t uk_int9_;
    std::vector<HoePostCollisions> post_collisions_;
};

class HoeFile
{
public:
    HoeFile() = default;
    static HoeFile* makeFile(std::filesystem::path path);
    float getMagicNumber() const;
    std::vector<HoeChunk*>& getChunks();
    const std::vector<HoeChunk*>& getChunks() const;
    HoeCollisions* getCollisions();
    HoeEvent* getEvent(const std::string& name);
private:
    float magic_number_;
    std::vector<HoeChunk*> chunks_;
    void parseCollisions(std::ifstream& file);
    int parseEvent(std::ifstream& file);
};

std::ostream& operator<<(std::ostream& os, const HoeFile& hoe_file);
std::ostream& operator<<(std::ostream& os, const HoeCollisions& collisions);
std::ostream& operator<<(std::ostream& os, const HoeCollisionsMap& map);
std::ostream& operator<<(std::ostream& os,
    const HoeCollisionsPostMap& post_map);
std::ostream& operator<<(std::ostream& os, const HoeCollisionCell& cell);
std::ostream& operator<<(std::ostream& os, const HoeEvent& event);
std::ostream& operator<<(std::ostream& os, const HoeConstant& constant);
std::ostream& operator<<(std::ostream& os, const HoeChunk& chunk);