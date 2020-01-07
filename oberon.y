%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "declaration.h"
    #include "expressions.h"
    #include "variables.h"
%}

%union {
    Expression* expression;
    LogicalExpression* logical_expression;
    Statement* statement;
    ListOfStatements* list;

    int int_value;
    double double_value;
    
    char id_name[256];
}

%left '+' '-'
%left '*' '/'

%nonassoc UMINUS
%nonassoc NOT

%token <int_value> NUMBER
%token <double_value> REAL
%token <id_name> IDENT
%token PRINT
%token IF
%token THEN
%token ELSE
%token ELSIF
%token MODULE
%token IMPORT
%token VAR
%token T_BEGIN
%token END

%type <expression> expression
%type <logical_expression> logic_expression
%type <list> statement_sequence
%type <statement> statement

%%

module:
	MODULE IDENT ';' IMPORT import_list ';' VAR declaration_sequence ';' program END IDENT '.' {};

program: 
	T_BEGIN statement_sequence {}
	| {};

import_list: 
	{};

declaration_sequence: 
	declaration_sequence ';' declaration delimeter {}
	| {};

declaration:
	IDENT ':' NUMBER {variables_container.Add($1, $3);}
	| IDENT ':' REAL {variables_container.Add($1, $3);};

statement_sequence: 
	statement_sequence ';' statement delimeter {} 
	| {$$ = new ListOfStatements;};

delimeter:
	'\n' {}
	| delimeter '\n' {}
	| {};

statement: 
	IDENT ":=" expression {$$ = new AssignStatement($1, $3);}
	| PRINT expression {}
	| if_statement {}
	| {};

if_statement: 
	IF logic_expression THEN delimeter statement_sequence 
	elsif_statement
	ELSE delimeter statement_sequence END {}
	| IF logic_expression THEN delimeter statement_sequence
	elsif_statement END {};

elsif_statement:
	ELSIF logic_expression THEN delimeter statement_sequence {}
	| {};

logic_expression: 
	expression "<" expression {$$ = new LogicalExpression(0, $1, $3);}
	| expression ">" expression {$$ = new LogicalExpression(2, $1, $3);}
	| expression "<=" expression {$$ = new LogicalExpression(1, $1, $3);}
	| expression ">=" expression {$$ = new LogicalExpression(3, $1, $3);}
	| expression "=" expression {$$ = new LogicalExpression(4, $1, $3);}
	| expression "#" expression {$$ = new LogicalExpression(5, $1, $3);}
	| expression "AND" expression {$$ = new LogicalExpression(6, $1, $3);}
	| expression "OR" expression {$$ = new LogicalExpression(7, $1, $3);}
	| "NOT" expression %prec NOT {$$ = new LogicalExpression(8, $2, NULL);}
	;

expression:
	IDENT {$$ = new VariableExpression($1);}
	| NUMBER {$$ = new NumeralExpression($1);}
	| '-' expression %prec UMINUS {$$ = new ArithmeticExpression(-5, $2, NULL);}
	| expression '+' expression {$$ = new ArithmeticExpression(-1, $1, $3);}
	| expression '-' expression {$$ = new ArithmeticExpression(-2, $1, $3);}
	| expression '*' expression {$$ = new ArithmeticExpression(-3, $1, $3);}
	| expression '/' expression {$$ = new ArithmeticExpression(-4, $1, $3);}
	| '(' expression ')' {$$ = $2;}
	;
%%
