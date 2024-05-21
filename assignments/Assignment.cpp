#include "Assignment.h"

Assignment::Assignment(
    const std::string& variable,
    Expression* exp
) : variable_(variable), exp_(exp) {}