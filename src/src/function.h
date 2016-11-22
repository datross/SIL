#ifndef FUNCTION_H
#define FUNCTION_H

#include "stack.h"
#include "function_node.h"

#include <string>
#include <vector>

namespace sil {

struct Function_parameter {
	std::string name;
	vartype::variable_type type;
};

class Function {
private:
	std::string name;
	std::vector<Function_parameter> parameters;
	// Variable return_value; ?
public:
	void execute();
};

}

#endif