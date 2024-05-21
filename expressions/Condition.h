#pragma once

#include "Expression.h"

enum class CompareOperators{
    EQUAL = 1,
    NOT_EQUAL,
    LOWER,
    GREATER,
    LOWER_OR_EQ,
    GREATER_OR_EQ
};

class Condition : public Expression {
public:
    Condition(Expression* f, Expression* s, CompareOperators op);
    virtual int eval(const Driver& driver) const override;

    void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }

   Expression* getF() {
    return f_;
   }

   Expression* getS() {
    return s_;
   }

   CompareOperators getOp() {
    return op_;
   }
private:
    Expression* f_;
    Expression* s_;
    CompareOperators op_;
};