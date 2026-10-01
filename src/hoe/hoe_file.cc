#include "hoe_file.hh"

#include <algorithm>
#include <iostream>

#include "bytecounter/bytecounter.hh"
#include "fileread/fileread.hh"
#include "filewrite/filewrite.hh"
#include "ppm/ppm_file.hh"
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
** HOE INSTANCE EVENT
*/

HoeInstanceEvent::HoeInstanceEvent()
    : len_(0)
    , uk_int1_(0)
    , name_("")
{}

HoeInstanceEvent::HoeInstanceEvent(const HoeInstanceEvent& other)
    : len_(other.len_)
    , uk_int1_(other.uk_int1_)
    , name_(other.name_)
    , constants_(other.constants_)
{}

void HoeInstanceEvent::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, len_);
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::writeLString(file, name_);
    filewrite::write4ByteMsb(file, constants_.size());
    for (HoeConstant& constant : constants_)
    {
        constant.serialize(file);
    }
}

std::uint32_t HoeInstanceEvent::getLen() const
{
    return len_;
}
std::uint32_t HoeInstanceEvent::getUkInt1() const
{
    return uk_int1_;
}
std::string HoeInstanceEvent::getName() const
{
    return name_;
}

std::vector<HoeConstant>& HoeInstanceEvent::getConstants()
{
    return constants_;
}

void HoeInstanceEvent::setLen(std::uint32_t le)
{
    len_ = le;
}
void HoeInstanceEvent::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}
void HoeInstanceEvent::setName(std::string name)
{
    name_ = name;
}

/*
** HOE INSTANCE GLOBAL
*/

HoeInstanceGlobal::HoeInstanceGlobal()
    : name_("")
    , uk_int1_(0)
    , uk_int2_(0)
{}

HoeInstanceGlobal::HoeInstanceGlobal(const HoeInstanceGlobal& other)
    : name_(other.name_)
    , uk_int1_(other.uk_int1_)
    , uk_int2_(other.uk_int2_)
{}

void HoeInstanceGlobal::serialize(std::ofstream& file)
{
    filewrite::writeLString(file, name_);
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::write4ByteMsb(file, uk_int2_);
}

std::string HoeInstanceGlobal::getName() const
{
    return name_;
}
std::uint32_t HoeInstanceGlobal::getUkInt1() const
{
    return uk_int1_;
}
std::uint32_t HoeInstanceGlobal::getUkInt2() const
{
    return uk_int2_;
}
void HoeInstanceGlobal::setName(std::string name)
{
    name_ = name;
}
void HoeInstanceGlobal::setUkInt1(std::uint32_t uk_int)
{
    uk_int1_ = uk_int;
}
void HoeInstanceGlobal::setUkInt2(std::uint32_t uk_int)
{
    uk_int2_ = uk_int;
}

/*
** HOE POST INSTANCE
*/

HoePostInstance::HoePostInstance()
    : uk_int1_(0)
    , uk_int2_(0)
    , uk_float1_(0.0)
    , uk_float2_(0.0)
    , uk_float3_(0.0)
    , uk_float4_(0.0)
    , uk_int3_(0)
    , uk_float5_(0.0)
    , uk_int4_(0)
    , uk_int5_(0)
{}

void HoePostInstance::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::write4ByteMsb(file, uk_int2_);
    filewrite::writeFloatMsb(file, uk_float1_);
    filewrite::writeFloatMsb(file, uk_float2_);
    filewrite::writeFloatMsb(file, uk_float3_);
    filewrite::writeFloatMsb(file, uk_float4_);
    filewrite::write4ByteMsb(file, uk_int3_);
    filewrite::writeFloatMsb(file, uk_float5_);
    filewrite::write4ByteMsb(file, uk_int4_);
    filewrite::write4ByteMsb(file, uk_int5_);
}

std::uint32_t HoePostInstance::getUkInt1() const
{
    return uk_int1_;
}
std::uint32_t HoePostInstance::getUkInt2() const
{
    return uk_int2_;
}
float HoePostInstance::getUkFloat1() const
{
    return uk_float1_;
}
float HoePostInstance::getUkFloat2() const
{
    return uk_float2_;
}
float HoePostInstance::getUkFloat3() const
{
    return uk_float3_;
}
float HoePostInstance::getUkFloat4() const
{
    return uk_float4_;
}
std::uint32_t HoePostInstance::getUkInt3() const
{
    return uk_int3_;
}
float HoePostInstance::getUkFloat5() const
{
    return uk_float5_;
}
std::uint32_t HoePostInstance::getUkInt4() const
{
    return uk_int4_;
}
std::uint32_t HoePostInstance::getUkInt5() const
{
    return uk_int5_;
}

