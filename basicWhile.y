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

%token VARIABLE INTEGER BOOL WHILE NEQ DO OD WRITE

%type <astNode> Expression Factor BooleanExpression ArithmeticExpression WhileStatement AssignmentStatement WriteStatement Statement StatementList BasicWhileProgram
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
	|		WhileStatement
	|		WriteStatement	
	;


AssignmentStatement:	VARIABLE '=' Expression	{ $$ = makeASTNode(assign, makeIntegerNode(variable, $1), $3); }
	;

WhileStatement:		WHILE '(' BooleanExpression ')' DO BasicWhileProgram OD

WriteStatement:		WRITE VARIABLE		{ printf("v%d: %d\n", $2, symbolArray[$2]); }
	|		WRITE INTEGER		{ printf("%d\n", $2);}
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

Factor:			VARIABLE		{ $$ = makeIntegerNode(variable, $1); }
	|		INTEGER			{ $$ = makeIntegerNode(integer, $1);}
	;

BooleanExpression:	Expression NEQ Expression	{ $$ = makeASTNode(nequal, $1, $3); }
	|		BOOL				{ $$ = makeIntegerNode(integer, $1); }
	;

%%

int main(int argc, char** argv) {
	int symbolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	yyparse();
}

int yyerror(char* s) { fprintf(stderr, "Error: %s\n", s); }
