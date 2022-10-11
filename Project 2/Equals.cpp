#include "Equals.h"
#include "subexpression.h"
#include "expression.h"


double Equals::evaluate() {
    SubExpression::parse();
    if (left = right) {
        return 1;
    }
    return 0;
}