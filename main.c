#include <stdio.h>
#include "ast.h"

int symbolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#ifdef EVAL_INT
int main(int argc, char** argv) {
	printf("Starting...\n");
	ASTNode* testNode = makeIntegerNode(integer, 1);
	printf("Expected: 1, Actual: %d\n", evaluateASTNode(testNode));
	freeASTNode(testNode);
	printf("Finished\n");
}
#endif
#ifdef EVAL_PLUS
int main(int argc, char** argv) {
	printf("Test: EVAL_PLUS\n");
	ASTNode* oneNode = makeIntegerNode(integer, 1);
	ASTNode* twoNode = makeIntegerNode(integer, 2);
	ASTNode* plusNode = makeASTNode(plus, oneNode, twoNode);
	printf("Expected: 3, Actual: %d\n", evaluateASTNode(plusNode));
	freeASTNode(plusNode);
}
#endif
#ifdef EVAL_MINUS
int main(int argc, char** argv) {
	printf("Test: EVAL_MINUS\n");
	ASTNode* oneNode = makeIntegerNode(integer, 1);
	ASTNode* twoNode = makeIntegerNode(integer, 2);
	ASTNode* minusNode = makeASTNode(minus, oneNode, twoNode);
	printf("Expected: -1, Actual: %d\n", evaluateASTNode(minusNode));
	freeASTNode(minusNode);
}
#endif
#ifdef EVAL_MULTIPLY
int main(int argc, char** argv) {
	printf("Test: EVAL_MULTIPLY\n");
	ASTNode* oneNode = makeIntegerNode(integer, 3);
	ASTNode* twoNode = makeIntegerNode(integer, 2);
	ASTNode* multiplyNode = makeASTNode(multiply, oneNode, twoNode);
	printf("Expected: 6, Actual: %d\n", evaluateASTNode(multiplyNode));
	freeASTNode(multiplyNode);
}
#endif
#ifdef EVAL_DIVIDE
int main(int argc, char** argv) {
	printf("Test: EVAL_DIVIDE\n");
	ASTNode* oneNode = makeIntegerNode(integer, 10);
	ASTNode* twoNode = makeIntegerNode(integer, 2);
	ASTNode* divideNode = makeASTNode(divide, oneNode, twoNode);
	printf("Expected: 5, Actual: %d\n", evaluateASTNode(divideNode));
	freeASTNode(divideNode);
}
#endif
#ifdef EVAL_NEQUAL_1
int main(int argc, char** argv) {
	printf("Test: EVAL_NEQUAL\n");
	ASTNode* oneNode = makeIntegerNode(integer, 1);
	ASTNode* twoNode = makeIntegerNode(integer, 1);
	ASTNode* nequalNode = makeASTNode(nequal, oneNode, twoNode);
	printf("Expected: 0, Actual: %d\n", evaluateASTNode(nequalNode));
	freeASTNode(nequalNode);
}
#endif
#ifdef EVAL_NEQUAL_2
int main(int argc, char** argv) {
	printf("Test: EVAL_NEQUAL\n");
	ASTNode* oneNode = makeIntegerNode(integer, 0);
	ASTNode* twoNode = makeIntegerNode(integer, 1);
	ASTNode* nequalNode = makeASTNode(nequal, oneNode, twoNode);
	printf("Expected: 1, Actual: %d\n", evaluateASTNode(nequalNode));
	freeASTNode(nequalNode);
}
#endif
#ifdef EVAL_GT_1
int main(int argc, char** argv) {
	printf("Test: EVAL_GT_1\n");
	ASTNode* oneNode = makeIntegerNode(integer, 1);
	ASTNode* twoNode = makeIntegerNode(integer, 1);
	ASTNode* gtNode = makeASTNode(gt, oneNode, twoNode);
	printf("Expected: 0, Actual: %d\n", evaluateASTNode(gtNode));
	freeASTNode(gtNode);
}
#endif
#ifdef EVAL_GT_2
int main(int argc, char** argv) {
	printf("Test: EVAL_GT_2\n");
	ASTNode* oneNode = makeIntegerNode(integer, 0);
	ASTNode* twoNode = makeIntegerNode(integer, 1);
	ASTNode* gtNode = makeASTNode(gt, oneNode, twoNode);
	printf("Expected: 0, Actual: %d\n", evaluateASTNode(gtNode));
	freeASTNode(gtNode);
}
#endif
#ifdef EVAL_GT_3
int main(int argc, char** argv) {
	printf("Test: EVAL_GT_3\n");
	ASTNode* oneNode = makeIntegerNode(integer, 4);
	ASTNode* twoNode = makeIntegerNode(integer, 1);
	ASTNode* gtNode = makeASTNode(gt, oneNode, twoNode);
	printf("Expected: 1, Actual: %d\n", evaluateASTNode(gtNode));
	freeASTNode(gtNode);
}
#endif
#ifdef ASSIGN
int main(int argc, char** argv) {
	printf("Test: ASSIGN\n");
	ASTNode* variableNode = makeIntegerNode(variable, 1);
	ASTNode* fiveNode = makeIntegerNode(integer, 5);
	ASTNode* assignNode = makeASTNode(assign, variableNode, fiveNode);
	int v1Before = symbolArray[1];
	evaluateASTNode(assignNode);	
	int v1After = symbolArray[1];
	printf("Before: %d, Expected: 5, Actual: %d\n", v1Before, v1After);
	freeASTNode(assignNode);
}
#endif
#ifdef WRITE
int main(int argc, char** argv) {
	printf("Test: WRITE\n");
	printf("Expected output: 5\nActual output: ");
	ASTNode* oneNode = makeIntegerNode(integer, 10);
	ASTNode* twoNode = makeIntegerNode(integer, 2);
	ASTNode* divideNode = makeASTNode(divide, oneNode, twoNode);
	ASTNode* writeNode = makeASTNode(write, divideNode, NULL);
	evaluateASTNode(writeNode);	
	freeASTNode(writeNode);
}
#endif
#ifdef WHILE
int main(int argc, char** argv) {
	printf("Test: WHILE\n");
	ASTNode* conditionNode = NULL;
	ASTNode* doListNode = NULL;
	ASTNode* whileNode = makeWhileNode(doWhile, conditionNode, doListNode);
	evaluateASTNode(whileNode);
	freeASTNode(whileNode);
}
#endif

