#pragma once

#include "Visitor.h"


#include <fstream>
#include <string>

class SymbolTreeVisitor: public Visitor {
 public:
    SymbolTreeVisitor(const std::string& filename);
    ~SymbolTreeVisitor();
    void Visit(NumberExpression* expression) override;
    void Visit(AddExpression* expression) override;
    void Visit(SubstractExpression* expression) override;
    void Visit(MulExpression* expression) override;
    void Visit(DivExpression* expression) override;
    void Visit(IdentExpression* expression) override;
    void Visit(Assignment* assignment) override;
    void Visit(StatementList* assignment_list) override;
    void Visit(Program* program) override;
    void Visit(If* ifs) override;
    void Visit(Print* print) override;
    void Visit(Condition* condition) override;
 private:

    void PrintTabs();
    std::ofstream stream_;
    int num_tabs_ = 0;

};