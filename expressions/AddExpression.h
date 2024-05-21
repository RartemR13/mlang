#pragma once
#include "Expression.h"

class AddExpression: public Expression {
 public:
    AddExpression(Expression* e1, Expression* e2);
    int eval(const Driver& driver) const override;

    Expression* getFirst() {
      return first;
    }

    Expression* getSecond() {
      return second;
    }

    void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }    
 private:
    Expression* first;
    Expression* second;
};