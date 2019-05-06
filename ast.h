#ifndef AST_H
#define	AST_H

// Adapted from 'Flex and Bison' by Levine.
#ifdef PROD
extern int yylineno;
int yyerror(char *s);
#endif

enum NodeType { ast, integer, plus, minus, multiply, divide };

typedef enum NodeType NodeType;

struct ASTNode {
	NodeType nodeType;
	struct ASTNode* leftChild;
	struct ASTNode* rightChild;
};

struct IntegerNode {
	NodeType nodeType;
	int value;
};

typedef struct ASTNode ASTNode;

typedef struct IntegerNode IntegerNode;

ASTNode* makeASTNode(NodeType nodeType, ASTNode* leftChild, ASTNode* rightChild);

ASTNode* makeIntegerNode(int value);

int evaluateASTNode(ASTNode* astNode);

void freeASTNode(ASTNode* astNode);

#endif
