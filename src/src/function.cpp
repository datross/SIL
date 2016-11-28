#include "function.h"

using namespace sil;
using namespace function;

Function::Function(std::string _name, std::vector<Function_parameter> _parameters) 
	: name(_name), parameters(_parameters) {

}

void Function::set_root(Statement_node & _root) {
	root = _root;
}

void Function::execute() {
	root.execute();
}

Variable & Function::get_return_value() {
	return return_value;
}
