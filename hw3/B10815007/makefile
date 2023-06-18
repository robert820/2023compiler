CC=g++

compiler: y.tab.o lex.yy.o SymbolTable.o  
	$(CC) -o compiler -O y.tab.o lex.yy.o SymbolTable.o -lfl

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c
	
y.tab.o: y.tab.c
	$(CC) -c y.tab.c

SymbolTable.o: SymbolTable.cpp
	$(CC) -c SymbolTable.cpp
	
ast.o: ast.c
	$(CC) -c ast.c

y.tab.c: hw3.y
	yacc -d hw3.y

lex.yy.c: hw3.l
	lex hw3.l

clean:
	rm lex.yy.c y.tab.c y.tab.h compiler *.o

