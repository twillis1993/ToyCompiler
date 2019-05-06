%{
#include "basicWhile.tab.h"
#include <stdlib.h>

extern int symbolArray[10];

%}

%%

v[0-9] 	{ yylval.intValue=(yytext[1] - '0'); return VARIABLE; }

[0-9]+	{ yylval.intValue = atoi(yytext); return INTEGER; }

"True" 	{ yylval.intValue = 1; return BOOL; }

"False" { yylval.intValue = 0; return BOOL; }

";" |
"=" |
"+" |
"-" |
"*" |
"/" |
"(" |
")" |
","	{ return yytext[0]; }

"while"	{ return WHILE; }
"do"	{ return DO; }
"od"	{ return OD; }
"!="	{ return NEQ; }
"write" { return WRITE; }

[ \t\n]	;
%%
