#include "variables.h"

void VariablesContainer::Add(
    const std::string& variable_name, const std::string& type) {
  if (type == "int") {
    int_container_[variable_name] = int();
  } else if (type == "double") {
    double_container_[variable_name] = double();
  } else if (type == "bool") {
    bool_container_[variable_name] = bool();
  } else if (type == "string") {
    string_container_[variable_name] = std::string();
  } else {
    std::cerr << "unknown type" << std::endl;
    exit(RUNTIME_ERROR);
  }
}

void VariablesContainer::ChangeInt(const std::string &variable_name, int value) {
  if (ExistsInt(variable_name)) {
    int_container_[variable_name] = value;
  } else {
    std::cerr << variable_name << " isn't declared in this scope or has incompatible type\n";
    exit(USAGE_ERROR);
  }
}

void VariablesContainer::ChangeDouble(const std::string &variable_name, double value) {
  if (ExistsDouble(variable_name)) {
    double_container_[variable_name] = value;
  } else {
    std::cerr << variable_name << " isn't declared in this scope or has incompatible type\n";
    exit(USAGE_ERROR);
  }
}

void VariablesContainer::ChangeBool(const std::string &variable_name, bool value) {
  if (ExistsBool(variable_name)) {
    bool_container_[variable_name] = value;
  } else {
    std::cerr << variable_name << " isn't declared in this scope or has incompatible type\n";
    exit(USAGE_ERROR);
  }
}

void VariablesContainer::ChangeString(const std::string &variable_name, const std::string& value) {
  if (ExistsString(variable_name)) {
    string_container_[variable_name] = value;
  } else {
    std::cerr << variable_name << " isn't declared in this scope or has incompatible type\n";
    exit(USAGE_ERROR);
  }
}

int VariablesContainer::GetInt(
    const std::string& variable_name) {
  if (ExistsInt(variable_name)) {
    return int_container_[variable_name];
  }
  exit(NOT_DECLARED_VARIABLE);
}

double VariablesContainer::GetDouble(
    const std::string& variable_name) {
  if (ExistsDouble(variable_name)) {
    return double_container_[variable_name];
  }
  exit(NOT_DECLARED_VARIABLE);
}

std::string VariablesContainer::GetString(
    const std::string& variable_name) {
  if (ExistsString(variable_name)) {
    return string_container_[variable_name];
  }
  exit(NOT_DECLARED_VARIABLE);
}

bool VariablesContainer::GetBool(
    const std::string& variable_name) {
  if (ExistsBool(variable_name)) {
    return bool_container_[variable_name];
  }
  exit(NOT_DECLARED_VARIABLE);
}

bool VariablesContainer::ExistsInt(
    const std::string& variable_name) {
  return int_container_.count(variable_name) > 0;
}

bool VariablesContainer::ExistsDouble(
    const std::string& variable_name) {
  return double_container_.count(variable_name) > 0;
}

bool VariablesContainer::ExistsString(
    const std::string& variable_name) {
  return string_container_.count(variable_name) > 0;
}

bool VariablesContainer::ExistsBool(
    const std::string& variable_name) {
  return bool_container_.count(variable_name) > 0;
}

VariablesContainer variables_container;
