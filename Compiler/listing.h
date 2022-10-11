// Compiler Theory and Design
//Xavier Garrido Project 4 3/8/2022

// This file contains the function prototypes for the functions that produce the 
// compilation listing

enum ErrorCategories {LEXICAL, SYNTAX, GENERAL_SEMANTIC, DUPLICATE_IDENTIFIER,
	UNDECLARED};

void firstLine();
void nextLine();
int lastLine();
void appendError(ErrorCategories errorCategory, string message);
void appendError(ErrorCategories errorCategory, string message, string variable);

