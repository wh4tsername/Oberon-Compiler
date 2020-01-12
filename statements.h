#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "expressions.h"
#include "variables.h"
#include "errors.h"

class Statement {
 public:
  virtual void Run() = 0;
};

class ListOfStatements {
 public:
  ListOfStatements() = default;
  void Add(Statement* state);
  void Run();

 private:
  std::vector<Statement*> list_;
};

class PrintStatement : public Statement {
 public:
  explicit PrintStatement(Expression* expression) :
      expression_(expression) {}
  void Run() final;

 private:
  Expression* expression_;
};

class IfStatement : public Statement {
 public:
  IfStatement(Expression* expression,
              ListOfStatements* first_statement,
              ListOfStatements* second_statement) :
      expression_(expression),
      first_statement_(first_statement),
      second_statement_(second_statement) {}

  void Run() final;

 private:
  Expression* expression_;
  ListOfStatements *first_statement_;
  ListOfStatements *second_statement_;
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
