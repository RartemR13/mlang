#pragma once

#include <vector>
#include "Statement.h"

class StatementList : public Statement {
 public:
    void AddStatement(Statement* statement);

    const std::vector<Statement*>& getStatements() {
        return statements_;
    }

    void Accept(Visitor* visitor) override;
 private:
    std::vector<Statement*> statements_;
};