#include "statements.h"

void ListOfStatements::Run() {
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

  if (expression_->GetType() == Expression::T_BOOL) {
    std::cout << (static_cast<bool>(expression_->Count()) ? "true" : "false");
  } else {
    std::cout << expression_->Count();
  }

  std::cout << std::endl;
}

void IfStatement::Run() {
  if (!expression_) {
    exit(NULL_POINTER_ERROR);
  }

  if (static_cast<bool>(expression_->Count())) {
    first_statement_->Run();
  } else if (second_statement_) {
    second_statement_->Run();
  }
}

void AssignStatement::Run() {
  if (expression_) {
    if (expression_->GetType() == Expression::Type::T_STRING) {
      std::string result = expression_->CountString();
      if (!variables_container.ExistsString(variable_name_)) {
        std::cerr << variable_name_ << " isn't declared in this scope or has incompatible type\n";
        exit(NOT_DECLARED_VARIABLE);
      }
      variables_container.ChangeString(variable_name_, result);
      return;
    }

    double value = expression_->Count();
    if (variables_container.ExistsInt(variable_name_)) {
      variables_container.ChangeInt(variable_name_, static_cast<int>(value));
    } else if (variables_container.ExistsDouble(variable_name_)) {
      variables_container.ChangeDouble(variable_name_, value);
    } else if (variables_container.ExistsBool(variable_name_)) {
      variables_container.ChangeBool(variable_name_, static_cast<bool>(value));
    } else {
      std::cerr << variable_name_ << " isn't declared in this scope or has incompatible type\n";
      exit(NOT_DECLARED_VARIABLE);
    }
  } else {
    std::cerr << "Null pointer error\n";
    exit(NULL_POINTER_ERROR);
  }
}
