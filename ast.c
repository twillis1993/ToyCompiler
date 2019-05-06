#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ASTNode* makeASTNode(NodeType nodeType, ASTNode* leftChild, ASTNode* rightChild) {
	ASTNode* astNode = malloc(sizeof(ASTNode));

	if(!astNode) {
		#ifdef PROD
		yyerror("Malloc of ASTNode failed\n");
		#else
		printf("Malloc of ASTNode failed\n");
		#endif
	}
	astNode->nodeType = nodeType;
	astNode->leftChild = leftChild;
	astNode->rightChild = rightChild;

	return astNode;	
}

ASTNode* makeIntegerNode(int value) {	
	IntegerNode* integerNode = malloc(sizeof(IntegerNode));

	if(!integerNode) {
		#ifdef PROD
		yyerror("Malloc of IntegerNode failed\n");
		#else
		printf("Malloc of IntegerNode failed\n");
		#endif
	}
	integerNode->nodeType = integer;
	integerNode->value = value;

	return (ASTNode*) integerNode;	
}

int evaluateASTNode(ASTNode* astNode) {
	switch(astNode->nodeType) {
		case integer:	return ((IntegerNode*) astNode)->value;
		default:	printf("Reached default case in evaluateASTNode\n");	
	}
}

void freeASTNode(ASTNode* astNode) {
	// TODO nice trick in the book relating to cases, we don't break so we always free this node
	switch(astNode->nodeType) {
		case ast:	if(astNode->leftChild) freeASTNode(astNode->leftChild); if(astNode->rightChild) freeASTNode(astNode->rightChild); 	
		case integer:	free(astNode); break;
		default:	printf("Reached default case in freeASTNode\n");
	}
}


