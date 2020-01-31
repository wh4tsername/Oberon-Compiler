#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "errors.h"
#include "expressions.h"
#include "variables.h"

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
  explicit PrintStatement(Expression* expression) : expression_(expression) {}
  void Run() final;

 private:
  Expression* expression_;
};

class IfStatement : public Statement {
 public:
  IfStatement(Expression* expression, ListOfStatements* first_statement,
              ListOfStatements* second_statement)
      : expression_(expression),
        first_statement_(first_statement),
        second_statement_(second_statement) {}

  void Run() final;

 private:
  Expression* expression_;
  ListOfStatements* first_statement_;
  ListOfStatements* second_statement_;
};

class WhileStatement : public Statement {
 public:
  explicit WhileStatement(Expression* expression, ListOfStatements* statements)
      : expression_(expression), statements_(statements) {}
  void Run() final;

 private:
  Expression* expression_;
  ListOfStatements* statements_;
};

class DoStatement : public Statement {
 public:
  explicit DoStatement(Expression* expression, ListOfStatements* statements)
      : expression_(expression), statements_(statements) {}
  void Run() final;

 private:
  Expression* expression_;
  ListOfStatements* statements_;
};

class AssignStatement : public Statement {
  std::string variable_name_;
  Expression* expression_;

 public:
  AssignStatement(std::string variable_name, Expression* expression)
      : variable_name_(std::move(variable_name)), expression_(expression) {}
  void Run() final;
};
