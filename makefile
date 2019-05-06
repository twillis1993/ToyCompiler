CC=gcc
# Default DEF
DEF=EVAL_INT
DEF_FLAGS=-D $(DEF)

ast.o:	ast.c
	$(CC) -c -o $@ $^ -I.

main.o:	main.c
	$(CC) -c -o $@ $^ -I. $(DEF_FLAGS)

main:	main.o ast.o
	$(CC) -o $@ $^ -I.

basicWhile:	basicWhile.l basicWhile.y ast.o
		bison -d -v basicWhile.y
		flex basicWhile.l
		$(CC) -o $@ basicWhile.tab.c lex.yy.c -I. -lfl

