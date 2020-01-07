#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include "expressions.h"
#include "variables.h"

class Statement {
 public:
  virtual void run() = 0;
};

class ListOfStatements {
  std::vector<Statement*> __list__;
 public:
  ListOfStatements() = default;
  void add(Statement* state);
  void run();

};

class PrintStatement : public Statement {
  Expression* __expression__;
 public:
  PrintStatement(Expression* expression):
      __expression__(expression) {}
  void run() final;
};

class IfStatement : public Statement {
  LogicalExpression* __expression__;
  ListOfStatements *__state1__;
  ListOfStatements *__state2__;
 public:
  IfStatement(LogicalExpression* expression,
              ListOfStatements* state1,
              ListOfStatements* state2) :
      __expression__(expression),
      __state1__(state1),
      __state2__(state2) {}

  void run() final;
};

class AssignStatement : public Statement {
  std::string __name__;
  Expression* __expression__;

 public:
  AssignStatement(std::string name, Expression* expression) :
      __name__(std::move(name)),
      __expression__(expression) {}
  void run() final;
};
