#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "hoe_script.hh"
#include "ppm/ppm_file.hh"

enum class HoeChunkType
{
    COLLISIONS = 0x02,
    IMPORTS = 0x03,
    END = 0x04,
    EVENT = 0x05,
    INSTANCE = 0x06,
};

enum class HoeConstantType
{
    INT = 0x1,
    FLOAT = 0x2
};

enum class HoeImportsType
{
    ONE = 0x5,
    TWO = 0x7,
};

class HoeConstant
{
public:
    HoeConstant() = default;
    HoeConstant(float float_value);
    HoeConstant(std::int32_t int_value);
    HoeConstant(HoeConstantType constant_type);
    HoeConstant(const HoeConstant& other);
    void serialize(std::ofstream& file);
    HoeConstantType getConstantType() const;
    std::int32_t getIntValue() const;
    float getFloatValue() const;

    void setConstantType(HoeConstantType constant_type);
    void setIntValue(std::int32_t int_value);
    void setFloatValue(float float_value);
private:
    HoeConstantType constant_type_;
    std::int32_t int_value_;
    float float_value_;
};

class HoeChunk
{
public:
    HoeChunk(HoeChunkType chunk_type);
    virtual ~HoeChunk();
    virtual void serialize(std::ofstream& file) = 0;
    HoeChunkType getChunkType();
protected:
    HoeChunkType chunk_type_;
};

class HoeInstanceEvent
{
public:
    HoeInstanceEvent();
    HoeInstanceEvent(const HoeInstanceEvent& other);
    void serialize(std::ofstream& file);
    std::uint32_t getLen() const;
    std::uint32_t getUkInt1() const;
    std::string getName() const;
    std::vector<HoeConstant>& getConstants();

    void setLen(std::uint32_t le);
    void setUkInt1(std::uint32_t uk_int1);
    void setName(std::string name);
private:
    std::uint32_t len_;
    std::uint32_t uk_int1_;
    std::string name_;
    std::vector<HoeConstant> constants_;
};

class HoeInstanceGlobal
{
public:
    HoeInstanceGlobal();
    HoeInstanceGlobal(const HoeInstanceGlobal& other);
    void serialize(std::ofstream& file);
    std::string getName() const;
    std::uint32_t getUkInt1() const;
    std::uint32_t getUkInt2() const;

    void setName(std::string name);
    void setUkInt1(std::uint32_t uk_int);
    void setUkInt2(std::uint32_t uk_int);
private:
    std::string name_;
    std::uint32_t uk_int1_; // type of var?
    std::uint32_t uk_int2_; // value of var?
};

class HoePostInstance
{
public:
    HoePostInstance();
    void serialize(std::ofstream& file);
    std::uint32_t getUkInt1() const;
    std::uint32_t getUkInt2() const;
    float getUkFloat1() const;
    float getUkFloat2() const;
    float getUkFloat3() const;
    float getUkFloat4() const;
    std::uint32_t getUkInt3() const;
    float getUkFloat5() const;
    std::uint32_t getUkInt4() const;
    std::uint32_t getUkInt5() const;

    void setUkInt1(std::uint32_t uk_int1);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkFloat1(float uk_float1);
    void setUkFloat2(float uk_float2);
    void setUkFloat3(float uk_float3);
    void setUkFloat4(float uk_float4);
    void setUkInt3(std::uint32_t uk_int3);
    void setUkFloat5(float uk_float5);
    void setUkInt4(std::uint32_t uk_int4);
    void setUkInt5(std::uint32_t uk_int5);
private:
    std::uint32_t uk_int1_;
    std::uint32_t uk_int2_;
    float uk_float1_;
    float uk_float2_;
    float uk_float3_;
    float uk_float4_;
    std::uint32_t uk_int3_;
    float uk_float5_;
    std::uint32_t uk_int4_;
    std::uint32_t uk_int5_;
};

