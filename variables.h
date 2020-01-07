#pragma once

#include <map>
#include <string>
#include "statements.h"

class ListOfStatements;

class VariablesContainer {
 public:
  VariablesContainer() = default;

  void Add(const std::string& variable_name, double value = 0);

  double Get(const std::string& variable_name);

  bool Exists(const std::string& variable_name);

 private:
  std::map<std::string, double> variables;
};

static VariablesContainer variables_container;
extern ListOfStatements* program;
