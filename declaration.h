#pragma once

#include "expressions.h"
#include "statements.h"
#include "oberon.tab.h"

int yylex();
void yyerror(const std::string& s);
