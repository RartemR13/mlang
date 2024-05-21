#pragma once

#include "statements/StatementList.h"
#include "expressions/Expression.h"

class Program : public Statement {
 public:
   Program(StatementList* statements);
   StatementList* getStatements() {
      return statements_;
   }
 private:
    StatementList* statements_;
};