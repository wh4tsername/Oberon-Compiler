#include "expressions.h"
#include <iostream>
#include "errors.h"
#include "variables.h"

double ArithmeticExpression::Count() {
  double lhs_value = 0;
  double rhs_value = 0;
  lhs_value = lhs_->Count();
  if (rhs_) {
    rhs_value = rhs_->Count();
  }
  switch (operation_) {
    case ArithmeticOperation::ADD:
      return lhs_value + rhs_value;
    case ArithmeticOperation::SUBSTRACT:
      return lhs_value - rhs_value;
    case ArithmeticOperation::MULTIPLY:
      return lhs_value * rhs_value;
    case ArithmeticOperation::DIVIDE:
      if (rhs_value == 0) {
        std::cerr << "Runtime error: division by zero" << std::endl;
        exit(RUNTIME_ERROR);
      }
    case ArithmeticOperation::UMINUS_:
      return -lhs_value;
  }
  return 0;
}

double VariableExpression::Count() {
  if (variables_container.Exists(variable_name_)) {
    return variables_container.Get(variable_name_);
  }
  std::cerr << variable_name_ << " isn't declared in this scope" << std::endl;
  exit(NOT_DECLARED_VARIABLE);
}

double LogicalExpression::Count() {
  bool lhs_value = false;
  bool rhs_value = false;
  lhs_value = static_cast<bool>(lhs_->Count());
  if (rhs_) {
    rhs_value = static_cast<bool>(rhs_->Count());
  }
  switch (operation_) {
    case LogicalOperation::EQ:
      return lhs_value == rhs_value;
    case LogicalOperation::NE:
      return lhs_value != rhs_value;
    case LogicalOperation::LT:
      return lhs_value < rhs_value;
    case LogicalOperation::LE:
      return lhs_value <= rhs_value;
    case LogicalOperation::GT:
      return lhs_value > rhs_value;
    case LogicalOperation::GE:
      return lhs_value >= rhs_value;
    case LogicalOperation::AND:
      return lhs_value && rhs_value;
    case LogicalOperation::OR:
      return lhs_value || rhs_value;
    case LogicalOperation::NOT_:
      return !lhs_value;
  }
}
