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

ASTNode* makeIntegerNode(NodeType nodeType, int value) {	
	IntegerNode* integerNode = malloc(sizeof(IntegerNode));

	if(!integerNode) {
		#ifdef PROD
		yyerror("Malloc of IntegerNode failed\n");
		#else
		printf("Malloc of IntegerNode failed\n");
		#endif
	}
	integerNode->nodeType = nodeType;
	integerNode->value = value;

	return (ASTNode*) integerNode;	
}

ASTNode* makeWhileNode(ASTNode* condition, ASTNode* doList) {
	WhileNode* whileNode = malloc(sizeof(ASTNode));

	if(!whileNode) {
		#ifdef PROD
		yyerror("Malloc of WhileNode failed\n");
		#else
		printf("Malloc of WhileNode failed\n");
		#endif
	}
	whileNode->nodeType = doWhile;
	whileNode->condition = condition;
	whileNode->doList = doList;

	return (ASTNode*) whileNode;
}

int evaluateASTNode(ASTNode* astNode) {
	switch(astNode->nodeType) {
		case plus:	
			return evaluateASTNode(astNode->leftChild) + evaluateASTNode(astNode->rightChild);
		case minus:	
			return evaluateASTNode(astNode->leftChild) - evaluateASTNode(astNode->rightChild);
		case multiply:	
			return evaluateASTNode(astNode->leftChild) * evaluateASTNode(astNode->rightChild);
		case divide:	
			return evaluateASTNode(astNode->leftChild) / evaluateASTNode(astNode->rightChild);
		case nequal:	
			return evaluateASTNode(astNode->leftChild) != evaluateASTNode(astNode->rightChild);
		case integer:	
			return ((IntegerNode*) astNode)->value;
		case variable:	
			return symbolArray[((IntegerNode*) astNode)->value];
		case write:
			printf("%d\n", evaluateASTNode(astNode->leftChild));
			return 0;
		case assign:
			symbolArray[((IntegerNode*) (astNode->leftChild))->value] = evaluateASTNode(astNode->rightChild);
			return 0;	
		case doWhile:	
			if(((WhileNode*) astNode)->doList) {
				while(evaluateASTNode(((WhileNode*) astNode)->condition)) {
					evaluateASTNode(((WhileNode*) astNode)->doList);		
				}	
			}
			return 0;
		case list: 
			if(astNode->leftChild) evaluateASTNode(astNode->leftChild);
			if(astNode->rightChild) evaluateASTNode(astNode->rightChild);	
			return 0;	
		default:	
			printf("Reached default case in evaluateASTNode\n");	
	}
}

// TODO reenable me and implement for while node etc.

void freeASTNode(ASTNode* astNode) {
	/*
	// TODO nice trick in the book relating to cases, we don't break so we always free this node
	switch(astNode->nodeType) {
		case integer:	free(astNode); 
				break;
		case doWhile:	freeASTNode
		default:	if(astNode->leftChild) freeASTNode(astNode->leftChild); 
				if(astNode->rightChild) freeASTNode(astNode->rightChild); 
				free(astNode);
	}
	*/
}
