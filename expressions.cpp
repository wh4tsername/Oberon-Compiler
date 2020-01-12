#include "expressions.h"
#include "variables.h"

double ArithmeticExpression::Count() {
  double lhs_value = 0;
  double rhs_value = 0;
  lhs_value = lhs_->Count();
  if (rhs_) {
    rhs_value = rhs_->Count();
  }

  if (operation_ == "+") {
    return lhs_value + rhs_value;
  }
  if (operation_ == "-") {
    return lhs_value - rhs_value;
  }
  if (operation_ == "*") {
    return lhs_value * rhs_value;
  }
  if (operation_ == "/") {
    if (rhs_value == 0) {
      std::cerr << "Runtime error: division by zero" << std::endl;
      exit(RUNTIME_ERROR);
    }
    return lhs_value / rhs_value;
  }
  if (operation_ == "@") {
    return -lhs_value;
  }

  exit(RUNTIME_ERROR);
}

VariableExpression::VariableExpression(const char* variable_name)
    : variable_name_(variable_name) {
  if (variables_container.ExistsInt(variable_name_)) {
    type_ = Type::T_INT;
  } else if (variables_container.ExistsDouble(variable_name_)){
    type_ = Type::T_REAL;
  } else if (variables_container.ExistsBool(variable_name_)) {
    type_ = Type::T_BOOL;
  } else if (variables_container.ExistsString(variable_name_)) {
    type_ = Type::T_STRING;
  } else {
    std::cerr << variable_name_ << " isn't declared in this scope" << std::endl;
    exit(NOT_DECLARED_VARIABLE);
  }
}

double VariableExpression::Count() {
  if (variables_container.ExistsInt(variable_name_)) {
    return variables_container.GetInt(variable_name_);
  } else if (variables_container.ExistsDouble(variable_name_)){
    return variables_container.GetDouble(variable_name_);
  } else if (variables_container.ExistsBool(variable_name_)) {
    return variables_container.GetBool(variable_name_);
  } else {
    std::cerr << variable_name_  << " isn't declared in this scope" << std::endl;
    exit(NOT_DECLARED_VARIABLE);
  }
}

std::string VariableExpression::CountString() {
  if (variables_container.ExistsString(variable_name_)) {
    return variables_container.GetString(variable_name_);
  } else {
    std::cerr << variable_name_  << " isn't declared in this scope" << std::endl;
    exit(NOT_DECLARED_VARIABLE);
  }
}

double LogicalExpression::Count() {
  if (operation_ == "TRUE") {
    return 1;
  }
  if (operation_ == "FALSE") {
    return 0;
  }

  if (operation_ == "EXPR") {
    return static_cast<bool>(lhs_->Count());
  }

  if (operation_ == "AND") {
    assert(lhs_->GetType() == Type::T_BOOL && rhs_->GetType() == Type::T_BOOL);
    return static_cast<bool>(lhs_->Count()) && static_cast<bool>(rhs_->Count());
  }
  if (operation_ == "OR") {
    assert(lhs_->GetType() == Type::T_BOOL && rhs_->GetType() == Type::T_BOOL);
    return static_cast<bool>(lhs_->Count()) || static_cast<bool>(rhs_->Count());
  }
  if (operation_ == "NOT") {
    assert(lhs_->GetType() == Type::T_BOOL);
    return !static_cast<bool>(lhs_->Count());
  }

  double lhs_value = lhs_->Count();
  double rhs_value = rhs_->Count();
  if (operation_ == "=") {
    return lhs_value == rhs_value;
  } else if (operation_ == "<") {
    return lhs_value < rhs_value;
  } else if (operation_ == ">") {
    return lhs_value > rhs_value;
  } else if (operation_ == "#") {
    return lhs_value != rhs_value;
  } else if (operation_ == ">=") {
    return lhs_value >= rhs_value;
  } else if (operation_ == "<=") {
    return lhs_value <= rhs_value;
  }

  exit(RUNTIME_ERROR);
}
