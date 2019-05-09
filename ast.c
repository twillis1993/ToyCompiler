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
	WhileNode* whileNode = malloc(sizeof(WhileNode));

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

ASTNode* makeIfElseNode(ASTNode* condition, ASTNode* ifList, ASTNode* elseList) {
	IfElseNode* ifElseNode = malloc(sizeof(IfElseNode));

	if(!ifElseNode) {
		#ifdef PROD
		yyerror("Malloc of WhileNode failed\n");
		#else
		printf("Malloc of WhileNode failed\n");
		#endif
	}
	ifElseNode->nodeType = ifElse;
	ifElseNode->condition = condition;
	ifElseNode->ifList = ifList;
	ifElseNode->elseList = elseList;
	
	return (ASTNode*) ifElseNode;
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
		case gt:
			return evaluateASTNode(astNode->leftChild) > evaluateASTNode(astNode->rightChild);	
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
		case program:
		case list: 
			if(astNode->leftChild) evaluateASTNode(astNode->leftChild);
			if(astNode->rightChild) evaluateASTNode(astNode->rightChild);	
			return 0;	
		case ifElse:
			if(evaluateASTNode(((IfElseNode*) astNode)->condition)) {
				if(((IfElseNode*) astNode)->ifList) evaluateASTNode(((IfElseNode*) astNode)->ifList);
			} else {
				if(((IfElseNode*) astNode)->elseList) evaluateASTNode(((IfElseNode*) astNode)->elseList);
			}
			return 0;
		default:	
			printf("Reached default case in evaluateASTNode\n");	
	}
}

// TODO reenable me and implement for while node etc.

void freeASTNode(ASTNode* astNode) {
	// TODO nice trick in the book relating to cases, we don't break so we always free this node
	switch(astNode->nodeType) {
		case variable:
		case integer:	free(astNode); 
				break;
		case doWhile:	if(((WhileNode*) astNode)->condition) freeASTNode(((WhileNode*) astNode)->condition);
				if(((WhileNode*) astNode)->doList) freeASTNode(((WhileNode*) astNode)->doList);
				free(astNode);
				break;	
		case ifElse:	if(((IfElseNode*) astNode)->condition) freeASTNode(((IfElseNode*) astNode)->condition);
				if(((IfElseNode*) astNode)->ifList) freeASTNode(((IfElseNode*) astNode)->ifList);
				if(((IfElseNode*) astNode)->elseList) freeASTNode(((IfElseNode*) astNode)->elseList);
				free(astNode);
				break;		
		default:	if(astNode->leftChild) freeASTNode(astNode->leftChild); 
				if(astNode->rightChild) freeASTNode(astNode->rightChild); 
				free(astNode);
	}
}

void generateProgram(ASTNode* headNode) {
	FILE* outputFile = fopen("cCode.c", "w");

	char* preambleString = "#include <stdio.h>\nint main(int argc, char** argv) {\n";
	char* symbolArrayString = "int symbolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};\n";
	char* endString = "return 0;\n}\n";
	fprintf(outputFile, "%s", preambleString);	
	fprintf(outputFile, "%s", symbolArrayString);		
	if(headNode->leftChild) {	
		generateCode(headNode->leftChild, outputFile);
	}
	fprintf(outputFile, "%s", endString);	
	fclose(outputFile);
}

void generateCode(ASTNode* astNode, FILE* outputFile) {
	switch(astNode->nodeType) {
		case plus:
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " + ");
			generateCode(astNode->rightChild, outputFile);
			break;
		case minus:	
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " - ");
			generateCode(astNode->rightChild, outputFile);
			break;
		case multiply:	
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " * ");
			generateCode(astNode->rightChild, outputFile);
			break;
		case divide:	
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " / ");
			generateCode(astNode->rightChild, outputFile);
			break;
		case nequal:	
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " != ");
			generateCode(astNode->rightChild, outputFile);
			break;
		case gt:
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " > ");
			generateCode(astNode->rightChild, outputFile);
			break;
		case integer:	
			fprintf(outputFile, "%d", ((IntegerNode*) astNode)->value);
			break;
		case variable:	
			fprintf(outputFile, "symbolArray[%d]", ((IntegerNode*) astNode)->value);
			break;
		case write:
			fprintf(outputFile, "printf(\"%%d\\n\", ");
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, ");");
			break;
		case assign:	
			generateCode(astNode->leftChild, outputFile);
			fprintf(outputFile, " = ");
			generateCode(astNode->rightChild, outputFile);
			fprintf(outputFile, ";");
			break;
		case doWhile:
			fprintf(outputFile, "while (");
			generateCode(((WhileNode*) astNode)->condition, outputFile);
			fprintf(outputFile, ") {\n");
			generateCode(((WhileNode*) astNode)->doList, outputFile);
			fprintf(outputFile, "}\n");
			break;
		case program:
		case list: 
			if(astNode->leftChild) {
				generateCode(astNode->leftChild, outputFile);
				fprintf(outputFile, "\n");
			}	
			if(astNode->rightChild) {
				generateCode(astNode->rightChild, outputFile);
			}
			break;
		case ifElse:
			fprintf(outputFile, "if(");	
			generateCode(((IfElseNode*) astNode)->condition, outputFile);
			fprintf(outputFile, ") {\n");
			if(((IfElseNode*) astNode)->ifList) { 
				generateCode(((IfElseNode*) astNode)->ifList, outputFile);
			}
			if(((IfElseNode*) astNode)->elseList) {
				fprintf(outputFile, "} else {\n");
				generateCode(((IfElseNode*) astNode)->elseList, outputFile);	
			} 
			fprintf(outputFile, "}");
			break;
		default:	
			printf("Reached default case in generateCode\n");
	
		}
}
