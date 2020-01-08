%{
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
	#include "declaration.h"
%}

IDENT [a-zA-Z][_a-zA-Z0-9]*
NUMBER ([1-9][0-9]*)|0
REAL (([1-9][0-9]*)|0)\.[0-9]*

%option noyywrap

%%
"MODULE"    { return MODULE; }
"IMPORT"    { return IMPORT; }
"VAR"       { return VAR; }
"BEGIN"     { return T_BEGIN; }
"END"       { return END; }
"PRINT"     { return PRINT; }
"IF"        { return IF; }
"THEN"      { return THEN; }
"ELSE"      { return ELSE; }
"ELSIF"     { return ELSIF; }
"INTEGER"   { return T_INTEGER; }
"REAL"      { return T_REAL; }
"="         { return '='; }
"<"         { return '<'; }
">"         { return '>'; }
"<="        { return LE; }
">="        { return GE; }
"AND"       { return AND; }
"OR"        { return OR; }
"NOT"       { return NOT; }
"+"         { return '+'; }
"-"         { return '-'; }
"/"         { return '/'; }
"*"         { return '*'; }
"("         { return '('; }
")"         { return ')'; }
" "         { /* space - do nothing */ }
";"         { return ';'; }
":"         { return ':'; }
"."         { return '.'; }
":="        { return ASSIGNMENT_SYMBOL; }
"\t"        { /* tab symbol - do nothing */ }
{IDENT}     { strcpy(yylval.id_name, yytext); return IDENT; }
{NUMBER}    { yylval.int_value = atoi(yytext); return NUMBER; }
{REAL}      { yylval.double_value = atof(yytext); return REAL; }
.           { printf("Lexical error: %s\n", yytext); exit(1); }

%%
