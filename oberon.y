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
%token T_INTEGER T_REAL T_BOOL T_STRING
%token ASSIGNMENT_SYMBOL
%token T_LE T_GE
%token T_AND T_OR T_NOT
%token T_TRUE T_FALSE

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
	IDENT ':' T_INTEGER {variables_container.Add($1, "int");}
	| IDENT ':' T_REAL {variables_container.Add($1, "double");};
	| IDENT ':' T_BOOL {variables_container.Add($1, "bool");}
        | IDENT ':' T_STRING {variables_container.Add($1, "string");};

statement_sequence: 
	statement_sequence statement ';' delimeter {$1->Add($2);  $$ = $1;}
	| {$$ = new ListOfStatements;};

delimeter:
	delimeter '\n' {}
	| {};

statement: 
	IDENT ASSIGNMENT_SYMBOL expression {$$ = new AssignStatement($1, $3);}
	| PRINT expression {$$ = new PrintStatement($2);}
	| IDENT ASSIGNMENT_SYMBOL logic_expression {$$ = new AssignStatement($1, $3);}
        | PRINT logic_expression {$$ = new PrintStatement($2);}
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
	expression '<' expression {$$ = new LogicalExpression("<", $1, $3);}
	| expression '>' expression {$$ = new LogicalExpression(">", $1, $3);}
	| expression T_LE expression {$$ = new LogicalExpression("<=", $1, $3);}
	| expression T_GE expression {$$ = new LogicalExpression(">=", $1, $3);}
	| expression '=' expression {$$ = new LogicalExpression("=", $1, $3);}
	| expression '#' expression {$$ = new LogicalExpression("#", $1, $3);}
	| logic_expression T_AND logic_expression {$$ = new LogicalExpression("AND", $1, $3);}
	| logic_expression T_OR logic_expression {$$ = new LogicalExpression("OR", $1, $3);}
	| T_NOT logic_expression %prec NOT {$$ = new LogicalExpression("NOT", $2, NULL);}
	| '(' logic_expression ')' {$$ = new LogicalExpression("()", $2, NULL);}
	| T_TRUE {$$ = new LogicalExpression("TRUE", NULL, NULL); }
        | T_FALSE {$$ = new LogicalExpression("FALSE", NULL, NULL);}
	;

expression:
	IDENT {$$ = new VariableExpression($1);}
	| NUMBER {$$ = new NumeralExpression($1);}
	| REAL {$$ = new DoubleExpression($1);}
	| '-' expression %prec UMINUS {$$ = new ArithmeticExpression(-5, $2, NULL);}
	| expression '+' expression {$$ = new ArithmeticExpression(-1, $1, $3);}
	| expression '-' expression {$$ = new ArithmeticExpression(-2, $1, $3);}
	| expression '*' expression {$$ = new ArithmeticExpression(-3, $1, $3);}
	| expression '/' expression {$$ = new ArithmeticExpression(-4, $1, $3);}
	| '(' expression ')' {$$ = $2;}
	;
%%
