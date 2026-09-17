#include "hoe_script.hh"

#include "fileread/fileread.hh"
#include "filewrite/filewrite.hh"
#include "utils/utils.hh"

class HoeEvent
{
public:
    std::string getHoeVariableName(size_t index);
    HoeConstant* getHoeConstant(size_t index);
};

/*
** INDENT
*/

int Indent::indent_ = 0;
void Indent::initializeIndent()
{
    indent_ = 0;
}

void Indent::increaseIndent()
{
    indent_++;
}

void Indent::decreaseIndent()
{
    indent_--;
}

void Indent::printIndent(std::ostream& os)
{
    for (int i = 0; i < indent_; i++)
    {
        os << "    ";
    }
}

int Indent::getIndent()
{
    return indent_;
}

/*
** DEBUG OFFSET
*/

size_t DebugOffset::offset_ = 0;

void DebugOffset::setOffset(size_t offset)
{
    offset_ = offset;
}

size_t DebugOffset::getOffset()
{
    return offset_;
}

/*
** CURRENT EVENT
*/

HoeEvent* CurrentEvent::current_event_ = nullptr;

HoeEvent* CurrentEvent::getCurrentEvent()
{
    return current_event_;
}

void CurrentEvent::setCurrentEvent(HoeEvent* event)
{
    current_event_ = event;
}

/*
** HOE IMMEDIATEARG
*/
HoeImmediateArg::HoeImmediateArg(std::uint32_t value)
    : HoeArgument(HoeArgumentType::IMMEDIATE)
    , value_(value)
{}

HoeImmediateArg* HoeImmediateArg::parseImmediateArg(std::ifstream& file)
{
    std::uint32_t value = fileread::read4ByteMsb(file);
    HoeImmediateArg* immediate_arg = new HoeImmediateArg(value);
    return immediate_arg;
}

std::uint32_t HoeImmediateArg::getValue() const
{
    return value_;
}

void HoeImmediateArg::setValue(std::uint32_t value)
{
    value_ = value;
}

/*
** HOE CONSTANTARG
*/

HoeConstantArg::HoeConstantArg()
    : HoeArgument(HoeArgumentType::HOE_CONSTANT)
    , expression_(nullptr)
{}

HoeConstantArg::~HoeConstantArg()
{
    if (expression_)
    {
        delete expression_;
    }
}

HoeConstantArg* HoeConstantArg::parseConstantArg(std::ifstream& file)
{
    HoeConstantArg* constant_arg = new HoeConstantArg();
    HoeExpression* expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete constant_arg;
        return nullptr;
    }
    constant_arg->setExpression(expression);
    return constant_arg;
}

HoeExpression* HoeConstantArg::getExpression()
{
    return expression_;
}

const HoeExpression* HoeConstantArg::getExpression() const
{
    return expression_;
}

void HoeConstantArg::setExpression(HoeExpression* expression)
{
    expression_ = expression;
}

/*
** HOE ARGUMENT
*/

HoeArgument::HoeArgument(HoeArgumentType type)
    : type_(type)
{}

HoeArgument::~HoeArgument()
{}

HoeArgument* HoeArgument::parseArgument(std::ifstream& file)
{
    std::uint8_t type = fileread::read1Byte(file);
    HoeArgumentType argument_type = static_cast<HoeArgumentType>(type);

    if (argument_type == HoeArgumentType::IMMEDIATE)
    {
        return HoeImmediateArg::parseImmediateArg(file);
    }

    return HoeConstantArg::parseConstantArg(file);
}

/*
**  HOE VARIABLE
*/
HoeVariable::HoeVariable(std::uint32_t index)
    : HoeValue(HoeValueType::VARIABLE)
    , index_(index)
    , name_("")
{}

HoeVariable* HoeVariable::parseVariable(std::ifstream& file)
{
    std::uint32_t index = fileread::read4ByteMsb(file);
    HoeVariable* variable = new HoeVariable(index);
    std::string name = CurrentEvent::getCurrentEvent()->getHoeVariableName(
        index
    );

    if (name != "")
    {
        variable->setName(name);
    }
    return variable;
}

std::uint32_t HoeVariable::getIndex() const
{
    return index_;
}

const std::string& HoeVariable::getName() const
{
    return name_;
}

void HoeVariable::setName(const std::string& name)
{
    name_ = name;
}

/*
** HOE CONSTANT VAL
*/
HoeConstantVal::HoeConstantVal(std::uint32_t index)
    : HoeValue(HoeValueType::HOE_CONSTANT)
    , index_(index)
{}

HoeConstantVal* HoeConstantVal::parseConstantVal(std::ifstream& file)
{
    std::uint32_t index = fileread::read4ByteMsb(file);
    HoeConstantVal* constant_val = new HoeConstantVal(index);
    HoeConstant* constant = CurrentEvent::getCurrentEvent()->getHoeConstant(
        index
    );
    constant_val->setConstant(constant);
    return constant_val;
}

std::uint32_t HoeConstantVal::getIndex() const
{
    return index_;
}

HoeConstant* HoeConstantVal::getConstant() const
{
    return constant_;
}

void HoeConstantVal::setConstant(HoeConstant* constant)
{
    constant_ = constant;
}