void HoePostInstance::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}
void HoePostInstance::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}
void HoePostInstance::setUkFloat1(float uk_float1)
{
    uk_float1_ = uk_float1;
}
void HoePostInstance::setUkFloat2(float uk_float2)
{
    uk_float2_ = uk_float2;
}
void HoePostInstance::setUkFloat3(float uk_float3)
{
    uk_float3_ = uk_float3;
}
void HoePostInstance::setUkFloat4(float uk_float4)
{
    uk_float4_ = uk_float4;
}
void HoePostInstance::setUkInt3(std::uint32_t uk_int3)
{
    uk_int3_ = uk_int3;
}
void HoePostInstance::setUkFloat5(float uk_float5)
{
    uk_float5_ = uk_float5;
}
void HoePostInstance::setUkInt4(std::uint32_t uk_int4)
{
    uk_int4_ = uk_int4;
}
void HoePostInstance::setUkInt5(std::uint32_t uk_int5)
{
    uk_int5_ = uk_int5;
}

/*
** HOE INSTANCE
*/

HoeInstance::HoeInstance()
    : HoeChunk(HoeChunkType::INSTANCE)
    , uk_byte1_(0)
    , length_(0)
    , uk_int1_(0)
    , name_("")
    , event_type_("")
    , params_("")
    , uk_int2_(0)
    , len_until_coord_(0)
    , uk_int3_(0)
    , uk_int4_(0)
    , x_(0.0)
    , y_(0.0)
    , z_(0.0)
    , uk_float1_(0.0)
    , uk_float2_(0.0)
    , uk_int5_(0)
    , health_(0.0)
    , max_health_(0.0)
    , uk_int6_(0)
    , uk_int7_(0)
    , uk_int8_(0)
    , radius_(0.0)
    , uk_float3_(0.0)
    , is_there_post_instance_(0)
{}

void HoeInstance::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, static_cast<std::uint32_t>(chunk_type_));
    filewrite::write1Byte(file, uk_byte1_);
    filewrite::write4ByteMsb(file, length_);
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::writeLString(file, name_);
    filewrite::writeLString(file, event_type_);
    filewrite::writeLString(file, params_);
    filewrite::write4ByteMsb(file, uk_int2_);
    if (uk_int1_ != 0x15)
    {
        filewrite::write4ByteMsb(file, len_until_coord_);
        filewrite::write4ByteMsb(file, uk_int3_);
        for (std::string& lstring : lstrings_)
        {
            filewrite::writeLString(file, lstring);
        }

        filewrite::write4ByteMsb(file, events_.size());
        for (HoeInstanceEvent& instance_event : events_)
        {
            instance_event.serialize(file);
        }

        if (events_.size())
        {
            filewrite::write4ByteMsb(file, uk_int4_);
        }

        filewrite::write4ByteMsb(file, globals_.size());
        for (HoeInstanceGlobal& global : globals_)
        {
            global.serialize(file);
        }
    }

    filewrite::writeFloatMsb(file, x_);
    filewrite::writeFloatMsb(file, y_);
    filewrite::writeFloatMsb(file, z_);
    filewrite::writeFloatMsb(file, uk_float1_);
    filewrite::writeFloatMsb(file, uk_float2_);
    filewrite::write4ByteMsb(file, uk_int5_);
    filewrite::writeFloatMsb(file, health_);
    filewrite::writeFloatMsb(file, max_health_);
    filewrite::write4ByteMsb(file, uk_int6_);
    filewrite::write4ByteMsb(file, uk_int7_);
    filewrite::write4ByteMsb(file, uk_int8_);
    filewrite::writeFloatMsb(file, radius_);
    filewrite::writeFloatMsb(file, uk_float3_);
    filewrite::write4ByteMsb(file, is_there_post_instance_);
    if (is_there_post_instance_)
    {
        post_instance_.serialize(file);
    }
}

std::uint8_t HoeInstance::getUkByte1() const
{
    return uk_byte1_;
}
std::uint32_t HoeInstance::getLength() const
{
    return length_;
}
std::uint32_t HoeInstance::getUkInt1() const
{
    return uk_int1_;
}
std::string HoeInstance::getName() const
{
    return name_;
}
std::string HoeInstance::getEventType() const
{
    return event_type_;
}
std::string HoeInstance::getParams() const
{
    return params_;
}
std::uint32_t HoeInstance::getUkInt2() const
{
    return uk_int2_;
}

std::uint32_t HoeInstance::getLenUntilCoord() const
{
    return len_until_coord_;
}
std::uint32_t HoeInstance::getUkInt3() const
{
    return uk_int3_;
}

bool HoeInstance::getIsThereRoomString() const
{
    return uk_int3_ & 1;
}

bool HoeInstance::getIsTherePNJString() const
{
    return uk_int3_ & 2;
}

