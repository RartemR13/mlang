#pragma once
#include "Expression.h"

#include <string>

class Driver;

class IdentExpression: public Expression {
 public:
    IdentExpression(const std::string& ident);
    int eval(const Driver& driver) const override;

    std::string getIdent() {
      return ident_;
    }

   void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }    
 private:
    std::string ident_;
};