#include "statements.h"
#include "errors.h"
#include "variables.h"

void ListOfStatements::run() {
  for (auto&& element : __list__) {
    element->run();
  }
}

void ListOfStatements::add(Statement* state) {
  __list__.emplace_back(state);
}

void PrintStatement::run() {
  if (!__expression__) {
    exit(NULL_POINTER_ERROR);
  }

  std::cout << __expression__->Count();
}

void IfStatement::run() {
  if (!__expression__) {
    exit(NULL_POINTER_ERROR);
  }

  if (static_cast<bool>(__expression__->Count())) {
    __state1__->run();
  } else if (__state2__) {
      __state2__->run();
  }
}

void AssignStatement::run() {
  double value = __expression__->Count();
  variables_container.Add(__name__, value);
}
