#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

class HoeEvent;

class Indent
{
public:
    static void initializeIndent();
    static void increaseIndent();
    static void decreaseIndent();
    static void printIndent(std::ostream& os);
    static int getIndent();
private:
    static int indent_;
};

class DebugOffset
{
public:
    static void setOffset(size_t offset);
    static size_t getOffset();
private:
    static size_t offset_;
};

class CurrentEvent
{
public:
    static HoeEvent* getCurrentEvent();
    static void setCurrentEvent(HoeEvent* event);
private:
    static HoeEvent* current_event_;
};

enum class HoeExpressionType
{
    VALUE = 0x65,
    ADDITION = 0x66,
    SUBTRACTION = 0x67,
    MULTIPLICATION = 0x68,
    DIVISION = 0x69,
    MODULO = 0x6A,
};

enum class HoeValueType
{
    VARIABLE = 0x01,
    HOE_CONSTANT = 0x02,
    UK_VALUE_TYPE_03 = 0x03,
    FUNCTION_CALL = 0x04,
    MATH_FUNCTION = 0x05,
    UK_FUNCTION_CALL = 0x06,
    RETURN = 0x07,
    STRING = 0x08,
};

enum class HoeMathFunctionType
{
    UNKNOWN = 0x00,
    SIN = 0x02,
    ABS = 0x09,
};

enum class HoeArgumentType
{
    IMMEDIATE = 0x01,
    HOE_CONSTANT = 0x02,
};

enum class HoeIfThenType
{
    IF_THEN_BLOCKS = 0x01,
    IF_THEN_IF = 0x02,
};

class HoeArgument
{
public:
    HoeArgument(HoeArgumentType type);
    virtual ~HoeArgument();
    static HoeArgument* parseArgument(std::ifstream& file);
private:
    HoeArgumentType type_;
};

class HoeImmediateArg : public HoeArgument
{
public:
    HoeImmediateArg(std::uint32_t value);
    static HoeImmediateArg* parseImmediateArg(std::ifstream& file);
    std::uint32_t getValue() const;
    void setValue(std::uint32_t value);
private:
    std::uint32_t value_;
};

class HoeValue
{
public:
    HoeValue(HoeValueType type);
    virtual ~HoeValue() = default;
    static HoeValue* parseValue(std::ifstream& file);
protected:
    HoeValueType type_;
};

class HoeExpression
{
public:
    HoeExpression(HoeExpressionType expressionType);
    virtual ~HoeExpression();
    static HoeExpression* parseExpression(std::ifstream& file);
    HoeExpressionType getExpressionType();
    void getExpressionType(HoeExpressionType expression_type);
private:
    HoeExpressionType expression_type_;
};

class HoeOperation : public HoeExpression
{
public:
    HoeOperation(HoeExpressionType expression_type);
    ~HoeOperation() override;
    HoeValue* getValue1();
    HoeValue* getValue2();
    const HoeValue* getValue1() const;
    const HoeValue* getValue2() const;
    void setValue1(HoeValue* value1);
    void setValue2(HoeValue* value2);
private:
    HoeValue* value1_;
    HoeValue* value2_;
};

class HoeConstantArg : public HoeArgument
{
public:
    HoeConstantArg();
    ~HoeConstantArg();
    static HoeConstantArg* parseConstantArg(std::ifstream& file);
    HoeExpression* getExpression();
    const HoeExpression* getExpression() const;
    void setExpression(HoeExpression* expression);
private:
    HoeExpression* expression_;
};

class HoeVariable : public HoeValue
{
public:
    HoeVariable(std::uint32_t index);
    static HoeVariable* parseVariable(std::ifstream& file);
    std::uint32_t getIndex() const;
    const std::string& getName() const;
    void setName(const std::string& name);
private:
    std::uint32_t index_;
    std::string name_;
};

class HoeConstantVal : public HoeValue
{
public:
    HoeConstantVal(std::uint32_t index);
    static HoeConstantVal* parseConstantVal(std::ifstream& file);
    std::uint32_t getIndex() const;
private:
    std::uint32_t index_;
};