bool HoeInstance::getIsThereScriptString() const
{
    return uk_int3_ & 4;
}
std::vector<std::string>& HoeInstance::getLStrings()
{
    return lstrings_;
}
std::vector<HoeInstanceEvent>& HoeInstance::getEvents()
{
    return events_;
}
std::uint32_t HoeInstance::getUkInt4() const
{
    return uk_int4_;
}
std::vector<HoeInstanceGlobal>& HoeInstance::getGlobals()
{
    return globals_;
}
float HoeInstance::getX() const
{
    return x_;
}
float HoeInstance::getY() const
{
    return y_;
}
float HoeInstance::getZ() const
{
    return z_;
}
float HoeInstance::getUkFloat1() const
{
    return uk_float1_;
}
float HoeInstance::getUkFloat2() const
{
    return uk_float2_;
}
std::uint32_t HoeInstance::getUkInt5() const
{
    return uk_int5_;
}
float HoeInstance::getHealth() const
{
    return health_;
}
float HoeInstance::getMaxHealth() const
{
    return max_health_;
}
std::uint32_t HoeInstance::getUkInt6() const
{
    return uk_int6_;
}
std::uint32_t HoeInstance::getUkInt7() const
{
    return uk_int7_;
}
std::uint32_t HoeInstance::getUkInt8() const
{
    return uk_int8_;
}
float HoeInstance::getRadius() const
{
    return radius_;
}
float HoeInstance::getUkFloat3() const
{
    return uk_float3_;
}
std::uint32_t HoeInstance::getIsTherePostInstance() const
{
    return is_there_post_instance_;
}

HoePostInstance& HoeInstance::getPostInstance()
{
    return post_instance_;
}

void HoeInstance::setUkByte1(std::uint8_t uk_byte1)
{
    uk_byte1_ = uk_byte1;
}
void HoeInstance::setLength(std::uint32_t length)
{
    length_ = length;
}
void HoeInstance::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}
void HoeInstance::setName(std::string name)
{
    name_ = name;
}
void HoeInstance::setEventType(std::string event_type)
{
    event_type_ = event_type;
}
void HoeInstance::setParams(std::string params)
{
    params_ = params;
}
void HoeInstance::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}
void HoeInstance::setLenUntilCoord(std::uint32_t len_until_coord)
{
    len_until_coord_ = len_until_coord;
}
void HoeInstance::setUkInt3(std::uint32_t uk_int3)
{
    uk_int3_ = uk_int3;
}
void HoeInstance::setUkInt4(std::uint32_t uk_int4)
{
    uk_int4_ = uk_int4;
}
void HoeInstance::setX(float x)
{
    x_ = x;
}
void HoeInstance::setY(float y)
{
    y_ = y;
}
void HoeInstance::setZ(float z)
{
    z_ = z;
}
void HoeInstance::setUkFloat1(float uk_float1)
{
    uk_float1_ = uk_float1;
}
void HoeInstance::setUkFloat2(float uk_float2)
{
    uk_float2_ = uk_float2;
}
void HoeInstance::setUkInt5(std::uint32_t uk_int5)
{
    uk_int5_ = uk_int5;
}
void HoeInstance::setHealth(float health)
{
    health_ = health;
}
void HoeInstance::setMaxHealth(float max_health)
{
    max_health_ = max_health;
}
void HoeInstance::setUkInt6(std::uint32_t uk_int6)
{
    uk_int6_ = uk_int6;
}
void HoeInstance::setUkInt7(std::uint32_t uk_int7)
{
    uk_int7_ = uk_int7;
}
void HoeInstance::setUkInt8(std::uint32_t uk_int8)
{
    uk_int8_ = uk_int8;
}
void HoeInstance::setRadius(float radius)
{
    radius_ = radius;
}
void HoeInstance::setUkFloat3(float uk_float3)
{
    uk_float3_ = uk_float3;
}
void HoeInstance::setIsTherePostInstance(std::uint32_t is_there_post_instance)
{
    is_there_post_instance_ = is_there_post_instance;
}

/*
** HOE POST IMPORTS
*/

HoePostImports::HoePostImports()
    : length_(0)
    , uk_int1_(0)
    , uk_int2_(0)
    , uk_int3_(0)
    , lstring_("")
    , uk_int4_(0)
    , uk_int5_(0)
    , uk_int6_(0)
{}
HoePostImports::HoePostImports(const HoePostImports& other)
    : length_(other.length_)
    , uk_int1_(other.uk_int1_)
    , uk_int2_(other.uk_int2_)
    , uk_int3_(other.uk_int3_)
    , lstring_(other.lstring_)
    , uk_int4_(other.uk_int4_)
    , uk_int5_(other.uk_int5_)
    , uk_int6_(other.uk_int6_)
{}

