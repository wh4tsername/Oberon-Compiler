#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Expression {
 protected:
  int type_;

 public:
  virtual double Count() = 0;
  virtual std::string CountString() {
    return std::string();
  }

  int GetType() {
    return type_;
  }

  enum Type{
    T_INT = 0,
    T_REAL = 1,
    T_BOOL = 2,
    T_STRING = 3
  };
};

class ArithmeticExpression : public Expression {
 public:
  ArithmeticExpression(std::string  operation, Expression* lhs,
                       Expression* rhs)
      : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {}

  double Count() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};

class NumeralExpression : public Expression {
 public:
  explicit NumeralExpression(int value) : value_(value) {
    type_ = Type::T_INT;
  }

  double Count() final { return value_; }

 private:
  int value_;
};

class DoubleExpression : public Expression {
 public:
  explicit DoubleExpression(double value) : value_(value) {
    type_ = Type::T_REAL;
  }

  double Count() final { return value_; }

 private:
  double value_;
};

class VariableExpression : public Expression {
 public:
  explicit VariableExpression(const char* variable_name);

  double Count() final;
  std::string CountString() final;

 private:
  std::string variable_name_;
};

class LogicalExpression : public Expression {
 public:
  LogicalExpression(std::string operation, Expression* lhs,
                    Expression* rhs)
      : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {
    type_ = Type::T_BOOL;
  }

  double Count() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};