class HoeUkValue03 : public HoeValue
{
public:
    HoeUkValue03(std::uint32_t uk_int);
    static HoeUkValue03* parseUkValue03(std::ifstream& file);
    std::uint32_t getUkInt() const;
private:
    std::uint32_t uk_int_;
};

class HoeFunctionCall : public HoeValue
{
public:
    HoeFunctionCall(std::string& name);
    static HoeFunctionCall* parseFunctionCall(std::ifstream& file);
    std::string getName() const;
    std::vector<HoeArgument*>& getArguments();
    const std::vector<HoeArgument*>& getArguments() const;
protected:
    std::string name_;
    std::vector<HoeArgument*> arguments_;
};

class HoeMathFunction : public HoeValue
{
public:
    HoeMathFunction(HoeMathFunctionType type);
    static HoeMathFunction* parseMathFunction(std::ifstream& file);
    HoeMathFunctionType getType() const;
    std::uint32_t getUkInt() const;
    HoeExpression* getExpression() const;
    void setUkInt(std::uint32_t uk_int);
    void setExpression(HoeExpression* expression);
protected:
    HoeMathFunctionType type_;
    std::uint32_t uk_int_;
    HoeExpression* expression_;
};

class HoeUkFunctionCall : public HoeFunctionCall
{
public:
    HoeUkFunctionCall(std::string& name);
private:
};

class HoeReturn : public HoeValue
{
public:
    HoeReturn();
    static HoeReturn* parseReturn(std::ifstream& file);
private:
};

class HoeString : public HoeValue
{
public:
    HoeString(const std::string& name);
    static HoeString* parseString(std::ifstream& file);
    const std::string& getName() const;
private:
    std::string name_;
};

// This corresponds to HoeExpressionType::VALUE (0x65)
class HoeValexpr : public HoeExpression
{
public:
    HoeValexpr();
    ~HoeValexpr() override;
    static HoeValexpr* parseValexpr(std::ifstream& file);
    HoeValue* getValue() const;
    void setValue(HoeValue* value);
private:
    HoeValue* value_;
};

class HoeAddition : public HoeOperation
{
public:
    HoeAddition();
    ~HoeAddition();
    static HoeAddition* parseAddition(std::ifstream& file);
private:
};

class HoeSubtraction : public HoeOperation
{
public:
    HoeSubtraction();
    ~HoeSubtraction();
    static HoeSubtraction* parseSubtraction(std::ifstream& file);
private:
};

class HoeMultiplication : public HoeOperation
{
public:
    HoeMultiplication();
    ~HoeMultiplication();
    static HoeMultiplication* parseMultiplication(std::ifstream& file);
private:
};

class HoeDivision : public HoeOperation
{
public:
    HoeDivision();
    ~HoeDivision();
    static HoeDivision* parseDivision(std::ifstream& file);
private:
};

class HoeModulo : public HoeOperation
{
public:
    HoeModulo();
    ~HoeModulo();
    static HoeModulo* parseModulo(std::ifstream& file);
private:
};

enum class HoeOpCode
{
    ASSIGN = 0xD0,
    EQUAL = 0xCA,
    NOT_EQUAL = 0xCB,
    GREATER_THAN = 0xCC,
    LOWER_THAN = 0xCD,
    GREATER_OR_EQUAL = 0xCE,
    LOWER_OR_EQUAL = 0xCF,
    BOOLEAN = 0xC9,

};

class HoeBlock
{
public:
    HoeBlock(HoeOpCode op_code);
    HoeBlock(const HoeBlock& other);
    virtual ~HoeBlock() = default;
    static HoeBlock* parseBlock(std::ifstream& file);
    bool getNot() const;

    void setNot(bool not_bool);
private:
    HoeOpCode op_code_;
    bool not_;
};

class HoeAssign : public HoeBlock
{
public:
    HoeAssign();
    ~HoeAssign() override;
    static HoeAssign* parseAssign(std::ifstream& file);
    HoeExpression* getExpression1();
    HoeExpression* getExpression2();
    const HoeExpression* getExpression1() const;
    const HoeExpression* getExpression2() const;