void HoePostImports::parse(std::ifstream& file)
{
    length_ = fileread::read4ByteMsb(file);
    uk_int1_ = fileread::read4ByteMsb(file);
    uk_int2_ = fileread::read4ByteMsb(file);
    uk_int3_ = fileread::read4ByteMsb(file);
    lstring_ = fileread::readLString(file);
    uk_int4_ = fileread::read4ByteMsb(file);
    uk_int5_ = fileread::read4ByteMsb(file);
    uk_int6_ = fileread::read4ByteMsb(file);
}

void HoePostImports::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, length_);
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::write4ByteMsb(file, uk_int2_);
    filewrite::write4ByteMsb(file, uk_int3_);
    filewrite::writeLString(file, lstring_);
    filewrite::write4ByteMsb(file, uk_int4_);
    filewrite::write4ByteMsb(file, uk_int5_);
    filewrite::write4ByteMsb(file, uk_int6_);
}

std::uint32_t HoePostImports::getLength()
{
    return length_;
}

std::uint32_t HoePostImports::getUkInt1()
{
    return uk_int1_;
}

std::uint32_t HoePostImports::getUkInt2()
{
    return uk_int2_;
}

std::uint32_t HoePostImports::getUkInt3()
{
    return uk_int3_;
}

std::string HoePostImports::getLString()
{
    return lstring_;
}

std::uint32_t HoePostImports::getUkInt4()
{
    return uk_int4_;
}

std::uint32_t HoePostImports::getUkInt5()
{
    return uk_int5_;
}

std::uint32_t HoePostImports::getUkInt6()
{
    return uk_int6_;
}

void HoePostImports::setLength(std::uint32_t length)
{
    length_ = length;
}

void HoePostImports::setUkInt1(std::uint32_t uk_int1)
{
    uk_int1_ = uk_int1;
}

void HoePostImports::setUkInt2(std::uint32_t uk_int2)
{
    uk_int2_ = uk_int2;
}

void HoePostImports::setUkInt3(std::uint32_t uk_int3)
{
    uk_int3_ = uk_int3;
}

void HoePostImports::setLString(std::string lstring)
{
    lstring_ = lstring;
}

void HoePostImports::setUkInt4(std::uint32_t uk_int4)
{
    uk_int4_ = uk_int4;
}

void HoePostImports::setUkInt5(std::uint32_t uk_int5)
{
    uk_int5_ = uk_int5;
}

void HoePostImports::setUkInt6(std::uint32_t uk_int6)
{
    uk_int6_ = uk_int6;
}

/*
** HOE IMPORTS
*/
HoeImports::HoeImports()
    : HoeChunk(HoeChunkType::IMPORTS)
    , length_(0)
    , imports_type_(HoeImportsType::ONE)
{}

void HoeImports::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, static_cast<std::uint32_t>(chunk_type_));
    filewrite::write4ByteMsb(file, length_);
    filewrite::write4ByteMsb(file, static_cast<std::uint32_t>(imports_type_));
    for (std::string& lstring : lstrings_)
    {
        filewrite::writeLString(file, lstring);
    }

    filewrite::write4ByteMsb(file, post_imports_.size());
    for (HoePostImports& post_import : post_imports_)
    {
        post_import.serialize(file);
    }
}

std::uint32_t HoeImports::getLength()
{
    return length_;
}

HoeImportsType HoeImports::getImportsType()
{
    return imports_type_;
}

std::vector<std::string>& HoeImports::getLStrings()
{
    return lstrings_;
}

std::vector<HoePostImports>& HoeImports::getPostImports()
{
    return post_imports_;
}

void HoeImports::setLength(std::uint32_t length)
{
    length_ = length;
}

void HoeImports::setImportsType(HoeImportsType imports_type)
{
    imports_type_ = imports_type;
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

void HoeConstant::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, static_cast<std::uint32_t>(constant_type_));

    switch (constant_type_)
    {
    case HoeConstantType::INT:
        filewrite::write4ByteMsb(file, int_value_);
        break;
    case HoeConstantType::FLOAT:
        filewrite::writeFloatMsb(file, float_value_);
        break;
    }
}

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

HoeEvent::~HoeEvent()
{
    delete script_;
}

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

