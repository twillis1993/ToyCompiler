# Description

A toy compiler written for a university assignment. The compiler is generated with the use of `flex` and `bison`. It was required that the language be sufficiently expressive that Euclid's algorithm could be implemented in it. The language is a 'basic while' language which is Turing-complete.

I borrowed heavily from examples in Levine's 'Flex and Bison' textbook.

# Building it

Run:
 
	make basicWhile

The compiler can be run interactively with `./basicWhile` or a source file can be passed to it, e.g.

	./basicWhile < euclidTest.txt

The compiler generates ugly C code in the `cCode.c` file. 