/*
**  HOE UK VALUE 03
*/
HoeUkValue03::HoeUkValue03(std::uint32_t uk_int)
    : HoeValue(HoeValueType::UK_VALUE_TYPE_03)
    , uk_int_(uk_int)
{}

HoeUkValue03* HoeUkValue03::parseUkValue03(std::ifstream& file)
{
    std::uint32_t uk_int = fileread::read4ByteMsb(file);
    HoeUkValue03* uk_value_03 = new HoeUkValue03(uk_int);
    return uk_value_03;
}

std::uint32_t HoeUkValue03::getUkInt() const
{
    return uk_int_;
}

/*
**  HOE FUNCTION CALL
*/
HoeFunctionCall::HoeFunctionCall(std::string& name)
    : HoeValue(HoeValueType::FUNCTION_CALL)
    , name_(name)
{}

std::string HoeFunctionCall::getName() const
{
    return name_;
}

std::vector<HoeArgument*>& HoeFunctionCall::getArguments()
{
    return arguments_;
}

const std::vector<HoeArgument*>& HoeFunctionCall::getArguments() const
{
    return arguments_;
}

HoeFunctionCall* HoeFunctionCall::parseFunctionCall(std::ifstream& file)
{
    std::string name = fileread::readLString(file);
    HoeFunctionCall* function_call = new HoeFunctionCall(name);

    std::uint32_t nb_arguments = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_arguments; i++)
    {
        HoeArgument* argument = HoeArgument::parseArgument(file);
        function_call->getArguments().push_back(argument);
    }

    return function_call;
}

/*
** HOE MATH FUNCTION
*/
HoeMathFunction::HoeMathFunction(HoeMathFunctionType type)
    : HoeValue(HoeValueType::MATH_FUNCTION)
    , type_(type)
    , expression_(nullptr)
{}

HoeMathFunction* HoeMathFunction::parseMathFunction(std::ifstream& file)
{
    std::uint32_t type_u = fileread::read4ByteMsb(file);
    HoeMathFunctionType type = static_cast<HoeMathFunctionType>(type_u);

    HoeMathFunction* math_function = new HoeMathFunction(type);
    std::uint32_t uk_int = fileread::read4ByteMsb(file);
    math_function->setUkInt(uk_int);
    HoeExpression* expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        delete math_function;
        return nullptr;
    }
    math_function->setExpression(expression);

    return math_function;
}

HoeMathFunctionType HoeMathFunction::getType() const
{
    return type_;
}

std::uint32_t HoeMathFunction::getUkInt() const
{
    return uk_int_;
}

HoeExpression* HoeMathFunction::getExpression() const
{
    return expression_;
}

void HoeMathFunction::setUkInt(std::uint32_t uk_int)
{
    uk_int_ = uk_int;
}

void HoeMathFunction::setExpression(HoeExpression* expression)
{
    expression_ = expression;
}

/*
**  HOE UK FUNCTION CALL
*/
// TODO: is this clean? we change the value type after calling the function call
// constructor
HoeUkFunctionCall::HoeUkFunctionCall(std::string& name)
    : HoeFunctionCall(name)
{
    type_ = HoeValueType::UK_FUNCTION_CALL;
}

/*
** HOE RETURN
*/
HoeReturn::HoeReturn()
    : HoeValue(HoeValueType::RETURN)
{}

HoeReturn* HoeReturn::parseReturn(std::ifstream& file)
{
    return new HoeReturn();
}

/*
** HOE STRING
*/

HoeString::HoeString(const std::string& name)
    : HoeValue(HoeValueType::STRING)
    , name_(name)
{}

HoeString* HoeString::parseString(std::ifstream& file)
{
    std::string name = fileread::readLString(file);
    HoeString* hoe_string = new HoeString(name);
    return hoe_string;
}
const std::string& HoeString::getName() const
{
    return name_;
}

/*
**  HOE VALUE
*/
HoeValue::HoeValue(HoeValueType type)
    : type_(type)
{}

HoeValue* HoeValue::parseValue(std::ifstream& file)
{
    std::uint32_t type = fileread::read4ByteMsb(file);
    HoeValueType value_type = static_cast<HoeValueType>(type);
    
    switch (value_type)
    {
    case HoeValueType::VARIABLE:
        return HoeVariable::parseVariable(file);
    case HoeValueType::HOE_CONSTANT:
        return HoeConstantVal::parseConstantVal(file);
    case HoeValueType::UK_VALUE_TYPE_03:
        return HoeUkValue03::parseUkValue03(file);
    case HoeValueType::FUNCTION_CALL:
        return HoeFunctionCall::parseFunctionCall(file);
    case HoeValueType::MATH_FUNCTION:
        return HoeMathFunction::parseMathFunction(file);
    case HoeValueType::UK_FUNCTION_CALL:
        return HoeUkFunctionCall::parseFunctionCall(file);
    case HoeValueType::RETURN:
        return HoeReturn::parseReturn(file);
    case HoeValueType::STRING:
        return HoeString::parseString(file);
    default:
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        return nullptr;
    }

    return nullptr;
}

/*
** HOE VALEXPR
*/

HoeValexpr::HoeValexpr()
    : HoeExpression(HoeExpressionType::VALUE)
    , value_(nullptr)
{}

HoeValexpr::~HoeValexpr()
{
    if (value_)
    {
        delete value_;
    }
}

