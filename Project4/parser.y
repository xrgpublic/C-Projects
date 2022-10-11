/* Compiler Theory and Design
   Xavier Garrido Project 4 3/8/2022*/

%{

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
void yyerror(const char* message);

Symbols<Types> symbols;

%}

%define parse.error verbose

%union
{
	CharPtr iden;
	double value;
	Types type;
	ArithmeticOperators arithOp;
	RelationalOperators relOp;
}

%token <iden> IDENTIFIER
%token <type> INT_LITERAL REAL_LITERAL BOOL_LITERAL

%token <arithOp> ADDOP MULOP

%token <relOp> ANDOP NOTOP OROP

%token REAL
%token IF THEN ELSE ENDIF
%token CASE ENDCASE OTHERS ARROW
%token WHEN

%token RELOP EXPOP REMOP
%token BEGIN_ BOOLEAN END ENDREDUCE FUNCTION INTEGER IS REDUCE RETURNS

%type <type> function_header body type statement statement_ reductions case expression relation term
	factor exponent remainder primary

%%

function:	
	function_header optional_variable body {checkAssignment($1,$3, "Return");} ;
	
function_header:	
	FUNCTION IDENTIFIER RETURNS type ';' {$$ = $4;} ;

optional_variable:
	variable optional_variable  |
	;

variable:	
	IDENTIFIER ':' type IS statement_ 
		{if (symbols.find($1, $3)) appendError(GENERAL_SEMANTIC, "Duplicate Identifier: ", $1);
		if (!symbols.find($1, $3)) checkAssignment($3, $5, "Variable Initialization"); 
		if (!symbols.find($1, $3)) symbols.insert($1, $3);};

type:
	INTEGER {$$ = INT_TYPE;} |
	REAL {$$ = REAL_TYPE;} |
	BOOLEAN {$$ = BOOL_TYPE;} ;

body:
	BEGIN_ statement_ END ';' { $$ = $2;} ;
    
statement_:
	statement ';' |
	error ';' {$$ = MISMATCH;} ;
	
statement:
	expression |
	REDUCE operator reductions ENDREDUCE {$$ = $3;} |
	IF expression THEN statement_ ELSE statement_ ENDIF {$$ = checkIf($2, $4, $6);}| 
	CASE expression IS optional_case OTHERS ARROW statement_ ENDCASE 
	{ $$ = checkCase($2, INT_TYPE, $7);} ;

optional_case:
	case optional_case |
	;

case:
	WHEN primary ARROW statement_ {if ($2 != INT_TYPE) appendError(GENERAL_SEMANTIC, "Case Expression Not Integer");} |
	error ';' {$$ = MISMATCH;};

operator:
	ADDOP |
	MULOP ;

reductions:
	reductions statement_ {$$ = checkArithmetic($1, $2);} |
	{$$ = INT_TYPE;} ;
		    
expression:
	expression ANDOP relation {$$ = checkLogical($1, $3);} |
	expression OROP relation {$$ = checkLogical($1, $3);} |
	NOTOP relation {$$ = checkNot($2);} |
	relation ;

relation:
	relation RELOP term {$$ = checkRelational($1, $3);}|
	term ;

term:
	term ADDOP factor {$$ = checkArithmetic($1, $3);} |
	factor ;
      
factor:
	factor MULOP remainder  {$$ = checkArithmetic($1, $3);} |
	remainder ;

remainder:
	remainder REMOP exponent {$$ = checkRemainder($1, $3);} |
	exponent;

exponent:
	exponent EXPOP primary {$$ = checkArithmetic($1, $3);} |
	primary;



/* NEEDS TO CHECK FOR REAL AND BOOLEAN */
primary:
	'(' expression ')' {$$ = $2;} |
	INT_LITERAL {$$ = INT_TYPE;} |
	REAL_LITERAL {$$ = REAL_TYPE;} |
	BOOL_LITERAL {$$ = BOOL_TYPE;} | 
	IDENTIFIER {if (!symbols.find($1, $$)) appendError(UNDECLARED, $1);} ;
    
%%

void yyerror(const char* message)
{
	appendError(SYNTAX, message);
}

int main(int argc, char *argv[])    
{
	firstLine();
	yyparse();
	lastLine();
	return 0;
} 
