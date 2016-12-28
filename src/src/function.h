#ifndef FUNCTION_H
#define FUNCTION_H

#include "tree_utilities.h"
#include "stack.h"
#include "function_node.h"

#include <string>
#include <vector>
#include <memory>

namespace sil {
namespace function {

struct Function_parameter {
	std::string name;
	vartype::variable_type type;
        
        Function_parameter();
        Function_parameter(std::string, vartype::variable_type);
};

class Function {
private:
	/* id of the function */
	std::string name;
	/* return type of the function */
	const vartype::variable_type return_type;
	/* specifies what are the parameters */
	std::vector<Function_parameter> parameters;
	/* return value, initialized with void */
	Variable_ptr return_value;
	/* root of the node tree, temporary */
	Statement_ptr root;

	/* Only Return_node can access function fields */
	friend class Return_node;
public:
	Function(std::string _name,
			 vartype::variable_type _return_type, 
			 std::vector<Function_parameter> _parameters);
	void set_root(Statement_ptr _root);
        const std::vector<Function_parameter>& get_parameters() const;
        std::string get_name() const;
	void execute();
	Variable_ptr get_return_value();
};

}
}

#endif
