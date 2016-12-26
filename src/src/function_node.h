#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "tree_utilities.h"
#include "variable.h"

#include <vector>
#include <string>

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

/* ------------------------------------------------------------------------- */

class Statement_node {
private:
public:
	Statement_node();
	virtual void execute();
};

/* ------------------------------------------------------------------------- */

class Call_node : public Statement_node, Expression_node {
private:
	Function& function;
        std::vector<Expression_ptr> children;
public:
	Call_node(Function& _function);
        void set_children(std::vector<Expression_ptr>);
	virtual void execute();
};

/* ------------------------------------------------------------------------- */

class Block_node : public Statement_node {
private:
	std::vector<Statement_ptr> children;
public:
	Block_node(std::vector<Statement_ptr> children);
	virtual void execute();
};

/* ------------------------------------------------------------------------- */

class Return_node : public Statement_node {
private:
	Function & function;

	/* children */
	Expression_node & child;
public:
	Return_node(Function & _function, Expression_node & _child);
	virtual void execute();
};

/* ------------------------------------------------------------------------- */

class Int_node : public Expression_node {
public:
	Int_node();
	void set_value(int value);
};

/* ------------------------------------------------------------------------- */

class Float_node : public Expression_node {
public:
	Float_node();
	void set_value(float value);
};

/* ------------------------------------------------------------------------- */

class String_node : public Expression_node {
public:
	String_node();
	void set_value(std::string value);
};

/* ------------------------------------------------------------------------- */

/* This node read a variable from the stack */
class Read_node : public Expression_node {
private:
    std::string variable_identifier;
public:
    Read_node(std::string);
    
    virtual void execute();
};

}
}

#endif