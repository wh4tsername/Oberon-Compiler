%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "declaration.h"
    #include "expressions.h"
    #include "variables.h"

    #define YYERROR_VERBOSE 1
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
%token T_INTEGER
%token T_REAL
%token ASSIGNMENT_SYMBOL

%type <expression> expression
%type <logical_expression> logic_expression
%type <list> statement_sequence
%type <statement> statement

%%

module:
	MODULE IDENT ';' IMPORT import_list ';' VAR declaration_sequence program END IDENT '.' {};

program: 
	T_BEGIN statement_sequence {program = $2;}
	| {};

import_list: 
	{};

declaration_sequence: 
	declaration_sequence declaration ';' delimeter {}
	| {};

declaration:
	IDENT ':' T_INTEGER {/*variables_container.Add($1);*/}
	| IDENT ':' T_REAL {/*variables_container.Add($1);*/};

statement_sequence: 
	statement_sequence statement ';' delimeter {$1->add($2);  $$ = $1;}
	| {$$ = new ListOfStatements;};

delimeter:
	delimeter '\n' {}
	| {};

statement: 
	IDENT ASSIGNMENT_SYMBOL expression {$$ = new AssignStatement($1, $3);}
	| PRINT expression {$$ = new PrintStatement($2);}
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
