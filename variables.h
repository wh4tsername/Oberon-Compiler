#pragma once

#include <map>
#include <string>

#include "errors.h"
#include "statements.h"

class Statement;
class ListOfStatements;

class VariablesContainer {
 public:
  VariablesContainer() = default;

  void Add(const std::string& variable_name, const std::string& type);

  void ChangeInt(const std::string& variable_name, int value);
  void ChangeDouble(const std::string& variable_name, double value);
  void ChangeBool(const std::string& variable_name, bool value);
  void ChangeString(const std::string& variable_name, const std::string& value);

  int GetInt(const std::string& variable_name);
  double GetDouble(const std::string& variable_name);
  bool GetBool(const std::string& variable_name);
  std::string GetString(const std::string& variable_name);

  bool ExistsInt(const std::string& variable_name);
  bool ExistsDouble(const std::string& variable_name);
  bool ExistsBool(const std::string& variable_name);
  bool ExistsString(const std::string& variable_name);

 private:
  std::map<std::string, int> int_container_;
  std::map<std::string, double> double_container_;
  std::map<std::string, bool> bool_container_;
  std::map<std::string, std::string> string_container_;
};

extern VariablesContainer variables_container;
extern ListOfStatements* program;