class HoeInstance : public HoeChunk
{
public:
    HoeInstance();
    void serialize(std::ofstream& file);
    std::uint8_t getUkByte1() const;
    std::uint32_t getLength() const;
    std::uint32_t getUkInt1() const;
    std::string getName() const;
    std::string getEventType() const;
    std::string getParams() const;
    std::uint32_t getUkInt2() const;
    std::uint32_t getLenUntilCoord() const;
    std::uint32_t getUkInt3() const;
    bool getIsThereRoomString() const;
    bool getIsTherePNJString() const;
    bool getIsThereScriptString() const;
    std::vector<std::string>& getLStrings();
    std::vector<HoeInstanceEvent>& getEvents();
    std::uint32_t getUkInt4() const;
    std::vector<HoeInstanceGlobal>& getGlobals();
    float getX() const;
    float getY() const;
    float getZ() const;
    float getUkFloat1() const;
    float getUkFloat2() const;
    std::uint32_t getUkInt5() const;
    float getHealth() const;
    float getMaxHealth() const;
    std::uint32_t getUkInt6() const;
    std::uint32_t getUkInt7() const;
    std::uint32_t getUkInt8() const;
    float getRadius() const;
    float getUkFloat3() const;
    std::uint32_t getIsTherePostInstance() const;
    HoePostInstance& getPostInstance();

    void setUkByte1(std::uint8_t uk_byte1);
    void setLength(std::uint32_t length);
    void setUkInt1(std::uint32_t uk_int1);
    void setName(std::string name);
    void setEventType(std::string event_type);
    void setParams(std::string params);
    void setUkInt2(std::uint32_t uk_int2);
    void setLenUntilCoord(std::uint32_t len_until_coord);
    void setUkInt3(std::uint32_t uk_int3);
    void setUkInt4(std::uint32_t uk_int4);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setUkFloat1(float uk_float1);
    void setUkFloat2(float uk_float2);
    void setUkInt5(std::uint32_t uk_int5);
    void setHealth(float health);
    void setMaxHealth(float max_health);
    void setUkInt6(std::uint32_t uk_int6);
    void setUkInt7(std::uint32_t uk_int7);
    void setUkInt8(std::uint32_t uk_int8);
    void setRadius(float radius);
    void setUkFloat3(float uk_float3);
    void setIsTherePostInstance(std::uint32_t is_there_post_instance);
private:
    std::uint8_t uk_byte1_;
    std::uint32_t length_;
    std::uint32_t uk_int1_; // 0x17/0x1F
    std::string name_;
    std::string event_type_;
    std::string params_;
    std::uint32_t uk_int2_; // 1
    std::uint32_t len_until_coord_;
    std::uint32_t uk_int3_;
    std::vector<std::string> lstrings_;
    std::vector<HoeInstanceEvent> events_;
    std::uint32_t uk_int4_; // 1
    std::vector<HoeInstanceGlobal> globals_;
    float x_;
    float y_;
    float z_;
    float uk_float1_;
    float uk_float2_;
    std::uint32_t uk_int5_;
    float health_; // ?
    float max_health_; // ?
    std::uint32_t uk_int6_;
    std::uint32_t uk_int7_; // 0x19
    std::uint32_t uk_int8_; // 1 or 3
    float radius_; // ?
    float uk_float3_;
    std::uint32_t is_there_post_instance_;
    HoePostInstance post_instance_;
};

class HoePostImports
{
public:
    HoePostImports();
    HoePostImports(const HoePostImports& other);
    void parse(std::ifstream& file);
    void serialize(std::ofstream& file);
    std::uint32_t getLength();
    std::uint32_t getUkInt1();
    std::uint32_t getUkInt2();
    std::uint32_t getUkInt3();
    std::string getLString();
    std::uint32_t getUkInt4();
    std::uint32_t getUkInt5();
    std::uint32_t getUkInt6();

    void setLength(std::uint32_t length);
    void setUkInt1(std::uint32_t uk_int1);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkInt3(std::uint32_t uk_int3);
    void setLString(std::string lstring);
    void setUkInt4(std::uint32_t uk_int4);
    void setUkInt5(std::uint32_t uk_int5);
    void setUkInt6(std::uint32_t uk_int6);
private:
    std::uint32_t length_;
    std::uint32_t uk_int1_;
    std::uint32_t uk_int2_;
    std::uint32_t uk_int3_;
    std::string lstring_;
    std::uint32_t uk_int4_;
    std::uint32_t uk_int5_;
    std::uint32_t uk_int6_;
};

