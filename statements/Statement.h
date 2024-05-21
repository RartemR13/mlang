#pragma once
#include <iostream>

#include "visitors/Visitor.h"

class Statement {
public:
    virtual ~Statement() = default;
    virtual void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
protected:
    Statement() = default;
};