#pragma once

#include "expressions.h"
#include "oberon.tab.h"
#include "statements.h"

int yylex();
void yyerror(const std::string& s);
