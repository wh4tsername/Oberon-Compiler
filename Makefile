all: oberon

oberon.tab.c oberon.tab.h: oberon.y
	bison -d --graph --verbose oberon.y

lex.yy.c: oberon.l
	flex oberon.l

oberon: lex.yy.c oberon.tab.c expressions.cpp statements.cpp variables.cpp main.cpp
	g++ -g -std=c++17 lex.yy.c oberon.tab.c expressions.cpp statements.cpp variables.cpp main.cpp -o oberon