    void setExpression1(HoeExpression* expression1);
    void setExpression2(HoeExpression* expression2);
private:
    HoeExpression* expression1_;
    HoeExpression* expression2_;
};

class HoeComparison : public HoeBlock
{
public:
    HoeComparison(HoeOpCode op_code);
    ~HoeComparison() override;
    static HoeComparison* parseComparison(std::ifstream& file,
        HoeOpCode op_code);
    HoeExpression* getExpression1();
    HoeExpression* getExpression2();
    const HoeExpression* getExpression1() const;
    const HoeExpression* getExpression2() const;
    void setExpression1(HoeExpression* expression1);
    void setExpression2(HoeExpression* expression2);
private:
    HoeExpression* expression1_;
    HoeExpression* expression2_;
};

class HoeEqual : public HoeComparison
{
public:
    HoeEqual();
    ~HoeEqual();
    static HoeEqual* parseEqual(std::ifstream& file);
private:
};

class HoeNotEqual : public HoeComparison
{
public:
    HoeNotEqual();
    ~HoeNotEqual();
    static HoeNotEqual* parseNotEqual(std::ifstream& file);
private:
};

class HoeGreaterThan : public HoeComparison
{
public:
    HoeGreaterThan();
    ~HoeGreaterThan();
    static HoeGreaterThan* parseGreaterThan(std::ifstream& file);
private:
};

class HoeLowerThan : public HoeComparison
{
public:
    HoeLowerThan();
    ~HoeLowerThan();
    static HoeLowerThan* parseLowerThan(std::ifstream& file);
private:
};

class HoeGreaterOrEqual : public HoeComparison
{
public:
    HoeGreaterOrEqual();
    ~HoeGreaterOrEqual();
    static HoeGreaterOrEqual* parseGreaterOrEqual(std::ifstream& file);
private:
};

class HoeLowerOrEqual : public HoeComparison
{
public:
    HoeLowerOrEqual();
    ~HoeLowerOrEqual();
    static HoeLowerOrEqual* parseLowerOrEqual(std::ifstream& file);
private:
};

class HoeBoolean : public HoeBlock
{
public:
    HoeBoolean();
    ~HoeBoolean() override;
    static HoeBoolean* parseBoolean(std::ifstream& file);
    HoeExpression* getExpression();
    const HoeExpression* getExpression() const;
    void setExpression(HoeExpression* expression);
private:
    HoeExpression* expression_;
};

class HoeIfThen
{
public:
    HoeIfThen(HoeIfThenType type);
    virtual ~HoeIfThen();
    static HoeIfThen* parseIfThen(std::ifstream& file);
    std::vector<HoeBlock*>& getConditions();
    const std::vector<HoeBlock*>& getConditions() const;
private:
    HoeIfThenType type_;
    std::vector<HoeBlock*> conditions_;
};

class HoeIfThenIf : public HoeIfThen
{
public:
    HoeIfThenIf();
    ~HoeIfThenIf();
    static HoeIfThenIf* parseIfThenIf(std::ifstream& file);
    std::vector<HoeIfThen*>& getBody();
    const std::vector<HoeIfThen*>& getBody() const;
private:
    std::vector<HoeIfThen*> body_;
};

class HoeIfThenBlocks : public HoeIfThen
{
public:
    HoeIfThenBlocks();
    ~HoeIfThenBlocks();
    static HoeIfThenBlocks* parseIfThenBlocks(std::ifstream& file);
    std::vector<HoeBlock*>& getBody();
    const std::vector<HoeBlock*>& getBody() const;
private:
    std::vector<HoeBlock*> body_;
};

class HoeMask
{
public:
    HoeMask(const std::string& name);
    const std::string& getName() const;
    std::vector<std::uint32_t>& getUkInts();
    const std::vector<std::uint32_t>& getUkInts() const;
    std::vector<std::uint32_t>& getM1();
    const std::vector<std::uint32_t>& getM1() const;
    std::uint32_t getUkInt1() const;
    std::uint32_t getUkInt2() const;
    HoeBlock* getBlock() const;
    std::uint32_t getUkInt3() const;
    HoeExpression* getExpression() const;

