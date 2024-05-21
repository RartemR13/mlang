#include "Interpreter.h"

#include "elems.h"

#include <iostream>

Interpreter::Interpreter() {
    is_tos_expression_ = false;
    tos_value_ = 0;
}

void Interpreter::Visit(NumberExpression* expression) {
    SetTosValue(expression->getValue());
}

void Interpreter::Visit(AddExpression* expression) {
    int value = 0;
    expression->getFirst()->Accept(this);
    value += tos_value_;

    expression->getSecond()->Accept(this);
    value += tos_value_;
    SetTosValue(value);
}

void Interpreter::Visit(SubstractExpression* expression) {
    expression->getFirst()->Accept(this);
    int value = tos_value_;
    expression->getSecond()->Accept(this);
    value -= tos_value_;
    
    SetTosValue(value);
}


void Interpreter::Visit(DivExpression* expression) {
    expression->getFirst()->Accept(this);
    int value = tos_value_;
    expression->getSecond()->Accept(this);
    value /= tos_value_;

    SetTosValue(value);
}

void Interpreter::Visit(MulExpression* expression) {
    expression->getFirst()->Accept(this);
    int value = tos_value_;
    expression->getSecond()->Accept(this);
    value *= tos_value_;
    
    SetTosValue(value);
}

void Interpreter::Visit(IdentExpression* expression) {
    int value = variables_[expression->getIdent()];

    SetTosValue(value);
}

void Interpreter::Visit(Assignment* assignment) {
    assignment->getExp()->Accept(this);
    variables_[assignment->getVar()] = tos_value_;

    UnsetTosValue();
}

void Interpreter::Visit(StatementList* statement_list) {
    for (Statement* assignment: statement_list->getStatements()) {
        assignment->Accept(this);
    }
    UnsetTosValue();
}

void Interpreter::Visit(Program* program) {
    program->getStatements()->Accept(this);
}

void Interpreter::SetTosValue(int value) {
    tos_value_ = value;
    is_tos_expression_ = true;
}

void Interpreter::UnsetTosValue() {
    tos_value_ = 0;
    is_tos_expression_ = false;
}

int Interpreter::GetResult(Program *program) {
    UnsetTosValue();
    Visit(program);
    return tos_value_;
}

void Interpreter::Visit(Print* print) {
    print->getExpresion()->Accept(this);

    std::cout << tos_value_ << std::endl;
    UnsetTosValue();
}

void Interpreter::Visit(Condition* condition) {
    condition->getF()->Accept(this);
    int val1 = tos_value_;

    condition->getS()->Accept(this);
    int val2 = tos_value_;

    switch (condition->getOp()) {
    case CompareOperators::EQUAL:
        SetTosValue(val1 == val2);
        break;
    case CompareOperators::GREATER:
        SetTosValue(val1 > val2);
        break;
    case CompareOperators::GREATER_OR_EQ:
        SetTosValue(val1 >= val2);
        break;
    case CompareOperators::LOWER:
        SetTosValue(val1 < val2);
        break;
    case CompareOperators::LOWER_OR_EQ:
        SetTosValue(val1 <= val2);
        break;
    case CompareOperators::NOT_EQUAL:
        SetTosValue(val1 != val2);
        break;
    default:
        break;
    }
}

void Interpreter::Visit(If* ifs) {
    ifs->getCondition()->Accept(this);

    if (tos_value_) {
        ifs->getL1()->Accept(this);
    } else if (ifs->getL2()) {
        ifs->getL2()->Accept(this);
    }

    UnsetTosValue();
}