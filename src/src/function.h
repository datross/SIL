#ifndef FUNCTION_H
#define FUNCTION_H

#include "tree_declarations.h"
#include "stack.h"
#include "function_node.h"

#include <string>
#include <vector>

namespace sil {

namespace function {

struct Function_parameter {
	std::string name;
	vartype::variable_type type;
};

class Function {
private:
	std::string name;
	std::vector<Function_parameter> parameters;
	Variable return_value;
	vartype::variable_type return_type;
	Statement_node root;

	friend class Return_node;
public:
	Function(std::string _name, std::vector<Function_parameter> _parameters);
	void set_root(Statement_node & _root);
	void execute();
	Variable & get_return_value();
};

}

}

#endif