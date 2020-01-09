#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "expressions.h"
#include "variables.h"

class Statement {
 public:
  virtual void Run() = 0;
};

class ListOfStatements {
  std::vector<Statement*> list_;
 public:
  ListOfStatements() = default;
  void Add(Statement* state);
  void run();

};

class PrintStatement : public Statement {
  Expression* expression_;
 public:
  PrintStatement(Expression* expression) :
      expression_(expression) {}
  void Run() final;
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

  void Run() final;
};

class AssignStatement : public Statement {
  std::string variable_name_;
  Expression* expression_;

 public:
  AssignStatement(std::string variable_name, Expression* expression) :
      variable_name_(std::move(variable_name)),
      expression_(expression) {}
  void Run() final;
};
