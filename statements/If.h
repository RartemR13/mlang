#pragma once

#include "expressions/Condition.h"
#include "StatementList.h"

class If : public Statement {
public:
    If(Condition* cond, StatementList* l1, StatementList* l2);

    Condition* getCondition() {
        return cond_;
    }

    StatementList* getL1() {
        return l1_;
    }

    StatementList* getL2() {
        return l2_;
    }

       void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }
private:
    Condition* cond_;
    StatementList* l1_;
    StatementList* l2_;
};