HoeValexpr* HoeValexpr::parseValexpr(std::ifstream& file)
{
    HoeValexpr* valexpr = new HoeValexpr();
    HoeValue* value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete valexpr;
        return nullptr;
    }
    valexpr->setValue(value);
    return valexpr;
}

HoeValue* HoeValexpr::getValue() const
{
    return value_;
}

void HoeValexpr::setValue(HoeValue* value)
{
    value_ = value;
}

/*
** HOE ADDITION
*/

HoeAddition::HoeAddition()
    : HoeOperation(HoeExpressionType::ADDITION)
{}

HoeAddition::~HoeAddition()
{}

HoeAddition* HoeAddition::parseAddition(std::ifstream& file)
{
    HoeAddition* addition = new HoeAddition();
    HoeValue* value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete addition;
        return nullptr;
    }

    addition->setValue1(value);

    value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete addition;
        return nullptr;
    }

    addition->setValue2(value);
    return addition;
}

/*
** HOE SUBTRACTION
*/

HoeSubtraction::HoeSubtraction()
    : HoeOperation(HoeExpressionType::SUBTRACTION)
{}

HoeSubtraction::~HoeSubtraction()
{}

HoeSubtraction* HoeSubtraction::parseSubtraction(std::ifstream& file)
{
    HoeSubtraction* subtraction = new HoeSubtraction();
    HoeValue* value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete subtraction;
        return nullptr;
    }

    subtraction->setValue1(value);
    value = HoeValue::parseValue(file);

    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete subtraction;
        return nullptr;
    }

    subtraction->setValue2(value);
    return subtraction;
}

/*
** HOE MULTIPLICATION
*/

HoeMultiplication::HoeMultiplication()
    : HoeOperation(HoeExpressionType::MULTIPLICATION)
{}

HoeMultiplication::~HoeMultiplication()
{}

HoeMultiplication* HoeMultiplication::parseMultiplication(std::ifstream& file)
{
    HoeMultiplication* multiplication = new HoeMultiplication();
    HoeValue* value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete multiplication;
        return nullptr;
    }

    multiplication->setValue1(value);

    value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete multiplication;
        return nullptr;
    }

    multiplication->setValue2(value);
    return multiplication;
}

/*
** HOE DIVISION
*/

HoeDivision::HoeDivision()
    : HoeOperation(HoeExpressionType::DIVISION)
{}

HoeDivision::~HoeDivision()
{}

HoeDivision* HoeDivision::parseDivision(std::ifstream& file)
{
    HoeDivision* division = new HoeDivision();
    HoeValue* value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete division;
        return nullptr;
    }

    division->setValue1(value);
    value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete division;
        return nullptr;
    }
    division->setValue2(value);
    return division;
}

/*
** HOE MODULO
*/

HoeModulo::HoeModulo()
    : HoeOperation(HoeExpressionType::MODULO)
{}

HoeModulo::~HoeModulo()
{}

HoeModulo* HoeModulo::parseModulo(std::ifstream& file)
{
    HoeModulo* modulo = new HoeModulo();
    HoeValue* value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete modulo;
        return nullptr;
    }
    modulo->setValue1(value);
    value = HoeValue::parseValue(file);
    if (!value)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete modulo;
        return nullptr;
    }
    modulo->setValue2(value);
    return modulo;
}

/*
** HOE OPERATION
*/
HoeOperation::HoeOperation(HoeExpressionType expression_type)
    : HoeExpression(expression_type)
    , value1_(nullptr)
    , value2_(nullptr)
{}

HoeOperation::~HoeOperation()
{
    if (value1_)
    {
        delete value1_;
    }
    if (value2_)
    {
        delete value2_;
    }
}

HoeValue* HoeOperation::getValue1()
{
    return value1_;
}

HoeValue* HoeOperation::getValue2()
{
    return value2_;
}

const HoeValue* HoeOperation::getValue1() const
{
    return value1_;
}

const HoeValue* HoeOperation::getValue2() const
{
    return value2_;
}

void HoeOperation::setValue1(HoeValue* value1)
{
    value1_ = value1;
}

void HoeOperation::setValue2(HoeValue* value2)
{
    value2_ = value2;
}

/*
** HOE EXPRESSION
*/

HoeExpression::HoeExpression(HoeExpressionType expression_type)
    : expression_type_(expression_type)
{}

HoeExpression::~HoeExpression()
{}

HoeExpression* HoeExpression::parseExpression(std::ifstream& file)
{
    std::uint32_t type = fileread::read4ByteMsb(file);
    HoeExpressionType expression_type = static_cast<HoeExpressionType>(type);

    switch (expression_type)
    {
    case HoeExpressionType::VALUE:
        return HoeValexpr::parseValexpr(file);
    case HoeExpressionType::ADDITION:
        return HoeAddition::parseAddition(file);
    case HoeExpressionType::SUBTRACTION:
        return HoeSubtraction::parseSubtraction(file);
    case HoeExpressionType::MULTIPLICATION:
        return HoeMultiplication::parseMultiplication(file);
    case HoeExpressionType::DIVISION:
        return HoeDivision::parseDivision(file);
    case HoeExpressionType::MODULO:
        return HoeModulo::parseModulo(file);
    default:
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        return nullptr;
    }

    return nullptr;
}

