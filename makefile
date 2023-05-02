scanner: lex.yy.c SymbolTable.c
	cc -o scanner -O lex.yy.c SymbolTable.c -lfl

lex.yy.c: hw1.l
	lex hw1.l

clean:
	rm lex.yy.c scanner

