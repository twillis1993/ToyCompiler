%{
#include <stdio.h>
#include "ast.h"

int yylex(void);
int yyerror(char* s);
int symbolArray[10];
%}

%union { 
	char* stringValue;
	int intValue;
}

%token VARIABLE INTEGER BOOL WHILE NEQ DO OD ASS_PLUS ASS_SUB

%type <intValue> Expression Factor VARIABLE INTEGER BOOL

%left '+' '-'
%left '*' '/'

%%

BasicWhileProgram:	StatementList ';'
	;

StatementList:		
	|		Statement ';' StatementList
	;

Statement:		WhileStatement
	|		AssignmentStatement
	;

WhileStatement:		WHILE VARIABLE NEQ INTEGER DO StatementList ';' OD

AssignmentStatement:	VARIABLE '=' VARIABLE	{ symbolArray[$1] = symbolArray[$3]; }
	| 		VARIABLE '=' INTEGER	{ symbolArray[$1] = $3; }
	| 		VARIABLE '=' Expression { symbolArray[$1] = $3; }
	| 		VARIABLE ASS_PLUS Expression { symbolArray[$1] = symbolArray[$1] + $3; }	
	| 		VARIABLE ASS_SUB Expression { symbolArray[$1] = symbolArray[$1] - $3; }
	|		Expression		{ printf("%d\n", $1); }
	;

Expression:		Expression '*' Expression	{ $$ = $1 * $3; }
	|		Expression '/' Expression 	{ $$ = $1 / $3; }
	|		Expression '+' Expression 	{ $$ = $1 + $3; }
	|		Expression '-' Expression 	{ $$ = $1 - $3; }
	| 		Factor	
	;	

Factor:			VARIABLE		{ $$ = symbolArray[$1]; }
	|		INTEGER	
	;

%%

int main(int argc, char** argv) {
	int symbolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	yyparse();
}

int yyerror(char* s) {
	fprintf(stderr, "Error: %s\n", s);
}