void HoeEvent::serialize(std::ofstream& file)
{
    // TODO: put the write4ByteMsb() in HoeChunk::serialize()?
    filewrite::write4ByteMsb(file, static_cast<std::uint32_t>(chunk_type_));
    filewrite::writeFloatMsb(file, magic_number_);
    filewrite::writeLString(file, name_);
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::write4ByteMsb(file, uk_int2_);
    filewrite::write4ByteMsb(file, uk_int3_);

    filewrite::write4ByteMsb(file, uk_ints_.size());
    for (std::uint32_t uk_int : uk_ints_)
    {
        filewrite::write4ByteMsb(file, uk_int);
    }

    filewrite::write4ByteMsb(file, lstrings_.size());
    for (std::string& lstring : lstrings_)
    {
        filewrite::writeLString(file, lstring);
    }

    filewrite::write4ByteMsb(file, hoe_constants_.size());
    for (HoeConstant& constant : hoe_constants_)
    {
        constant.serialize(file);
    }

    filewrite::write4ByteMsb(file, m1_.size());
    for (std::uint32_t m1 : m1_)
    {
        filewrite::write4ByteMsb(file, m1);
    }

    script_->serialize(file);
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
    globals.push_back("gState"); // Not sure

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
    : uk_short1_(other.uk_short1_)
    , uk_short2_(other.uk_short2_)
    , uk_int2_(other.uk_int2_)
    , uk_float_(other.uk_float_)
    , flags_and_index_(other.flags_and_index_)
    , uk_byte1_(other.uk_byte1_)
    , uk_byte2_(other.uk_byte2_)
{}

void HoeCollisionCell::serialize(std::ofstream& file)
{
    filewrite::write2ByteLsb(file, uk_short1_);
    filewrite::write2ByteLsb(file, uk_short2_);
    filewrite::write4ByteLsb(file, uk_int2_);
    filewrite::writeFloatLsb(file, uk_float_);
    filewrite::write2ByteLsb(file, flags_and_index_);
    filewrite::write1Byte(file, uk_byte1_);
    filewrite::write1Byte(file, uk_byte2_);
}

PpmPixel HoeCollisionCell::getPixelByFlags()
{
    std::uint32_t red = 0;
    std::uint32_t green = 0;
    std::uint32_t blue = 0;

    // Map colours depending on the flags
    if (getUkBool2())
    {
        green = 0xFF;
        if (getUkBool1())
        {
            blue = 0xFF;
        }
    }
    return PpmPixel(red, green, blue);
}

PpmPixel HoeCollisionCell::getPixelByIndex()
{
    std::uint32_t red = getIndex();
    std::uint32_t green = 0;
    std::uint32_t blue = 0;
    return PpmPixel(red, green, blue);
}

PpmPixel HoeCollisionCell::getPixelByUkShort2()
{
    std::uint32_t red = getUkShort2();
    std::uint32_t green = 0;
    std::uint32_t blue = 0;
    return PpmPixel(red, green, blue);
}

PpmPixel HoeCollisionCell::getPixelByUkInt2()
{
    std::uint32_t red = getUkInt2() >> 8;
    std::uint32_t green = 0;
    std::uint32_t blue = 0;
    return PpmPixel(red, green, blue);
}

PpmPixel HoeCollisionCell::getPixelByUkFloat()
{
    std::uint32_t uk_float_u = getUkFloat();
    std::uint32_t red = 0;
    std::uint32_t green = uk_float_u;
    std::uint32_t blue = 0;
    return PpmPixel(red, green, blue);
}

PpmPixel HoeCollisionCell::getPixelByUkByte1()
{
    std::uint32_t red = 0;
    std::uint32_t green = 0;
    std::uint32_t blue = getUkByte1();
    return PpmPixel(red, green, blue);
}

std::uint16_t HoeCollisionCell::getUkShort1() const
{
    return uk_short1_;
}

std::uint16_t HoeCollisionCell::getUkShort2() const
{
    return uk_short2_;
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
    return (flags_and_index_ & 0x8000) != 0;
}

bool HoeCollisionCell::getUkBool2()
{
    return (flags_and_index_ & 0x4000) != 0;
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

void HoeCollisionCell::setUkShort1(std::uint16_t  uk_short1)
{
    uk_short1_ = uk_short1;
}

void HoeCollisionCell::setUkShort2(std::uint16_t  uk_short2)
{
    uk_short2_ = uk_short2;
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
    if (getUkBool1() == uk_bool1) return;
    flags_and_index_ ^= 0x8000;
}

void HoeCollisionCell::setUkBool2(bool uk_bool2)
{
    if (getUkBool2() == uk_bool2) return;
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

void HoeCollisionsPostMap::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::write4ByteMsb(file, uk_int2_);
    filewrite::write4ByteMsb(file, uk_int3_);
    filewrite::write4ByteMsb(file, uk_int4_);
    filewrite::write4ByteMsb(file, uk_int5_);
    filewrite::write4ByteMsb(file, uk_ints_.size());
    for (std::uint32_t uk_int : uk_ints_)
    {
        filewrite::write4ByteMsb(file, uk_int);
    }
}

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
    cell.setUkShort1(fileread::read2ByteLsb(file));
    cell.setUkShort2(fileread::read2ByteLsb(file));
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

void HoeCollisionsMap::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, index_);
    filewrite::write4ByteMsb(file, cells_.size());
    for (HoeCollisionCell& cell : cells_)
    {
        cell.serialize(file);
    }

    filewrite::write4ByteMsb(file, width_);
    filewrite::write4ByteMsb(file, height_);
    filewrite::writeFloatMsb(file, uk_float1_);
    filewrite::writeFloatMsb(file, uk_float2_);
    filewrite::writeFloatMsb(file, uk_float3_);
    filewrite::writeFloatMsb(file, uk_float4_);
    filewrite::writeFloatMsb(file, uk_float5_);
    filewrite::writeFloatMsb(file, uk_float6_);
    filewrite::writeFloatMsb(file, uk_float7_);
    filewrite::writeFloatMsb(file, uk_float8_);

    for (HoeCollisionsPostMap& post_map : post_maps_)
    {
        post_map.serialize(file);
    }
}

