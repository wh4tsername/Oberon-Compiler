#include <iostream>
#include "expressions.h"
#include "errors.h"
#include "statements.h"

extern int yylex();
extern int yylineno;
extern void yyparse();
extern FILE* yyin;

ListOfStatements* program;

void yyerror(const std::string& string) {
  std::cerr << "Parser error: " << string << std::endl;
}

int main(int argc, char** argv) {
  FILE* handle;

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
    exit(USAGE_ERROR);
  }
  if (!(handle = fopen(argv[1], "r"))) {
    std::cerr << "Can't open file " << argv[1] << std::endl;
    exit(FILE_ACCESS_ERROR);
  }

  yyin = handle;
  yyparse();
  program->Run();

  return 0;
}
