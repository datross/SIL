#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "tree_declarations.h"
#include "variable.h"

namespace sil {

namespace function {

class Expression_node {
protected:
	Variable_ptr return_value;
public:
	Expression_node();
	virtual void execute();
	Variable_ptr get_return_value();
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

class Int_node : public Expression_node {
public:
	Int_node();
	void set_value(int value);
};

}
}

#endif