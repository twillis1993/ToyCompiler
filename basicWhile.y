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

%token VARIABLE INTEGER BOOL WHILE NEQ DO OD WRITE IF FI THEN ELSE 

%type <astNode> Expression Factor BooleanExpression ArithmeticExpression WhileStatement AssignmentStatement WriteStatement Statement StatementList BasicWhileProgram IfStatement
%type <intValue> INTEGER VARIABLE BOOL

%left '+' '-'
%left '*' '/'
%left NEQ '>'

%%

BasicWhileProgram:	StatementList 		{ $$ = makeASTNode(list, $1, NULL); evaluateASTNode($$); }
	;

StatementList:						{ $$ = NULL; }
	|		Statement ';' StatementList	{ $$ = makeASTNode(list, $1, $3); }
	;

Statement:		AssignmentStatement
	|		WhileStatement
	|		WriteStatement	
	| 		IfStatement
	| 		Expression			{ $$ = $1; printf("%d\n", evaluateASTNode($1)); }
	;

AssignmentStatement:	VARIABLE '=' Expression	{ $$ = makeASTNode(assign, makeIntegerNode(variable, $1), $3); }
	;

WhileStatement:		WHILE '(' BooleanExpression ')' DO StatementList OD { $$ = makeWhileNode($3, $6); }

IfStatement:		IF '(' BooleanExpression ')' THEN StatementList FI  {$$ = makeIfElseNode($3, $6, NULL); }
	| 		IF '(' BooleanExpression ')' THEN StatementList FI ELSE StatementList { $$ = makeIfElseNode($3, $6, $9); }
	;

WriteStatement:		WRITE Expression		{ $$ = makeASTNode(write, $2, NULL); }
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
	|		Expression '>' Expression	{ $$ = makeASTNode(gt, $1, $3);    }
	|		BOOL				{ $$ = makeIntegerNode(integer, $1); }
	;

%%

int main(int argc, char** argv) {
	int symbolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	yyparse();
}

int yyerror(char* s) { fprintf(stderr, "Error: %s\n", s); }
