#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "symboltable.h"
#include "parse.h"

SymbolTable symbolTable;

void parseAssignments(string& strm);

int main()
{
    Expression* expression;
    char paren, comma;
    ifstream file;
    string expr;


    file.open("expressionText.txt", ios::in);
    if (!file)
    {
        cout << "Could not find file" << endl;
        return -1;
    }
    while (getline(file, expr)) {
        try
        {
            expr.erase(std::remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
            cout << "Expression: " + expr <<"\n";
            paren = expr.at(0);
            expr.erase(0, 1);
            expression = SubExpression::parse(expr);
            comma = expr.at(0);
            expr.erase(0, 1);
            parseAssignments(expr);
            cout << "Value = " << expression->evaluate() << endl;
            symbolTable.wipe();
        }
        catch (...)
        {
            cout << "Error: Invalid syntax";
        }
    }
    file.close();


    return 0;
}

void parseAssignments(string& expr)
{
    char assignop, delimiter;
    string variable;
    double value;
    string temp;
    do
    {
        temp = "";
        variable = parseName(expr);
        assignop = expr.at(0);
        expr.erase(0, 1);
        
        if (isdigit(expr.at(0))) {
            temp = temp + expr.at(0);
            expr.erase(0, 1);
        }
        value = stod(temp);
        delimiter = expr.at(0);
        expr.erase(0, 1);

        symbolTable.insert(variable, value);
    } while (delimiter == ',');
}