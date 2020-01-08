#include "variables.h"
#include "errors.h"

void VariablesContainer::Add(
    const std::string& variable_name, double value) {
  variables[variable_name] = value;
}

double VariablesContainer::Get(
    const std::string& variable_name) {
  if (Exists(variable_name)) {
    return variables[variable_name];
  }
  exit(NOT_DECLARED_VARIABLE);
}

bool VariablesContainer::Exists(
    const std::string& variable_name) {
  return variables.count(variable_name) > 0;
}

VariablesContainer variables_container;
