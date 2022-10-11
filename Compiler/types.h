// Compiler Theory and Design
//Xavier Garrido Project 4 3/8/2022

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, BOOL_TYPE, REAL_TYPE};

enum ArithmeticOperators { ADD, SUBTRACT, MULTIPLY, DIVIDE, POWER, REM, CASEARROW};

enum RelationalOperators {AND, OR, NOT, EQUAL, NOTEQUAL, GREATER, GREATEREQUAL, LESS, LESSEQUAL};


void checkAssignment(Types lValue, Types rValue, string message);
Types checkArithmetic(Types left, Types right);
Types checkRemainder(Types left, Types right);
Types checkLogical(Types left, Types right);
Types checkIf(Types left, Types ifStatement, Types elseStatement);
Types checkCase(Types caseStatement, Types optionalStatement, Types otherStatement);
Types checkNot(Types left);
Types checkReturn(Types left, Types right);
Types checkRelational(Types left, Types right);