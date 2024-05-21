#pragma once

#include "Statement.h"

class Print : public Statement {
public:
    explicit Print(Expression* exp);

    Expression* getExpresion() {
        return exp_;
    }

    void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }
private:
    Expression* exp_;
};