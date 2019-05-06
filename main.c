#include <stdio.h>
#include "ast.h"

#ifdef EVAL_INT
int main(int argc, char** argv) {
	printf("Starting...\n");
	ASTNode* testNode = (ASTNode*) makeIntegerNode(1);
	printf("Node value: %d\n", evaluateASTNode(testNode));
	freeASTNode(testNode);
	printf("Finished\n");
}
#endif
#ifdef EVAL_PLUS
int main(int argc, char** argv) {
	printf("Test: EVAL_PLUS\n");
	ASTNode* plusNode = (ASTNode* ) makeASTNode( 	
	ASTNode* oneNode = (ASTNode*) makeIntegerNode(1);
	ASTNode* twoNode = (ASTNode*) makeIntegerNode(2);
}
#endif
