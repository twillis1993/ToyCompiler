CC=gcc
DEF=EVAL_INT
BISON_DEF=PROD
DEF_FLAGS=-D$(DEF) -D$(BISON_DEF)

# Running ast tests: make main DEF=<test_case> BISON_DEF=TEST
#
basicWhile:	lex.yy.c basicWhile.tab.c ast.o
		$(CC) -o $@ ast.o basicWhile.tab.c lex.yy.c -I. -lfl $(DEF_FLAGS)
ast.o:	ast.c
	$(CC) -c -o $@ $^ -I. $(DEF_FLAGS)

main.o:	main.c
	$(CC) -c -o $@ $^ -I. $(DEF_FLAGS)

main:	main.o ast.o
	$(CC) -o $@ $^ -I.

basicWhile.tab.c:
		bison -d -v basicWhile.y

lex.yy.c:	
		flex basicWhile.l

clean:		
		rm -f *.o basicWhile *.tab.* main *.output lex.yy.c cCode.c;
