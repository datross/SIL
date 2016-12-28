#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "tree_utilities.h"
#include "variable.h"
#include "function.h"

#include <vector>
#include <string>
#include <iostream>

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
	Function_ptr function;
        std::vector<Expression_ptr> children;
public:
	Call_node(Function_ptr);
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
	Function_ptr function;

	/* children */
	Expression_ptr child;
public:
	Return_node(Function_ptr _function, Expression_ptr _child);
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

/* ------------------------------------------------------------------------- */

/* This node creates a variable in the stack */
class Allocate_node : public Statement_node {
private:
    vartype::variable_type type;
    std::string name;
public:
    Allocate_node(vartype::variable_type, std::string);
    virtual void execute();
};

/* ------------------------------------------------------------------------- */

/* This node writes a variable from the stack (it does not create it) */
class Write_node : public Statement_node {
private:
    std::string name;
    Expression_ptr child;
public:
    Write_node(std::string);
    
    void set_child(Expression_ptr);
    
    virtual void execute();    
};

/* ------------------------------------------------------------------------- */

/* Classic math operations */

/* type of the operation computed with the children. */
enum binary_operation_type {
    ADDITION,
    MULTIPLICATION
};

class Binary_math_node : public Expression_node {
private:
    binary_operation_type type;
    Expression_ptr left_child, right_child;
public:
    Binary_math_node(binary_operation_type);
    Binary_math_node();
    void set_left_child(Expression_ptr);
    void set_right_child(Expression_ptr);
    
    virtual void execute();
};

}
}

#endif