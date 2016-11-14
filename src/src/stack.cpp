#include "stack.h"
#include "errors.h"

using namespace sil;

Stack::Stack() {
}

Stack::~Stack() {
}

std::map<std::string, Variable>::iterator Stack::access(const std::string name) {
	std::map<std::string, Variable>::iterator it = data[data.size() - 1].find(name);
	if(it == data[data.size() - 1].end()) {
		throw error::undeclared_variable(name);
	}
	return it;
}

void Stack::push() {
    std::map<std::string, Variable> scope;
    data.push_back(scope);
}

void Stack::pop() {
    data.pop_back();
}

const Variable& Stack::read_variable(const std::string name) const {
	std::map<std::string, Variable>::const_iterator it = data[data.size() - 1].find(name);
	if(it == data[data.size() - 1].end()) {
		throw error::undeclared_variable(name);
	}
	return it->second;
}

void Stack::write_variable(std::string name, const Variable& value) {
	std::map<std::string, Variable>::iterator it = data[data.size() - 1].find(name);
	it->second
}

void Stack::create_variable(std::string name, const Variable& value) {
	std::pair<std::map<std::string, Variable>::iterator, bool> element = data.insert(value);
	/* eventual debugging info given to user, if variable already exists (element.second == true) */
}