HoeExpressionType HoeExpression::getExpressionType()
{
    return expression_type_;
}

void HoeExpression::getExpressionType(HoeExpressionType expression_type)
{
    expression_type_ = expression_type;
}

/*
** HOE ASSIGN
*/
HoeAssign::HoeAssign()
    : HoeBlock(HoeOpCode::ASSIGN)
    , expression1_(nullptr)
    , expression2_(nullptr)
{}

HoeAssign::~HoeAssign()
{
    if (expression1_)
    {
        delete expression1_;
    }
    if (expression2_)
    {
        delete expression2_;
    }
}

HoeAssign* HoeAssign::parseAssign(std::ifstream& file)
{
    HoeAssign* assign = new HoeAssign();
    HoeExpression* expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete assign;
        return nullptr;
    }
    assign->setExpression1(expression);
    expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete assign;
        return nullptr;
    }
    assign->setExpression2(expression);
    return assign;
}

HoeExpression* HoeAssign::getExpression1()
{
    return expression1_;
}

HoeExpression* HoeAssign::getExpression2()
{
    return expression2_;
}

const HoeExpression* HoeAssign::getExpression1() const
{
    return expression1_;
}

const HoeExpression* HoeAssign::getExpression2() const
{
    return expression2_;
}

void HoeAssign::setExpression1(HoeExpression* expression1)
{
    expression1_ = expression1;
}

void HoeAssign::setExpression2(HoeExpression* expression2)
{
    expression2_ = expression2;
}

/*
** HOE EQUAL
*/
HoeEqual::HoeEqual()
    : HoeComparison(HoeOpCode::EQUAL)
{}

HoeEqual::~HoeEqual()
{}

/*
** HOE NOT EQUAL
*/
HoeNotEqual::HoeNotEqual()
    : HoeComparison(HoeOpCode::NOT_EQUAL)
{}

HoeNotEqual::~HoeNotEqual()
{}

/*
** HOE GREATER THAN
*/
HoeGreaterThan::HoeGreaterThan()
    : HoeComparison(HoeOpCode::GREATER_THAN)
{}

HoeGreaterThan::~HoeGreaterThan()
{}

/*
** HOE LOWER THAN
*/
HoeLowerThan::HoeLowerThan()
    : HoeComparison(HoeOpCode::LOWER_THAN)
{}

HoeLowerThan::~HoeLowerThan()
{}

/*
** HOE GREATER OR EQUAL
*/
HoeGreaterOrEqual::HoeGreaterOrEqual()
    : HoeComparison(HoeOpCode::GREATER_OR_EQUAL)
{}

HoeGreaterOrEqual::~HoeGreaterOrEqual()
{}

/*
** HOE LOWER OR EQUAL
*/
HoeLowerOrEqual::HoeLowerOrEqual()
    : HoeComparison(HoeOpCode::LOWER_OR_EQUAL)
{}

HoeLowerOrEqual::~HoeLowerOrEqual()
{}

/*
** HOE BOOLEAN
*/

HoeBoolean::HoeBoolean()
    : HoeBlock(HoeOpCode::BOOLEAN)
    , expression_(nullptr)
{}

HoeBoolean::~HoeBoolean()
{
    if (expression_)
    {
        delete expression_;
    }
}

HoeBoolean* HoeBoolean::parseBoolean(std::ifstream& file)
{
    HoeBoolean* boolean = new HoeBoolean();
    HoeExpression* expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete boolean;
        return nullptr;
    }
    boolean->setExpression(expression);
    return boolean;
}

HoeExpression* HoeBoolean::getExpression()
{
    return expression_;
}

const HoeExpression* HoeBoolean::getExpression() const
{
    return expression_;
}

void HoeBoolean::setExpression(HoeExpression* expression)
{
    expression_ = expression;
}

/*
** HOE COMPARISON
*/
HoeComparison::HoeComparison(HoeOpCode op_code)
    : HoeBlock(op_code)
    , expression1_(nullptr)
    , expression2_(nullptr)
{}

HoeComparison::~HoeComparison()
{
    if (expression1_)
    {
        delete expression1_;
    }

    if (expression2_)
    {
        delete expression2_;
    }
}

HoeComparison* HoeComparison::parseComparison(std::ifstream& file,
    HoeOpCode op_code)
{
    HoeComparison* comparison = nullptr;
    switch (op_code)
    {
    case HoeOpCode::EQUAL:
        comparison = new HoeEqual();
        break;
    case HoeOpCode::NOT_EQUAL:
        comparison = new HoeNotEqual();
        break;
    case HoeOpCode::GREATER_THAN:
        comparison = new HoeGreaterThan();
        break;
    case HoeOpCode::LOWER_THAN:
        comparison = new HoeLowerThan();
        break;
    case HoeOpCode::GREATER_OR_EQUAL:
        comparison = new HoeGreaterOrEqual();
        break;
    case HoeOpCode::LOWER_OR_EQUAL:
        comparison = new HoeLowerOrEqual();
        break;
    default:
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        return nullptr;
    }

    HoeExpression* expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete comparison;
        return nullptr;
    }
    comparison->setExpression1(expression);
    expression = HoeExpression::parseExpression(file);
    if (!expression)
    {
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        delete comparison;
        return nullptr;
    }
    comparison->setExpression2(expression);

    return comparison;
}

