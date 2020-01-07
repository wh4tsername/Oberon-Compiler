all: oberon

oberon.tab.c oberon.tab.h: oberon.y
	bison -d oberon.y

lex.yy.c: oberon.l
	flex oberon.l

oberon: lex.yy.c oberon.tab.c expressions.cpp statements.cpp variables.cpp main.cpp
	g++ -std=c++17 lex.yy.c oberon.tab.c expressions.cpp statements.cpp variables.cpp main.cpp -o oberon