    void setUkInt1(std::uint32_t uk_int);
    void setUkInt2(std::uint32_t uk_int);
    void setBlock(HoeBlock* block);
    void setUkInt3(std::uint32_t uk_int);
    void setExpression(HoeExpression* expression);
private:
    std::string name_;
    std::vector<std::uint32_t> uk_ints_;
    std::vector<std::uint32_t> m1_;
    std::uint32_t uk_int1_;
    std::uint32_t uk_int2_;
    HoeBlock* block_;
    std::uint32_t uk_int3_;
    HoeExpression* expression_;
};

class HoeScript
{
public:
    HoeScript();
    HoeScript(const HoeScript& other);
    ~HoeScript();
    void parseHoeBlock(std::ifstream& file);
    void parseHoeMask(std::ifstream& file);
    int parseHoeScript(std::ifstream& file);

    HoeMask* getMask();
    std::vector<HoeBlock*>& getBlocks();
    const std::vector<HoeBlock*>& getBlocks() const;
    std::vector<HoeIfThen*>& getIfThens();
    const std::vector<HoeIfThen*>& getIfThens() const;

    void setMask(HoeMask* mask);
private:
    HoeMask* mask_;
    std::vector<HoeBlock*> blocks_;
    std::vector<HoeIfThen*> if_thens_;
};

std::ostream& operator<<(std::ostream& os, const HoeScript& script);

std::ostream& operator<<(std::ostream& os, const HoeIfThenBlocks& if_then_blocks);
std::ostream& operator<<(std::ostream& os, const HoeIfThenIf& if_then_if);
std::ostream& operator<<(std::ostream& os, const HoeIfThen& if_then);

std::ostream& operator<<(std::ostream& os, const HoeBlock& block);
std::ostream& operator<<(std::ostream& os, const HoeAssign& assign);
std::ostream& operator<<(std::ostream& os, const HoeBoolean& boolean);
std::ostream& operator<<(std::ostream& os, const HoeComparison& comparison);
std::ostream& operator<<(std::ostream& os, const HoeEqual& equal);
std::ostream& operator<<(std::ostream& os, const HoeNotEqual& not_equal);
std::ostream& operator<<(std::ostream& os, const HoeGreaterThan& greater_than);
std::ostream& operator<<(std::ostream& os, const HoeLowerThan& lower_than);
std::ostream& operator<<(std::ostream& os, const HoeGreaterOrEqual& greater_or_equal);
std::ostream& operator<<(std::ostream& os, const HoeLowerOrEqual& lower_or_equal);

std::ostream& operator<<(std::ostream& os, const HoeOperation& operation);
std::ostream& operator<<(std::ostream& os, const HoeAddition& addition);
std::ostream& operator<<(std::ostream& os, const HoeSubtraction& subtraction);
std::ostream& operator<<(std::ostream& os, const HoeMultiplication& multiplication);
std::ostream& operator<<(std::ostream& os, const HoeDivision& division);
std::ostream& operator<<(std::ostream& os, const HoeModulo& modulo);
std::ostream& operator<<(std::ostream& os, const HoeExpression& expression);
std::ostream& operator<<(std::ostream& os, const HoeValexpr& valexpr);
std::ostream& operator<<(std::ostream& os, const HoeValue& value);
std::ostream& operator<<(std::ostream& os, const HoeVariable& variable);
std::ostream& operator<<(std::ostream& os, const HoeConstantVal& constant_val);
std::ostream& operator<<(std::ostream& os, const HoeUkValue03& uk_value_03);
std::ostream& operator<<(std::ostream& os, const HoeFunctionCall& function_call);
std::ostream& operator<<(std::ostream& os, const HoeMathFunction& math_function);
std::ostream& operator<<(std::ostream& os, const HoeUkFunctionCall& uk_function_call);
std::ostream& operator<<(std::ostream& os, const HoeReturn& ret);
std::ostream& operator<<(std::ostream& os, const HoeString& str);

std::ostream& operator<<(std::ostream& os, const HoeArgument& argument);
std::ostream& operator<<(std::ostream& os, const HoeImmediateArg& immediate_arg);
std::ostream& operator<<(std::ostream& os, const HoeConstantArg& constant_arg);