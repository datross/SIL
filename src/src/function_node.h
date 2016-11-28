#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "tree_declarations.h"
#include "variable.h"

namespace sil {

namespace function {

class Expression_node {
private:
	Variable return_value;
public:
	Expression_node();
	virtual void execute();
	Variable & get_return_value();
};

class Statement_node {
private:
public:
	Statement_node();
	virtual void execute();
};

class Return_node : public Statement_node {
private:
	Function & function;

	/* children */
	Expression_node & child;
public:
	Return_node(Function & _function, Expression_node & _child);
	virtual void execute();
};

}
}

#endif