#include <cctype> 
#include <iostream> 
#include <string> 
using namespace std;

#include "parse.h"

string parseName(string& expr)
{
    char alnum;
    string name = "";

    while(isalnum(expr.at(0)))
    {
        alnum = expr.at(0);
        expr.erase(0, 1);
        name += alnum;
    }
    return name;
}