#include "statements.h"
#include "errors.h"
#include "variables.h"

void ListOfStatements::run() {
  for (auto&& element : list_) {
    element->Run();
  }
}

void ListOfStatements::Add(Statement* state) {
  list_.emplace_back(state);
}

void PrintStatement::Run() {
  if (!expression_) {
    exit(NULL_POINTER_ERROR);
  }

  std::cout << expression_->Count();
}

void IfStatement::Run() {
  if (!__expression__) {
    exit(NULL_POINTER_ERROR);
  }

  if (static_cast<bool>(__expression__->Count())) {
    __state1__->run();
  } else if (__state2__) {
      __state2__->run();
  }
}

void AssignStatement::Run() {
  if (expression_) {
    if (expression_->GetType() == Expression::Type::T_STRING) {
      std::string result = expression_->CountString();
      if (!variables_container.ExistsString(variable_name_)) {
        std::cerr << variable_name_ << " isn't declared in this scope or has incompatible type\n";
        exit(USAGE_ERROR);
      }
      variables_container.ChangeString(variable_name_, result);
      return;
    }

    double value = expression_->Count();
    if (expression_->GetType() == Expression::Type::T_INT) {
      if (!variables_container.ExistsInt(variable_name_)) {
        std::cerr << variable_name_ << " isn't declared in this scope or has incompatible type\n";
        exit(NOT_DECLARED_VARIABLE);
      }
      variables_container.ChangeInt(variable_name_, static_cast<int>(value + 0.1));
    } else if (expression_->GetType() == Expression::Type::T_REAL) {
      if (!variables_container.ExistsDouble(variable_name_)) {
        std::cerr << variable_name_ << " isn't declared in this scope or has incompatible type\n";
        exit(NOT_DECLARED_VARIABLE);
      }
      variables_container.ChangeDouble(variable_name_, value);
    } else if (expression_->GetType() == Expression::Type::T_BOOL) {
      int value = expression_->Count();
      if (!variables_container.ExistsBool(variable_name_)) {
        std::cerr << variable_name_ << " isn't declared in this scope or has incompatible type\n";
        exit(NOT_DECLARED_VARIABLE);
      }
      variables_container.ChangeBool(variable_name_, value != 0);
    }
  } else {
    std::cerr << "Null pointer error\n";
    exit(NULL_POINTER_ERROR);
  }
}
