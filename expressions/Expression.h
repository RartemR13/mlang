#pragma once
#include "statements/Statement.h"

class Driver;

class Expression : public Statement {
public:
    virtual int eval(const Driver& driver) const = 0;
};