std::uint32_t HoeCollisionsMap::getMaxUkShort2()
{
    std::uint16_t max = 0;
    for (HoeCollisionCell& cell : cells_)
    {
        std::uint16_t uk_int1 = cell.getUkShort2();
        if (uk_int1 > max)
        {
            max = uk_int1;
        }
    }

    return max;
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

void HoePostCollisions::serialize(std::ofstream& file)
{
    filewrite::writeFloatMsb(file, uk_float1_);
    filewrite::writeFloatMsb(file, uk_float2_);
    filewrite::writeFloatMsb(file, uk_float3_);
    filewrite::writeFloatMsb(file, uk_float4_);
    filewrite::writeFloatMsb(file, uk_float5_);
    filewrite::writeFloatMsb(file, uk_float6_);
}

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

void HoeCollisions::serialize(std::ofstream& file)
{
    filewrite::write4ByteMsb(file, static_cast<std::uint32_t>(chunk_type_));
    filewrite::write4ByteMsb(file, length_);
    filewrite::write4ByteMsb(file, uk_int1_);
    filewrite::writeLString(file, room_id_);
    filewrite::write4ByteMsb(file, uk_int2_);
    filewrite::writeFloatMsb(file, uk_float1_);
    filewrite::writeFloatMsb(file, uk_float2_);
    filewrite::writeFloatMsb(file, uk_float3_);

    filewrite::write4ByteMsb(file, maps_.size());
    for (HoeCollisionsMap& map : maps_)
    {
        map.serialize(file);
    }

    filewrite::write4ByteMsb(file, width_);
    filewrite::write4ByteMsb(file, height_);
    filewrite::writeFloatMsb(file, uk_float4_);
    filewrite::writeFloatMsb(file, uk_float5_);
    filewrite::writeFloatMsb(file, uk_float6_);
    filewrite::writeFloatMsb(file, uk_float7_);
    filewrite::writeFloatMsb(file, uk_float8_);
    filewrite::writeFloatMsb(file, uk_float9_);
    filewrite::write4ByteMsb(file, uk_int3_);
    filewrite::write4ByteMsb(file, uk_int4_);
    filewrite::write4ByteMsb(file, uk_int5_);
    filewrite::write4ByteMsb(file, uk_int6_);
    filewrite::write4ByteMsb(file, uk_int7_);
    filewrite::write4ByteMsb(file, uk_int8_);
    filewrite::write4ByteMsb(file, uk_int9_);

    filewrite::write4ByteMsb(file, post_collisions_.size());
    for (HoePostCollisions& post_collision : post_collisions_)
    {
        post_collision.serialize(file);
    }
}

std::uint32_t HoeCollisions::getLength()
{
    return length_;
}

std::uint32_t HoeCollisions::getUkInt1()
{
    return uk_int1_;
}


std::string HoeCollisions::getRoomId()
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

HoeFile::~HoeFile()
{
    for (HoeChunk* chunk : chunks_)
    {
        delete chunk;
    }
}

int HoeFile::parseImports(std::ifstream& file)
{
    auto imports_chunk = new HoeImports();

    imports_chunk->setLength(fileread::read4ByteMsb(file));
    std::uint32_t imports_type_u = fileread::read4ByteMsb(file);
    HoeImportsType imports_type = static_cast<HoeImportsType>(imports_type_u);

    switch (imports_type)
    {
    case HoeImportsType::TWO:
        imports_chunk->getLStrings().push_back(fileread::readLString(file));
    case HoeImportsType::ONE:
        imports_chunk->getLStrings().push_back(fileread::readLString(file));
        imports_chunk->setImportsType(imports_type);
        break;
    default:
        delete imports_chunk;
        return 1;
    }

    std::uint32_t nb_post_imports = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_post_imports; i++)
    {
        HoePostImports post_import;
        post_import.parse(file);
        imports_chunk->getPostImports().push_back(post_import);
    }

    chunks_.push_back(imports_chunk);
    return 0;
}

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

