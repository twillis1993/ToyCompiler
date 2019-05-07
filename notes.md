# TODO

Check coursework brief, needs to be able to evaluate expressions

# Pseudocode

while a != b
	if a > b
		a := a - b;
	else
		b := b - a;
return a;

# TODO

Readme

* Variables are numbered 0-9, we store them in an array which we update, initialised to 0 so that we do not need to handle initialisation
* Kept grammar small, just what was necessary to implement Euclid's algorithm
* Used the abstract syntax tree from Levine, omitted proper symbol table, though
* We construct the abstract syntax tree depth-up
* We evaluate from the head down
* We also generate code from the head down 
