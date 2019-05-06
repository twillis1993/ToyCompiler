basicWhile:	basicWhile.l basicWhile.y
		bison -d -v basicWhile.y
		flex basicWhile.l
		gcc -o $@ basicWhile.tab.c lex.yy.c -lfl