int HoeFile::parseInstance(std::ifstream& file)
{
    auto instance_chunk = new HoeInstance();

    instance_chunk->setUkByte1(fileread::read1Byte(file));
    instance_chunk->setLength(fileread::read4ByteMsb(file));
    instance_chunk->setUkInt1(fileread::read4ByteMsb(file));
    instance_chunk->setName(fileread::readLString(file));
    instance_chunk->setEventType(fileread::readLString(file));
    instance_chunk->setParams(fileread::readLString(file));
    instance_chunk->setUkInt2(fileread::read4ByteMsb(file));
    if (instance_chunk->getUkInt1() != 0x15)
    {
        instance_chunk->setLenUntilCoord(fileread::read4ByteMsb(file));
        instance_chunk->setUkInt3(fileread::read4ByteMsb(file));

        // TODO: if there are only 3 strings, then maybe do not use a vector
        // and make 3 std::string attributes
        std::uint32_t nb_lstrings = 0;
        if (instance_chunk->getIsThereRoomString())
        {
            nb_lstrings++;
        }
        if (instance_chunk->getIsTherePNJString())
        {
            nb_lstrings++;
        }
        if (instance_chunk->getIsThereScriptString())
        {
            nb_lstrings++;
        }

        std::string lstring;
        try
        {
            for (std::uint32_t i = 0; i < nb_lstrings; i++)
            {
                lstring = fileread::readLString(file);
                instance_chunk->getLStrings().push_back(lstring);
            }
        } catch (std::exception& e)
        {
            delete instance_chunk;
            return 1;
        }

        std::uint32_t nb_events = fileread::read4ByteMsb(file);
        for (std::uint32_t i = 0; i < nb_events; i++)
        {
            HoeInstanceEvent instance_event;

            instance_event.setLen(fileread::read4ByteMsb(file));
            instance_event.setUkInt1(fileread::read4ByteMsb(file));
            instance_event.setName(fileread::readLString(file));
            std::uint32_t nb_constants = fileread::read4ByteMsb(file);
            for (std::uint32_t j = 0; j < nb_constants; j++)
            {
                HoeConstantType constant_type = static_cast<HoeConstantType>(
                    fileread::read4ByteMsb(file)
                );

                HoeConstant constant(constant_type);
                constant.setConstantType(constant_type);

                if (constant_type == HoeConstantType::INT)
                {
                    constant.setIntValue(fileread::read4ByteMsb(file));
                }
                else if (constant_type == HoeConstantType::FLOAT)
                {
                    constant.setFloatValue(fileread::readFloatMsb(file));
                }
                else
                {
                    delete instance_chunk;
                    return 1;
                }

                instance_event.getConstants().push_back(constant);
            }

            instance_chunk->getEvents().push_back(instance_event);
        }

        if (nb_events)
        {
            instance_chunk->setUkInt4(fileread::read4ByteMsb(file));
        }

        std::uint32_t nb_globals = fileread::read4ByteMsb(file);
        for (std::uint32_t i = 0; i < nb_globals; i++)
        {
            HoeInstanceGlobal instance_global;

            instance_global.setName(fileread::readLString(file));
            instance_global.setUkInt1(fileread::read4ByteMsb(file));
            instance_global.setUkInt2(fileread::read4ByteMsb(file));

            instance_chunk->getGlobals().push_back(instance_global);
        }
    }

    instance_chunk->setX(fileread::readFloatMsb(file));
    instance_chunk->setY(fileread::readFloatMsb(file));
    instance_chunk->setZ(fileread::readFloatMsb(file));
    instance_chunk->setUkFloat1(fileread::readFloatMsb(file));
    instance_chunk->setUkFloat2(fileread::readFloatMsb(file));
    instance_chunk->setUkInt5(fileread::read4ByteMsb(file));
    instance_chunk->setHealth(fileread::readFloatMsb(file));
    instance_chunk->setMaxHealth(fileread::readFloatMsb(file));
    instance_chunk->setUkInt6(fileread::read4ByteMsb(file));
    instance_chunk->setUkInt7(fileread::read4ByteMsb(file));
    instance_chunk->setUkInt8(fileread::read4ByteMsb(file));
    instance_chunk->setRadius(fileread::readFloatMsb(file));
    instance_chunk->setUkFloat3(fileread::readFloatMsb(file));
    instance_chunk->setIsTherePostInstance(fileread::read4ByteMsb(file));

    if (instance_chunk->getIsTherePostInstance())
    {
        HoePostInstance& post_instance = instance_chunk->getPostInstance();
        post_instance.setUkInt1(fileread::read4ByteMsb(file));
        post_instance.setUkInt2(fileread::read4ByteMsb(file));
        post_instance.setUkFloat1(fileread::readFloatMsb(file));
        post_instance.setUkFloat2(fileread::readFloatMsb(file));
        post_instance.setUkFloat3(fileread::readFloatMsb(file));
        post_instance.setUkFloat4(fileread::readFloatMsb(file));
        post_instance.setUkInt3(fileread::read4ByteMsb(file));
        post_instance.setUkFloat5(fileread::readFloatMsb(file));
        post_instance.setUkInt4(fileread::read4ByteMsb(file));
        post_instance.setUkInt5(fileread::read4ByteMsb(file));
    }

    chunks_.push_back(instance_chunk);
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
    while (next_chunk_type != HoeChunkType::END)
    {
        switch (next_chunk_type)
        {
        case HoeChunkType::COLLISIONS:
            hoe_file->parseCollisions(file);
            break;
        case HoeChunkType::IMPORTS:
            if (hoe_file->parseImports(file))
            {
                file.close();
                delete hoe_file;
                return nullptr;
            }
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
            if (hoe_file->parseInstance(file))
            {
                file.close();
                delete hoe_file;
                return nullptr;
            }
            break;
        default:
            file.close();
            return nullptr;
        }

        chunk_type_u = fileread::read4ByteMsb(file);
        next_chunk_type = static_cast<HoeChunkType>(chunk_type_u);
    }

    file.close();
    return hoe_file;
}

