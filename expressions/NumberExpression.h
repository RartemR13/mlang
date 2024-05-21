#pragma once
#include "Expression.h"

class NumberExpression: public Expression {
public:
    explicit NumberExpression(int value);
    int eval(const Driver& driver) const override;

    int getValue() {
        return value_;
    }

    void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }
private:
    int value_;
};