#include <iostream>
#include <list>
#include <sstream>
using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "operand.h"
#include "literal.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "Equals.h"
#include "GreaterThan.h"
#include "And.h"
#include "Or.h"
#include "Negate.h"
#include "Condition.h"

SubExpression::SubExpression(Expression* left, Expression* right)
{
    this->left = left;
    this->right = right;
}
SubExpression::SubExpression(Expression* left, Expression* right, Expression* condition)
{
    this->left = left;
    this->right = right;
    this->condition = condition;
}

Expression* SubExpression::parse(string& expr)
{
    Expression* left;
    Expression* right;
    Expression* newLeft;
    Expression* newRight;
    char operation, paren;
    int conditionalControl = 1;
    int control = 0;
   
        left = Operand::parse(expr);
        operation = expr.at(0);
        expr.erase(0, 1);
        right = Operand::parse(expr);
        paren = expr.at(0);
        expr.erase(0, 1);
        switch (operation)
        {
        case '+':
            return new Plus(left, right);
        case '-':
            return new Minus(left, right);
        case '*':
            return new Times(left, right);
        case '/':
            return new Divide(left, right);
        case '>':
            return new GreaterThan(left, right);
        case '<':
            return new GreaterThan(right, left);
        case '=':
            return new Equals(left, right);
        case '&':
            return new And(left, right);
        case '|':
            return new Or(left, right);
        case '!':
            return new Negate(left, right);
        case ':':
            return new Condition(left, right, SubExpression::parse(expr));
        }
    return 0;
}