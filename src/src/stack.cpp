#include "stack.h"

using namespace sil;

Stack::Stack() {
}

Stack::~Stack() {
}

void Stack::push() {
    std::map<std::string, Variable> scope;
    data.push_back(scope);
}

void Stack::pop() {
    data.pop_back();
}

const Variable& Stack::read_variable(std::string name) const {
    const Variable & v = data[data.size() - 1][name];
    return v;
}

void Stack::write_variable(std::string name, const Variable&) {
}

void Stack::create_variable(std::string name) {
}