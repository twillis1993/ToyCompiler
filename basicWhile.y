%{
#include <stdio.h>
#include "ast.h"

int yylex(void);
int yyerror(char* s);
int symbolArray[10];
%}

%union { 
	struct ASTNode* astNode;
	int intValue;
}

%token VARIABLE INTEGER BOOL WHILE NEQ DO OD ASS_PLUS ASS_SUB WRITE

%type <astNode> Expression Factor BooleanExpression ArithmeticExpression
%type <intValue> INTEGER VARIABLE BOOL

%left '+' '-'
%left '*' '/'

%%

BasicWhileProgram:	StatementList ';'
	;

StatementList:		
	|		Statement ';' StatementList
	;

Statement:		AssignmentStatement
	|		WriteStatement
	;

WriteStatement:		WRITE VARIABLE		{ printf("v%d: %d\n", $2, symbolArray[$2]); }
	|		WRITE INTEGER		{ printf("%d\n", $2);}
	;

AssignmentStatement:	VARIABLE '=' VARIABLE	{ symbolArray[$1] = symbolArray[$3]; }
	| 		VARIABLE '=' INTEGER	{ symbolArray[$1] = $3; }
	| 		VARIABLE '=' Expression { symbolArray[$1] = evaluateASTNode($3); }
	| 		VARIABLE ASS_PLUS ArithmeticExpression { symbolArray[$1] = symbolArray[$1] + evaluateASTNode($3); }	
	| 		VARIABLE ASS_SUB ArithmeticExpression { symbolArray[$1] = symbolArray[$1] - evaluateASTNode($3); }
	;

Expression:		ArithmeticExpression
	|		BooleanExpression	
	;

ArithmeticExpression:	ArithmeticExpression '*' ArithmeticExpression	{ $$ = makeASTNode(multiply, $1, $3); }
	|		ArithmeticExpression '/' ArithmeticExpression 	{ $$ = makeASTNode(divide, $1, $3); }
	|		ArithmeticExpression '+' ArithmeticExpression 	{ $$ = makeASTNode(plus, $1, $3); }
	|		ArithmeticExpression '-' ArithmeticExpression 	{ $$ = makeASTNode(minus, $1, $3); }
	| 		Factor				
	;	

Factor:			VARIABLE		{ $$ = makeIntegerNode(symbolArray[$1]); }
	|		INTEGER			{ $$ = makeIntegerNode($1);}
	;

BooleanExpression:	Expression NEQ Expression	{ $$ = makeASTNode(nequal, $1, $3); }
	|		BOOL				{ $$ = makeIntegerNode($1); }
	;

%%

int main(int argc, char** argv) {
	int symbolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	yyparse();
}

int yyerror(char* s) { fprintf(stderr, "Error: %s\n", s); }
