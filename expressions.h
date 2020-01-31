#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "errors.h"

class Expression {
 protected:
  int type_;

 public:
  virtual double Count() { return 0; };
  virtual std::string CountString() { return std::string(); }

  int GetType() { return type_; }

  enum Type { T_INT = 0, T_REAL = 1, T_BOOL = 2, T_STRING = 3 };
};

class ArithmeticExpression : public Expression {
 public:
  ArithmeticExpression(std::string operation, Expression* lhs, Expression* rhs)
      : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {}

  double Count() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};

class NumeralExpression : public Expression {
 public:
  explicit NumeralExpression(int value) : value_(value) { type_ = Type::T_INT; }

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
  LogicalExpression(std::string operation, Expression* lhs, Expression* rhs)
      : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {
    type_ = Type::T_BOOL;
  }

  double Count() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};

class StringExpression : public Expression {
 public:
  explicit StringExpression(std::string operation, std::string str,
                            Expression* left, Expression* right)
      : operation_(std::move(operation)),
        variable_name_(std::move(str)),
        lhs_(left),
        rhs_(right) {
    type_ = Type::T_STRING;
  }

  explicit StringExpression(std::string operation, Expression* lhs,
                            Expression* rhs)
      : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {
    type_ = Type::T_STRING;
  }

  explicit StringExpression(const std::string& str)
      : result_string_(std::move(str.substr(1, str.size() - 2))),
        lhs_(nullptr),
        rhs_(nullptr) {
    type_ = Type::T_STRING;
  }

  std::string CountString() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
  std::string result_string_;
  std::string variable_name_;
};
