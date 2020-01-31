#pragma once

#include "expressions.h"
#include "statements.h"
#include "variables.h"

extern ListOfStatements* program;
extern VariablesContainer variables_container;

#include "oberon.tab.h"

int yylex();
void yyerror(const std::string& s);