void HoeFile::serialize(std::filesystem::path path)
{
    std::ofstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return;
    }

    filewrite::writeFloatMsb(file, magic_number_);

    for (HoeChunk* chunk : chunks_)
    {
        chunk->serialize(file);
    }

    filewrite::write4ByteMsb(file,
        static_cast<std::uint32_t>(HoeChunkType::END)
    );

    file.close();
}

// The path should be a path to a folder, the generated files will be named
// [room_id]_[n].ppm where n is the index of the map
int HoeFile::extractCollisionsMaps(std::filesystem::path path)
{
    HoeCollisions* collisions = getCollisions();
    if (!collisions)
    {
        return 1;
    }

    for (HoeCollisionsMap& map : collisions->getMaps())
    {
        std::string room_id = collisions->getRoomId();
        std::uint32_t map_index = map.getIndex();
        std::string map_index_str = std::to_string(map_index);

        std::string filename = room_id + "_" + map_index_str + ".ppm";

        std::filesystem::path output_path = path;
        output_path.append(filename);

        // In the case of maps made with the UkBools of the HoeCollisionCells,
        // the maximum value for a colour is always 0xFF, but it might not be
        // the case for other types of maps, we will consider this later
        PpmFile ppm_file(map.getWidth(), map.getHeight(), 0xFF);

        for (HoeCollisionCell& cell : map.getCells())
        {
            PpmPixel ppm_pixel = cell.getPixelByFlags();
            ppm_file.getPixels().push_back(ppm_pixel);
        }

        ppm_file.serialize(output_path);
    }

    return 0;
}

int HoeFile::modifyCollisionsMap(std::filesystem::path ppm_path, size_t index)
{
    HoeCollisions* collisions = getCollisions();
    if (!collisions)
    {
        return 1;
    }

    if (index >= collisions->getMaps().size())
    {
        return 1;
    }

    PpmFile* ppm_file = PpmFile::makeFile(ppm_path);
    if (!ppm_file)
    {
        return 1;
    }

    HoeCollisionsMap& map = collisions->getMaps().at(index);

    size_t i = 0;
    auto pixels = ppm_file->getPixels();

    if (map.getCells().size() != pixels.size())
    {
        delete ppm_file;
        return 1;
    }

    for (HoeCollisionCell& cell : map.getCells())
    {
        // Map colours depending on the flags (2)
        std::uint32_t green = pixels.at(i).getGreen();
        std::uint32_t blue = pixels.at(i).getBlue();
        cell.setUkBool1(blue == 0xFF);
        cell.setUkBool2(green == 0xFF);
        i++;
    }

    delete ppm_file;
    return 0;
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
        HoeCollisions* collisions = dynamic_cast<HoeCollisions*>(chunk);
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
        HoeEvent* event = dynamic_cast<HoeEvent*>(chunk);
        if (event && event->getName() == name)
        {
            return event;
        }
    }

    return nullptr;
}

HoeInstance* HoeFile::getInstance(const std::string& name)
{
    for (HoeChunk* chunk: chunks_)
    {
        HoeInstance* instance = dynamic_cast<HoeInstance*>(chunk);
        if (instance && instance->getName() == name)
        {
            return instance;
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
