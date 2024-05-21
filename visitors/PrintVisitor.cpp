#include "PrintVisitor.h"

#include "elems.h"

#include <iostream>

SymbolTreeVisitor::SymbolTreeVisitor(const std::string& filename) : stream_(filename) {
}

void SymbolTreeVisitor::Visit(NumberExpression* expression) {
    PrintTabs();
    stream_ << "NumExpression " << expression->getValue() << std::endl;
}

void SymbolTreeVisitor::Visit(AddExpression* expression) {
    PrintTabs();
    stream_ << "AddExpression is:" << std::endl;

    ++num_tabs_;
    expression->getFirst()->Accept(this);
    expression->getSecond()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(SubstractExpression* expression) {
    PrintTabs();

    stream_ << "SubExpression: " << std::endl;
    ++num_tabs_;
    expression->getFirst()->Accept(this);
    expression->getSecond()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(MulExpression* expression) {
    PrintTabs();

    stream_ << "MulExpression: " << std::endl;
    ++num_tabs_;
    expression->getFirst()->Accept(this);
    expression->getSecond()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(DivExpression* expression) {
    PrintTabs();
    stream_ << "DivExpression: " << std::endl;
    ++num_tabs_;
    expression->getFirst()->Accept(this);
    expression->getSecond()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(IdentExpression* expression) {
    PrintTabs();

    stream_ << "IdentExpression: " << expression->getIdent() << std::endl;
}

void SymbolTreeVisitor::Visit(Assignment* assignment) {
    PrintTabs();
    stream_ << "Assignment: " << assignment->getVar() << std::endl;
    ++num_tabs_;
    assignment->getExp()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(StatementList* statement_list) {
    PrintTabs();
    stream_ << "StatementList: " << std::endl;

    ++num_tabs_;
    for (Statement* Statement : statement_list->getStatements()) {
        Statement->Accept(this);
    }
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(If* ifs) {
    PrintTabs();
    stream_ << "IfStatement: " << std::endl;

    ++num_tabs_;
    ifs->getCondition()->Accept(this);
    ifs->getL1()->Accept(this);
    if (ifs->getL2()) {
        ifs->getL2()->Accept(this);
    }
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(Condition* condition) {
    PrintTabs();
    stream_ << "Condition: " << static_cast<int>(condition->getOp()) << std::endl;

    ++num_tabs_;
    condition->getF()->Accept(this);
    condition->getS()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(Print* print) {
    PrintTabs();
    stream_ << "Print: " << std::endl;

    ++num_tabs_;
    print->getExpresion()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::PrintTabs() {
    for (int i = 0; i < num_tabs_; ++i) {
        stream_ << '\t';
    }
}

void SymbolTreeVisitor::Visit(Program* program) {
    stream_ << "Scope:" << std::endl;

    ++num_tabs_;
    // std::cout << (program == nullptr) << std::endl;
    // std::cout << program->getStatements()->getStatements().size() << std::endl;
    program->getStatements()->Accept(this);
    --num_tabs_;
}

SymbolTreeVisitor::~SymbolTreeVisitor() {
    stream_.close();
}