class HoeImports : public HoeChunk
{
public:
    HoeImports();
    void serialize(std::ofstream& file);
    std::uint32_t getLength();
    HoeImportsType getImportsType();
    std::vector<std::string>& getLStrings();
    std::vector<HoePostImports>& getPostImports();

    void setLength(std::uint32_t length);
    void setImportsType(HoeImportsType post_imports);
private:
    std::uint32_t length_;
    HoeImportsType imports_type_;
    std::vector<std::string> lstrings_;
    std::vector<HoePostImports> post_imports_;
};

class HoeEvent : public HoeChunk
{
public:
    HoeEvent();
    ~HoeEvent();
    void parseHoeConstant(std::ifstream& file);
    void parseHoeScript(std::ifstream& file);
    void serialize(std::ofstream& file);
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
    std::vector<std::int32_t>& getM1();
    const std::vector<std::uint32_t>& getUkInts() const;
    const std::vector<std::string>& getLStrings() const;
    const std::vector<HoeConstant>& getHoeConstants() const;
    const std::vector<std::int32_t>& getM1() const;
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
    std::vector<std::int32_t> m1_;
    HoeScript* script_;
};

class HoeCollisionCell
{
public:
    HoeCollisionCell() = default;
    HoeCollisionCell(const HoeCollisionCell& other);
    void serialize(std::ofstream& file);
    PpmPixel getPixelByFlags();
    PpmPixel getPixelByIndex();
    PpmPixel getPixelByUkShort2();
    PpmPixel getPixelByUkInt2();
    PpmPixel getPixelByUkFloat();
    PpmPixel getPixelByUkByte1();
    std::uint16_t getUkShort1() const;
    std::uint16_t getUkShort2() const;
    std::uint32_t getUkInt2();
    float getUkFloat();
    size_t getIndex();
    bool getUkBool1();
    bool getUkBool2();
    std::uint16_t getFlagsAndIndex();
    std::uint8_t getUkByte1();
    std::uint8_t getUkByte2();

    void setUkShort1(std::uint16_t uk_short1);
    void setUkShort2(std::uint16_t uk_short2);
    void setUkInt2(std::uint32_t uk_int2);
    void setUkFloat(float uk_float);
    void setIndex(size_t index);
    void setUkBool1(bool uk_bool1);
    void setUkBool2(bool uk_bool2);
    void setFlagsAndIndex(std::uint16_t flags_and_index);
    void setUkByte1(std::uint8_t uk_byte1);
    void setUkByte2(std::uint8_t uk_byte2);
private:
    uint16_t uk_short1_;
    // Might correspond to the Z index, how far from the floor it is
    uint16_t uk_short2_;
    uint32_t uk_int2_;
    // Weird stuff that looks similar to other weird stuff (lighting?)
    float uk_float_;
    uint16_t flags_and_index_;
    // Sometimes it looks like the collisions, sometimes it's weird stuff
    uint8_t uk_byte1_;
    uint8_t uk_byte2_;
};

class HoeCollisionsPostMap
{
public:
    HoeCollisionsPostMap() = default;
    HoeCollisionsPostMap(const HoeCollisionsPostMap& other);
    void serialize(std::ofstream& file);
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
    void serialize(std::ofstream& file);
    std::uint32_t getMaxUkShort2();
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
    void serialize(std::ofstream& file);
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
    void serialize(std::ofstream& file);
    std::uint32_t getLength();
    std::uint32_t getUkInt1();
    std::string getRoomId();
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
    ~HoeFile();
    static HoeFile* makeFile(std::filesystem::path path);
    void serialize(std::filesystem::path path);
    int extractCollisionsMaps(std::filesystem::path path);
    int modifyCollisionsMap(std::filesystem::path ppm_path, size_t index);
    float getMagicNumber() const;
    std::vector<HoeChunk*>& getChunks();
    const std::vector<HoeChunk*>& getChunks() const;
    HoeCollisions* getCollisions();
    HoeEvent* getEvent(const std::string& name);
    HoeInstance* getInstance(const std::string& name);
private:
    float magic_number_;
    std::vector<HoeChunk*> chunks_;
    int parseImports(std::ifstream& file);
    void parseCollisions(std::ifstream& file);
    int parseEvent(std::ifstream& file);
    int parseInstance(std::ifstream& file);
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