HoeExpression* HoeComparison::getExpression1()
{
    return expression1_;
}

HoeExpression* HoeComparison::getExpression2()
{
    return expression2_;
}

const HoeExpression* HoeComparison::getExpression1() const
{
    return expression1_;
}

const HoeExpression* HoeComparison::getExpression2() const
{
    return expression2_;
}

void HoeComparison::setExpression1(HoeExpression* expression1)
{
    expression1_ = expression1;
}

void HoeComparison::setExpression2(HoeExpression* expression2)
{
    expression2_ = expression2;
}

/*
** HOE IF THEN IFS
*/

HoeIfThenIf::HoeIfThenIf()
    : HoeIfThen(HoeIfThenType::IF_THEN_IF)
{}

HoeIfThenIf::~HoeIfThenIf()
{
    for (HoeIfThen* if_then : body_)
    {
        delete if_then;
    }
}

HoeIfThenIf* HoeIfThenIf::parseIfThenIf(std::ifstream& file)
{
    HoeIfThenIf* if_then_if = new HoeIfThenIf();

    std::uint32_t nb_blocks = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_blocks; i++)
    {
        HoeBlock* block = HoeBlock::parseBlock(file);
        if (!block)
        {
            auto pos = file.tellg();
            DebugOffset::setOffset(pos);
            delete if_then_if;
            return nullptr;
        }
        if_then_if->getConditions().push_back(block);
    }

    std::uint32_t body_size = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < body_size; i++)
    {
        HoeIfThen* if_then = HoeIfThen::parseIfThen(file);
        if (!if_then)
        {
            auto pos = file.tellg();
            DebugOffset::setOffset(pos);
            delete if_then_if;
            return nullptr;
        }
        if_then_if->getBody().push_back(if_then);
    }

    return if_then_if;
}

std::vector<HoeIfThen*>& HoeIfThenIf::getBody()
{
    return body_;
}

const std::vector<HoeIfThen*>& HoeIfThenIf::getBody() const
{
    return body_;
}

/*
** HOE IF THEN BLOCKS
*/

HoeIfThenBlocks::HoeIfThenBlocks()
    : HoeIfThen(HoeIfThenType::IF_THEN_BLOCKS)
{}

HoeIfThenBlocks::~HoeIfThenBlocks()
{
    for (HoeBlock* block : body_)
    {
        delete block;
    }
}

HoeIfThenBlocks* HoeIfThenBlocks::parseIfThenBlocks(std::ifstream& file)
{
    HoeIfThenBlocks* if_then_blocks = new HoeIfThenBlocks();

    std::uint32_t nb_blocks = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_blocks; i++)
    {
        HoeBlock* block = HoeBlock::parseBlock(file);
        if (!block)
        {
            auto pos = file.tellg();
            DebugOffset::setOffset(pos);
            delete if_then_blocks;
            return nullptr;
        }
        if_then_blocks->getConditions().push_back(block);
    }

    std::uint32_t body_size = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < body_size; i++)
    {
        HoeBlock* block = HoeBlock::parseBlock(file);
        if (!block)
        {
            auto pos = file.tellg();
            DebugOffset::setOffset(pos);
            delete if_then_blocks;
            return nullptr;
        }
        if_then_blocks->getBody().push_back(block);
    }

    return if_then_blocks;
}

std::vector<HoeBlock*>& HoeIfThenBlocks::getBody()
{
    return body_;
}

const std::vector<HoeBlock*>& HoeIfThenBlocks::getBody() const
{
    return body_;
}

/*
** HOE IF THEN
*/

HoeIfThen::HoeIfThen(HoeIfThenType type)
    : type_(type)
{}

HoeIfThen::~HoeIfThen()
{
    for (HoeBlock* block : conditions_)
    {
        delete block;
    }
}

HoeIfThen* HoeIfThen::parseIfThen(std::ifstream& file)
{
    std::uint8_t type = fileread::read1Byte(file);
    HoeIfThenType if_then_type = static_cast<HoeIfThenType>(type);

    switch (if_then_type)
    {
    case HoeIfThenType::IF_THEN_BLOCKS:
        return HoeIfThenBlocks::parseIfThenBlocks(file);
    case HoeIfThenType::IF_THEN_IF:
        return HoeIfThenIf::parseIfThenIf(file);
    default:
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        return nullptr;
    }

    return nullptr;
}

std::vector<HoeBlock*>& HoeIfThen::getConditions()
{
    return conditions_;
}

const std::vector<HoeBlock*>& HoeIfThen::getConditions() const
{
    return conditions_;
}

/*
** HOE BLOCK
*/
HoeBlock::HoeBlock(HoeOpCode op_code)
    : op_code_(op_code)
{}

HoeBlock::HoeBlock(const HoeBlock& other)
    : op_code_(other.op_code_)
    , not_(other.not_)
{}