#ifdef IF_ELSE_1
int main(int argc, char** argv) {
	printf("Test: IF_ELSE_1\n");
	ASTNode* oneNode = makeIntegerNode(integer, 4);
	ASTNode* twoNode = makeIntegerNode(integer, 1);
	ASTNode* gtNode = makeASTNode(gt, oneNode, twoNode);
	evaluateASTNode(ifElseNode);
}
#endif
#ifdef LIST
int main(int argc, char** argv) {
	printf("Test: LIST\n");
	// left child
	ASTNode* variableNode = makeIntegerNode(variable, 1);
	ASTNode* fiveNode = makeIntegerNode(integer, 5);
	ASTNode* assignNode = makeASTNode(assign, variableNode, fiveNode);
	// right child		
	ASTNode* writeNode = makeASTNode(write, variableNode, NULL);
	ASTNode* listNode = makeASTNode(list, assignNode, writeNode);	
	evaluateASTNode(listNode);	
	freeASTNode(listNode);
}
#endif
#ifdef PROGRAM
int main(int argc, char** argv) {
	printf("Test: PROGRAM\n");
	// left child
	ASTNode* variableNode = makeIntegerNode(variable, 1);
	ASTNode* fiveNode = makeIntegerNode(integer, 5);
	ASTNode* assignNode = makeASTNode(assign, variableNode, fiveNode);
	// right child		
	ASTNode* writeNode = makeASTNode(write, variableNode, NULL);
	ASTNode* listNode = makeASTNode(list, assignNode, writeNode);	
	ASTNode* programNode = makeASTNode(list, listNode, NULL);
	printf("Expected output: 5\nActual output: ");
	evaluateASTNode(programNode);	
	freeASTNode(programNode);
}
#endif
