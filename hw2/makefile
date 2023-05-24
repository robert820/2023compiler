scanner: y.tab.c lex.yy.c SymbolTable.c
	cc -o scanner -O y.tab.c lex.yy.c SymbolTable.c -lfl

y.tab.c: hw2.y
	yacc -d hw2.y


lex.yy.c: hw2.l
	lex hw2.l

clean:
	rm lex.yy.c y.tab.c y.tab.h scanner

