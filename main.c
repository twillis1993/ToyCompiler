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
	ASTNode* oneNode = (ASTNode*) makeIntegerNode(1);
	ASTNode* twoNode = (ASTNode*) makeIntegerNode(2);
	ASTNode* plusNode = (ASTNode*) makeASTNode(plus, oneNode, twoNode);
	printf("Expected: 3, Actual: %d\n", evaluateASTNode(plusNode));
	freeASTNode(plusNode);
}
#endif
#ifdef EVAL_MINUS
int main(int argc, char** argv) {
	printf("Test: EVAL_MINUS\n");
	ASTNode* oneNode = (ASTNode*) makeIntegerNode(1);
	ASTNode* twoNode = (ASTNode*) makeIntegerNode(2);
	ASTNode* minusNode = (ASTNode*) makeASTNode(minus, oneNode, twoNode);
	printf("Expected: -1, Actual: %d\n", evaluateASTNode(minusNode));
	freeASTNode(minusNode);
}
#endif
#ifdef EVAL_MULTIPLY
int main(int argc, char** argv) {
	printf("Test: EVAL_MULTIPLY\n");
	ASTNode* oneNode = (ASTNode*) makeIntegerNode(3);
	ASTNode* twoNode = (ASTNode*) makeIntegerNode(2);
	ASTNode* multiplyNode = (ASTNode*) makeASTNode(multiply, oneNode, twoNode);
	printf("Expected: 6, Actual: %d\n", evaluateASTNode(multiplyNode));
	freeASTNode(multiplyNode);
}
#endif
#ifdef EVAL_DIVIDE
int main(int argc, char** argv) {
	printf("Test: EVAL_DIVIDE\n");
	ASTNode* oneNode = (ASTNode*) makeIntegerNode(10);
	ASTNode* twoNode = (ASTNode*) makeIntegerNode(2);
	ASTNode* divideNode = (ASTNode*) makeASTNode(divide, oneNode, twoNode);
	printf("Expected: 5, Actual: %d\n", evaluateASTNode(divideNode));
	freeASTNode(divideNode);
}
#endif
