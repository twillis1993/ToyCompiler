// Adapted from 'Flex and Bison' by Levine.
#ifndef TEST
extern int yylineno;
void yyerror(char *s);
#endif

enum NodeType { ast, integer };

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

