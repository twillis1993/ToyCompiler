%{
#include "basicWhile.tab.h"
#include <stdlib.h>
#include <stdbool.h>
%}
%%

[0-9]+	{ yylval.intValue = atoi(yytext); return INTEGER; }

"True"  { yylval.boolValue = true; return BOOL; }

"False"	{ yylval.boolValue = false; return BOOL; }

";" |
"=" |
"+" |
"-" |
"*" |
"/" |
"(" |
")" |
","	{ return yytext[0]; }

"while" |
"!=" 	|
"do"	|
"od"	|
"+="	|
"-="	|
"write" |
"read"	{ return *yytext; }

[ \t\n]	;
%%
