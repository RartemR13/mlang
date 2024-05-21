#include "Condition.h"

Condition::Condition(Expression* f, Expression* s, CompareOperators op) :
    f_(f), s_(s), op_(op) {}

int Condition::eval(const Driver& driver) const {
    int num1 = f_->eval(driver);
    int num2 = f_->eval(driver);

    switch (op_) {
    case CompareOperators::EQUAL:
        return num1 == num2;
        break;

    case CompareOperators::NOT_EQUAL:
        return num1 != num2;
        break;

    default:
        break;
    }

    return 0;
}