HoeBlock* HoeBlock::parseBlock(std::ifstream& file)
{
    std::uint32_t code = fileread::read4ByteMsb(file);
    HoeOpCode op_code = static_cast<HoeOpCode>(code);

    std::uint32_t not_u = fileread::read4ByteMsb(file);
    bool not_bool = !!not_u;

    HoeBlock* block = nullptr;
    switch (op_code)
    {
    case HoeOpCode::ASSIGN:
        block = HoeAssign::parseAssign(file);
        break;
    case HoeOpCode::EQUAL:
    case HoeOpCode::NOT_EQUAL:
    case HoeOpCode::GREATER_THAN:
    case HoeOpCode::LOWER_THAN:
    case HoeOpCode::GREATER_OR_EQUAL:
    case HoeOpCode::LOWER_OR_EQUAL:
        block = HoeComparison::parseComparison(file, op_code);
        break;
    case HoeOpCode::BOOLEAN:
        block = HoeBoolean::parseBoolean(file);
        break;
    default:
        auto pos = file.tellg();
        DebugOffset::setOffset(pos);
        return nullptr;
    }

    if (block)
    {
        block->setNot(not_bool);
    }

    return block;
}

bool HoeBlock::getNot() const
{
    return not_;
}

void HoeBlock::setNot(bool not_bool)
{
    not_ = not_bool;
}
/*
** HOE MASK
*/

HoeMask::HoeMask(const std::string& name)
    : name_(name)
{}

const std::string& HoeMask::getName() const
{
    return name_;
}

std::vector<std::uint32_t>& HoeMask::getUkInts()
{
    return uk_ints_;
}

const std::vector<std::uint32_t>& HoeMask::getUkInts() const
{
    return uk_ints_;
}

std::vector<std::uint32_t>& HoeMask::getM1()
{
    return m1_;
}

const std::vector<std::uint32_t>& HoeMask::getM1() const
{
    return m1_;
}

std::uint32_t HoeMask::getUkInt1() const
{
    return uk_int1_;
}

std::uint32_t HoeMask::getUkInt2() const
{
    return uk_int2_;
}

HoeBlock* HoeMask::getBlock() const
{
    return block_;
}

std::uint32_t HoeMask::getUkInt3() const
{
    return uk_int3_;
}

HoeExpression* HoeMask::getExpression() const
{
    return expression_;
}

void HoeMask::setUkInt1(std::uint32_t uk_int)
{
    uk_int1_ = uk_int;
}

void HoeMask::setUkInt2(std::uint32_t uk_int)
{
    uk_int2_ = uk_int;
}

void HoeMask::setBlock(HoeBlock* block)
{
    block_ = block;
}

void HoeMask::setUkInt3(std::uint32_t uk_int)
{
    uk_int3_ = uk_int;
}

void HoeMask::setExpression(HoeExpression* expression)
{
    expression_ = expression;
}

/*
** HOE SCRIPT
*/

HoeScript::HoeScript()
    : mask_(nullptr)
{}

HoeScript::HoeScript(const HoeScript& other)
    : mask_(other.mask_)
    , blocks_(other.blocks_)
    , if_thens_(other.if_thens_)
{}

HoeScript::~HoeScript()
{
    for (HoeBlock* block : blocks_)
    {
        delete block;
    }

    for (HoeIfThen* if_then : if_thens_)
    {
        delete if_then;
    }
}

void HoeScript::parseHoeMask(std::ifstream& file)
{
    std::string name = fileread::readLString(file);
    HoeMask* mask = new HoeMask(name);

    std::uint32_t nb_uk_ints = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_uk_ints; i++)
    {
        std::uint32_t uk_int = fileread::read4ByteMsb(file);
        mask->getUkInts().push_back(uk_int);
    }

    std::uint32_t nb_m1 = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_m1; i++)
    {
        std::uint32_t m1 = fileread::read4ByteMsb(file);
        mask->getM1().push_back(m1);
    }

    mask->setUkInt1(fileread::read4ByteMsb(file));
    mask->setUkInt2(fileread::read4ByteMsb(file));
    mask->setBlock(HoeBlock::parseBlock(file));
    mask->setUkInt3(fileread::read4ByteMsb(file));
    mask->setExpression(HoeExpression::parseExpression(file));

    mask_ = mask;
}

int HoeScript::parseHoeScript(std::ifstream& file)
{
    std::uint32_t nb_blocks = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_blocks; i++)
    {
        HoeBlock* block = HoeBlock::parseBlock(file);
        if (!block)
        {
            auto pos = file.tellg();
            DebugOffset::setOffset(pos);
            return 1;
        }

        blocks_.push_back(block);
    }

    std::uint32_t nb_if_thens = fileread::read4ByteMsb(file);
    for (std::uint32_t i = 0; i < nb_if_thens; i++)
    {
        HoeIfThen* if_then = HoeIfThen::parseIfThen(file);
        if (!if_then)
        {
            auto pos = file.tellg();
            DebugOffset::setOffset(pos);
            return 1;
        }

        if_thens_.push_back(if_then);
    }

    return 0;
}

HoeMask* HoeScript::getMask()
{
    return mask_;
}

std::vector<HoeBlock*>& HoeScript::getBlocks()
{
    return blocks_;
}

const std::vector<HoeBlock*>& HoeScript::getBlocks() const
{
    return blocks_;
}

std::vector<HoeIfThen*>& HoeScript::getIfThens()
{
    return if_thens_;
}

const std::vector<HoeIfThen*>& HoeScript::getIfThens() const
{
    return if_thens_;
}

void HoeScript::setMask(HoeMask* mask)
{
    mask_ = mask;
}

