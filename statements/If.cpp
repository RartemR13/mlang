#include "If.h"

If::If(Condition* cond, StatementList* l1, StatementList* l2) :
    cond_(cond), l1_(l1), l2_(l2) {}