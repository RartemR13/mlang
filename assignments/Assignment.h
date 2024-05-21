#pragma once

#include "statements/Statement.h"

#include <string>

class Assignment : public Statement {
 public:
    Assignment(const std::string& variable, Expression* sta);

   std::string getVar() {
      return variable_;
   }

   Expression* getExp() {
      return exp_;
   }

   void Accept(Visitor* visitor) override {
      visitor->Visit(this);
   }

 private:
    std::string variable_;
    Expression* exp_;
};