/*
** << OPERATOR
*/
std::ostream& operator<<(std::ostream& os, const HoeScript& script)
{
    int i = 0;
    for (HoeBlock* block : script.getBlocks())
    {
        if (i)
        {
            Indent::printIndent(os);
        }
        os << *block << std::endl;
        i++;
    }

    if (i != 0)
    {
        Indent::printIndent(os);
    }
    os << "while (true) {" << std::endl;
    Indent::increaseIndent();
    for (HoeIfThen* if_then : script.getIfThens())
    {
        Indent::printIndent(os);
        os << *if_then << std::endl;
    }

    Indent::decreaseIndent();
    Indent::printIndent(os);
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeIfThenBlocks& if_then_blocks)
{
    if (if_then_blocks.getConditions().size() == 0)
    {
        int j = 0;
        for (HoeBlock* block : if_then_blocks.getBody())
        {
            if (j)
            {
                os << std::endl;
                Indent::printIndent(os);
            }
            os << *block;
            j++;
        }
        return os;
    }

    int i = 0;
    os << "if (";
    for (HoeBlock* block : if_then_blocks.getConditions())
    {
        if (i)
        {
            os << " && ";
        }
        os << *block;
        i++;
    }
    os << ")" << std::endl;
    Indent::printIndent(os);
    os << "{" << std::endl;
    Indent::increaseIndent();
    for (HoeBlock* block : if_then_blocks.getBody())
    {
        Indent::printIndent(os);
        os /* << "    " */ << *block << std::endl;
        i++;
    }
    Indent::decreaseIndent();
    Indent::printIndent(os);
    os << "}" /* << std::endl */;
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeIfThenIf& if_then_if)
{
    if (if_then_if.getConditions().size() == 0)
    {
        int j = 0;
        for (HoeIfThen* if_then : if_then_if.getBody())
        {
            if (j)
            {
                os << std::endl;
                Indent::printIndent(os);
            }
            os << *if_then;
            j++;
        }
        return os;
    }

    int i = 0;
    os << "if (";
    for (HoeBlock* block : if_then_if.getConditions())
    {
        if (i)
        {
            os << " && ";
        }
        os << *block;
        i++;
    }
    os << ")" << std::endl;
    Indent::printIndent(os);
    os << "{" << std::endl;
    Indent::increaseIndent();
    for (HoeIfThen* if_then : if_then_if.getBody())
    {
        Indent::printIndent(os);
        os /* << "    " */<< *if_then << std::endl;
        i++;
    }
    Indent::decreaseIndent();
    Indent::printIndent(os);
    os << "}" /* << std::endl */;
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeIfThen& if_then)
{
    const HoeIfThenBlocks* if_then_blocks = dynamic_cast<const HoeIfThenBlocks*>(&if_then);
    if (if_then_blocks)
    {
        os << *if_then_blocks;
    }

    const HoeIfThenIf* if_then_if = dynamic_cast<const HoeIfThenIf*>(&if_then);
    if (if_then_if)
    {
        os << *if_then_if;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeBlock& block)
{
    if (block.getNot())
    {
        os << "NOT ";
    }

    const HoeAssign* assign = dynamic_cast<const HoeAssign*>(&block);
    if (assign)
    {
        os << *assign;
    }

    const HoeBoolean* boolean = dynamic_cast<const HoeBoolean*>(&block);
    if (boolean)
    {
        os << *boolean;
    }

    const HoeComparison* comparison = dynamic_cast<const HoeComparison*>(&block);
    if (comparison)
    {
        os << *comparison;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeAssign& assign)
{
    os << *(assign.getExpression1()) << " = " << *(assign.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeBoolean& boolean)
{
    os << *(boolean.getExpression());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeComparison& comparison)
{
    const HoeEqual* equal = dynamic_cast<const HoeEqual*>(&comparison);
    if (equal)
    {
        os << *equal;
    }

    const HoeNotEqual* not_equal = dynamic_cast<const HoeNotEqual*>(&comparison);
    if (not_equal)
    {
        os << *not_equal;
    }

    const HoeGreaterThan* greater_than = dynamic_cast<const HoeGreaterThan*>(&comparison);
    if (greater_than)
    {
        os << *greater_than;
    }

    const HoeLowerThan* lower_than = dynamic_cast<const HoeLowerThan*>(&comparison);
    if (lower_than)
    {
        os << *lower_than;
    }

    const HoeGreaterOrEqual* greater_or_equal = dynamic_cast<const HoeGreaterOrEqual*>(&comparison);
    if (greater_or_equal)
    {
        os << *greater_or_equal;
    }

    const HoeLowerOrEqual* lower_or_equal = dynamic_cast<const HoeLowerOrEqual*>(&comparison);
    if (lower_or_equal)
    {
        os << *lower_or_equal;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeEqual& equal)
{
    os << *(equal.getExpression1()) << " == "
        << *(equal.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeNotEqual& not_equal)
{
    os << *(not_equal.getExpression1()) << " != "
        << *(not_equal.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeGreaterThan& greater_than)
{
    os << *(greater_than.getExpression1()) << " > "
        << *(greater_than.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeLowerThan& lower_than)
{
    os << *(lower_than.getExpression1()) << " < "
        << *(lower_than.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeGreaterOrEqual& greater_or_equal)
{
    os << *(greater_or_equal.getExpression1()) << " >= "
        << *(greater_or_equal.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeLowerOrEqual& lower_or_equal)
{
    os << *(lower_or_equal.getExpression1()) << " <= "
        << *(lower_or_equal.getExpression2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeOperation& operation)
{
    const HoeAddition* addition = dynamic_cast<const HoeAddition*>(&operation);
    if (addition)
    {
        os << *addition;
    }

    const HoeSubtraction* subtraction = dynamic_cast<const HoeSubtraction*>(&operation);
    if (subtraction)
    {
        os << *subtraction;
    }

    const HoeMultiplication* multiplication = dynamic_cast<const HoeMultiplication*>(&operation);
    if (multiplication)
    {
        os << *multiplication;
    }

    const HoeDivision* division = dynamic_cast<const HoeDivision*>(&operation);
    if (division)
    {
        os << *division;
    }

    const HoeModulo* modulo = dynamic_cast<const HoeModulo*>(&operation);
    if (modulo)
    {
        os << *modulo;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeAddition& addition)
{
    os << *(addition.getValue1()) << " + " << *(addition.getValue2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeSubtraction& subtraction)
{
    os << *(subtraction.getValue1()) << " - " << *(subtraction.getValue2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeMultiplication& multiplication)
{
    os << *(multiplication.getValue1()) << " * " << *(multiplication.getValue2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeDivision& division)
{
    os << *(division.getValue1()) << " / " << *(division.getValue2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeModulo& modulo)
{
    os << *(modulo.getValue1()) << " % " << *(modulo.getValue2());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeExpression& expression)
{
    const HoeValexpr* valexpr = dynamic_cast<const HoeValexpr*>(&expression);
    if (valexpr)
    {
        os << *valexpr;
    }

    const HoeOperation* operation = dynamic_cast<const HoeOperation*>(&expression);
    if (operation)
    {
        os << *operation;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeValexpr& valexpr)
{
    os << *(valexpr.getValue());
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeValue& value)
{
    const HoeVariable* variable = dynamic_cast<const HoeVariable*>(&value);
    if (variable)
    {
        os << *variable;
        return os;
    }

    const HoeConstantVal* constant = dynamic_cast<const HoeConstantVal*>(&value);
    if (constant)
    {
        os << *constant;
        return os;
    }

    const HoeUkValue03* uk_value_03 = dynamic_cast<const HoeUkValue03*>(&value);
    if (uk_value_03)
    {
        os << *uk_value_03;
        return os;
    }

    const HoeFunctionCall* function_call = dynamic_cast<const HoeFunctionCall*>(&value);
    if (function_call)
    {
        os << *function_call;
        return os;
    }

    const HoeMathFunction* math_function = dynamic_cast<const HoeMathFunction*>(&value);
    if (math_function)
    {
        os << *math_function;
        return os;
    }

    const HoeUkFunctionCall* uk_function_call = dynamic_cast<const HoeUkFunctionCall*>(&value);
    if (uk_function_call)
    {
        os << *uk_function_call;
        return os;
    }

    const HoeReturn* ret = dynamic_cast<const HoeReturn*>(&value);
    if (ret)
    {
        os << *ret;
        return os;
    }

    const HoeString* str = dynamic_cast<const HoeString*>(&value);
    if (str)
    {
        os << *str;
        return os;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeVariable& variable)
{
    if (variable.getName() != "")
    {
        os << variable.getName();
        return os;
    }

    os << "var" << variable.getIndex();
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeConstantVal& constant_val)
{
    if (!constant_val.getConstant())
    {
        os << "hoe_constants[" << constant_val.getIndex() << "]";
        return os;
    }

    os << *(constant_val.getConstant()) << "(hoe_constant)";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeUkValue03& uk_value_03)
{
    os << "UkValue03(" << uk_value_03.getUkInt() << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeFunctionCall& function_call)
{
    os << function_call.getName() << "(";
    int i = 0;
    for (HoeArgument* argument : function_call.getArguments())
    {
        if (i)
        {
            os << ", ";
        }

        os << *argument;
        i++;
    }

    os << ")";

    return os;
}

// TODO: We are not printing the UkInt because it seems to always be 1
// Maybe I should do more research on that
std::ostream& operator<<(std::ostream& os, const HoeMathFunction& math_function)
{
    switch (math_function.getType())
    {
    case HoeMathFunctionType::SIN:
        os << "sin(";
        break;
    case HoeMathFunctionType::ABS:
        os << "abs(";
        break;
    default:
        os << "some_math_function(";
        break;
    }

    os << *(math_function.getExpression());
    os << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeUkFunctionCall& uk_function_call)
{
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeReturn& ret)
{
    os << "return";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeString& str)
{
    os << "string " << str.getName();
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeArgument& argument)
{
    const HoeImmediateArg* immediate_arg = dynamic_cast<const HoeImmediateArg*>(&argument);
    if (immediate_arg)
    {
        os << *immediate_arg;
        return os;
    }

    const HoeConstantArg* constant_arg = dynamic_cast<const HoeConstantArg*>(&argument);
    if (constant_arg)
    {
        os << *constant_arg;
        return os;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeImmediateArg& immediate_arg)
{
    os << immediate_arg.getValue();
    return os;
}

std::ostream& operator<<(std::ostream& os, const HoeConstantArg& constant_arg)
{
    os << *(constant_arg.getExpression());
    return os;
}
