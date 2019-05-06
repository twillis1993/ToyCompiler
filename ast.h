#ifndef AST_H
#define	AST_H

// Adapted from 'Flex and Bison' by Levine.
#ifdef PROD
extern int yylineno;
int yyerror(char *s);
#endif

extern int symbolArray[10];

enum NodeType { ast, integer, variable, plus, minus, multiply, divide, nequal, doWhile, assign, write };

typedef enum NodeType NodeType;

struct ASTNode {
	NodeType nodeType;
	struct ASTNode* leftChild;
	struct ASTNode* rightChild;
};

typedef struct ASTNode ASTNode;

struct IntegerNode {
	NodeType nodeType;
	int value;
};

typedef struct IntegerNode IntegerNode;

struct WhileNode {
	NodeType nodeType;
	struct ASTNode* condition;
	struct ASTNode* doList;
};

typedef struct WhileNode WhileNode;

ASTNode* makeASTNode(NodeType nodeType, ASTNode* leftChild, ASTNode* rightChild);

ASTNode* makeIntegerNode(NodeType nodeType, int value);

ASTNode* makeWhileNode(ASTNode* condition, ASTNode* doList);

int evaluateASTNode(ASTNode* astNode);

void freeASTNode(ASTNode* astNode);

#endif
