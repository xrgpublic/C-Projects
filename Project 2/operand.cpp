#include <cctype>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "operand.h"
#include "variable.h"
#include "literal.h"
#include "parse.h"

Expression* Operand::parse(string& expr)
{
    char paren;
    double value;

    string temp = "";
    if (isdigit(expr.at(0)))
    {
        temp = temp + expr.at(0);
        value = stod(temp);
        expr.erase(0, 1);
        Expression* literal = new Literal(value);
        return literal;
    }
    if (expr.at(0) == '(')
    {
        paren = expr.at(0);
        expr.erase(0, 1);
        return SubExpression::parse(expr);
    }
    else
        return new Variable(parseName(expr));
    return 0;
}