%{
int yylex(void);
int symbolArray[10];
%}

%union { int intValue;
	 bool boolValue;
}

%token <intValue> VARIABLE
%token <intValue> INTEGER
%token <boolValue> BOOL

%%
BasicWhileProgram:	StatementList ';' WriteCommand ';'
	;

StatementList:		Statement
	|		StatementList ';' Statement
	;

Statement:		WhileStatement
	| 		AssignmentStatement
	| 		/* Allows blank lines */	
	;

WhileStatement:		'while' VARIABLE '!=' 
				'do' StatementList 'od'
	;

AssignmentStatement:	VARIABLE '=' VARIABLE { $1 = $3; } { symbolArray[$1] = symbolArray[$3]; }
	| 		VARIABLE '+=' INTEGER { symbolArray[$1] = symbolArray[$1] + $3; } 
	| 		VARIABLE '-=' INTEGER { symbolArray[$1] = symbolArray[$1] - $3; }
	| 		VARIABLE '=' INTEGER	{ symbolArray[$1] = $3; }
	| 		VARIABLE '=' Expression
	;

Expression:		Expression '+' Term
	|		Expression '-' Term
	;	

Term:			Factor '*' Term
	|		Factor '/' 
	| 		Factor
	;
Factor:			'(' Expression ')'
	|		INTEGER				
	;

WriteCommand:		'write' '(' IdentifierList ')'
	;

IdentifierList:		VARIABLE
	|		IdentifierList ',' VARIABLE
	;
%%	

int main(int argc, char** argv) {
	yyparse();
}
