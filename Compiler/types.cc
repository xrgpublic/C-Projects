// Compiler Theory and Design
//Xavier Garrido Project 4 3/8/2022

// This file contains the bodies of the type checking functions

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "types.h"
#include "listing.h"

void checkAssignment(Types lValue, Types rValue, string message)
{
	if (lValue == INT_TYPE && rValue == REAL_TYPE) {
		appendError(GENERAL_SEMANTIC, "Illegal Narrowing Variable Initialization");
	}
	else if (lValue == REAL_TYPE && rValue == INT_TYPE) {
		//Do nothing
	}
	else if (lValue == MISMATCH || rValue == MISMATCH || lValue != rValue) {
		appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
		
	}


}

Types checkArithmetic(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == BOOL_TYPE || right == BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Number Type Required");
		return MISMATCH;
	}
	if (left == REAL_TYPE || right == REAL_TYPE)
	{
		return REAL_TYPE;
	}
	else {
		return INT_TYPE;
	}
}

Types checkRemainder(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == BOOL_TYPE || right == BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Number Type Required");
		return MISMATCH;
	}
	else if (right == REAL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Remainder Operator Requires Integer Operands");
	}
	if (left == REAL_TYPE)
	{
		return REAL_TYPE;
	}
	else {
		return INT_TYPE;
	}
}

Types checkLogical(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left != BOOL_TYPE || right != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required");
		return MISMATCH;
	}	
		return BOOL_TYPE;
	return MISMATCH;
}

Types checkIf(Types left, Types ifStatement, Types elseStatement)
{
	if (left != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "If Expression Must Be Boolean");
	}
	if (ifStatement != elseStatement) {
		appendError(GENERAL_SEMANTIC, "If-Then Type Mismatch");
	}
	return elseStatement;
}

Types checkCase(Types caseStatement, Types optionalStatement, Types otherStatement) {

	if (caseStatement != INT_TYPE) {
		appendError(GENERAL_SEMANTIC, "Case Expression Not Integer");
	}
	if (caseStatement != otherStatement) {
		appendError(GENERAL_SEMANTIC, "Case Types Mismatch");
	}
	return INT_TYPE;
}

Types checkNot(Types left)
{
	if (left == MISMATCH)
		return MISMATCH;
	if (left != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required");
		return MISMATCH;
	}
		return BOOL_TYPE;
	return MISMATCH;
}

Types checkReturn(Types left, Types right) {
	//Checks for bool
	if (left != right) {
		if (left == INT_TYPE && right == REAL_TYPE) {
			appendError(GENERAL_SEMANTIC, "Boolean Type Required");
			return MISMATCH;
		}
		else {
			return BOOL_TYPE;
		}
	}


	return BOOL_TYPE;
}

Types checkRelational(Types left, Types right)
{
	if (checkArithmetic(left, right) == MISMATCH)
		return MISMATCH;
	return BOOL_TYPE;
}
