#pragma once

#include <string>
#include <vector>

enum ArithmeticOperation {
  ADD = -1,
  SUBSTRACT = -2,
  MULTIPLY = -3,
  DIVIDE = -4,
  UMINUS_ = -5
};

enum LogicalOperation {
  LT = 0,
  LE = 1,
  GT = 2,
  GE = 3,
  EQ = 4,
  NE = 5,
  AND = 6,
  OR = 7,
  NOT_ = 8
};

class Expression {
 public:
  virtual double Count() = 0;
};

class ArithmeticExpression : public Expression {
 public:
  ArithmeticExpression(int operation, Expression* lhs,
                       Expression* rhs)
      : operation_(operation), lhs_(lhs), rhs_(rhs) {}

  double Count() final;

 private:
  int operation_;
  Expression* lhs_;
  Expression* rhs_;
};

class VariableExpression : public Expression {
 public:
  explicit VariableExpression(const char* variable_name)
      : variable_name_(variable_name) {}

  ~VariableExpression();

  double Count() final;

 private:
  std::string variable_name_;
};

class NumeralExpression : public Expression {
 public:
  explicit NumeralExpression(int value) : value_(value) {}

  double Count() final { return value_; }

 private:
  double value_;
};

class LogicalExpression : public Expression {
 public:
  LogicalExpression(int operation, Expression* lhs,
                    Expression* rhs)
      : operation_(operation), lhs_(lhs), rhs_(rhs) {}

  double Count() final;

 private:
  int operation_;
  Expression* lhs_;
  Expression* rhs_;
};
