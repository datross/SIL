#include "function.h"

using namespace sil;
using namespace function;

Function_parameter::Function_parameter(){
}

Function_parameter::Function_parameter(std::string _name, vartype::variable_type _type) 
    : name(_name), type(_type) {
}

Function::Function(std::string _name,
			 	   vartype::variable_type _return_type, 
			 	   std::vector<Function_parameter> _parameters)
	: name(_name), 
	  return_type(_return_type), 
	  parameters(_parameters) {
}

void Function::set_root(Statement_ptr _root) {
	root = std::move(_root);
}

#include <iostream>

const std::vector<Function_parameter>& Function::get_parameters() const {
    return parameters;
}

void Function::execute() {
	root->execute();
}

Variable_ptr Function::get_return_value() {
	return return_value;
}
