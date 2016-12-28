#include "stack.h"
#include "errors.h"

using namespace sil;

Stack::Stack() {
	push();
}

Stack::~Stack() {
}

Stack& Stack::get_instance() {
    static Stack singleton_instance;
    return singleton_instance;
}

void Stack::push() {
    std::map<std::string, Variable_ptr> scope;
    data.push_back(scope);
}

void Stack::pop() {
    data.pop_back();
}

Variable_ptr& Stack::operator[](const std::string name) {
	try {
		try { 
			return data[data.size() - 1].at(name); 
		} catch(const std::out_of_range& e) { 
			try {
				return data[0].at(name);
			} catch(const std::out_of_range& e) {
				throw;
			}
		}
	} catch(const std::out_of_range& e) {
		throw error::undeclared_variable(name);
	}
}

void Stack::create_variable(std::string name, Variable_ptr value) {
	std::pair<std::map<std::string, Variable_ptr>::iterator, bool> element = data[data.size() - 1].insert(std::make_pair(name, value));
	/* eventual debugging info given to user, if variable already exists (element.second == true) */
}
