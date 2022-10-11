/* Compiler Theory and Design
   Xavier Garrido Project 4 3/8/2022*/

/* This file contains flex input file */

%{
#include <string>

using namespace std;

#include "types.h"
#include "listing.h"
#include "tokens.h"

%}

%option noyywrap
ws		[ \t\r]+
comment ("//"|"--").*\n
line		[\n]
id		[A-Za-z][A-Za-z0-9]*
digit		[0-9]
double		{digit}+[.]?{digit}*
punc		[\(\),:;]
sNotation	[0-9]+[.][0-9]*([eE]?[+-]?[0-9]+)?
%%

{ws}		{ ECHO; }
{comment}	{ ECHO; nextLine();}
{line}		{ ECHO; nextLine();}
"<"		{ ECHO; yylval.relOp = LESS; return(RELOP); }
"+"		{ ECHO; yylval.arithOp = ADD; return(ADDOP); }
"*"		{ ECHO; yylval.arithOp = MULTIPLY; return(MULOP); }

{sNotation} { ECHO; yylval.iden = (CharPtr)malloc(yyleng + 1); 
			strcpy(yylval.iden, yytext); return(REAL_LITERAL);}
"="		{ ECHO; yylval.relOp = EQUAL; return(RELOP); }
"/="	{ ECHO; yylval.relOp = NOTEQUAL; return(RELOP); }
">"		{ ECHO; yylval.relOp = GREATER; return(RELOP); }
">="	{ ECHO; yylval.relOp = GREATEREQUAL; return(RELOP); }
"<="	{ ECHO; yylval.relOp = LESSEQUAL; return(RELOP); }
or		{ ECHO; yylval.relOp = OR; return(OROP); }
not		{ ECHO; yylval.relOp = NOT; return(NOTOP); }
"-"		{ ECHO; yylval.arithOp = SUBTRACT; return(ADDOP); }
"/"		{ ECHO; yylval.arithOp = DIVIDE; return(MULOP); }
"=>"	{ ECHO; yylval.arithOp = CASEARROW; return(ARROW); }
"**"	{ ECHO; yylval.arithOp = POWER; return(EXPOP); }
case		{ ECHO; return(CASE); }
else		{ ECHO; return(ELSE); }
endcase		{ ECHO; return(ENDCASE); }
endif		{ ECHO; return(ENDIF); }
if			{ ECHO; return(IF); }
others		{ ECHO; return(OTHERS); } 
real		{ ECHO; return(REAL); } 
then		{ ECHO; return(THEN); }
when		{ ECHO; return(WHEN); }
rem			{ ECHO; yylval.arithOp = REM; return(REMOP); }
true		{ ECHO; return(BOOL_LITERAL); }
false		{ ECHO; return(BOOL_LITERAL); }


begin		{ ECHO; return(BEGIN_); }
boolean		{ ECHO; return(BOOLEAN); }
end		{ ECHO; return(END); }
endreduce	{ ECHO; return(ENDREDUCE); }
function	{ ECHO; return(FUNCTION); }
integer		{ ECHO; return(INTEGER); }
is		{ ECHO; return(IS); }
reduce		{ ECHO; return(REDUCE); }
returns		{ ECHO; return(RETURNS); }
and		{ ECHO; return(ANDOP); }
{id}		{ ECHO; yylval.iden = (CharPtr)malloc(yyleng + 1); 
			strcpy(yylval.iden, yytext); return(IDENTIFIER);}
{double}		{ ECHO; yylval.value = atoi(yytext); return(INT_LITERAL); }
{punc}		{ ECHO; return(yytext[0]); }
.		{ ECHO; appendError(LEXICAL, yytext); }

%%
