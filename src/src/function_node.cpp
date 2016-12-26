#include "function_node.h"
#include "function.h"
#include "int.h"
#include "float.h"
#include "string.h"
#include "stack.h"

#include <iostream>

using namespace sil;
using namespace function;

Expression_node::Expression_node() {

}

void Expression_node::execute() {

}

Variable_ptr Expression_node::get_return_value() {
	return return_value;
}

/* ------------------------------------------------------------------------- */

Statement_node::Statement_node() {

}

void Statement_node::execute() {

}

/* ------------------------------------------------------------------------- */

Call_node::Call_node(Function& _function)
	: function(_function)
{
}

void Call_node::set_children(std::vector<Expression_ptr> _children) {
    children = _children;
}

void Call_node::execute() {
        /* function called needs its own scope */
        sil::Stack::get_instance().push();
        
        /* Allocate each parameter on the stack.
           Iterating is done on children, although we assume that there are as many children as parameters. */
        auto it_params   = function.get_parameters().begin();
        auto it_children = children.begin();
        for(; it_children != children.end() && it_params != function.get_parameters().end(); ++it_children, ++it_params) {
            (*it_children)->execute();
            sil::Stack::get_instance().create_variable(it_params->name, (*it_children)->get_return_value());
        }
        
        /* function can be executed now. */
	function.execute();
        
        /* function has been executed, scope can be popped. */
        sil::Stack::get_instance().pop();
        
	/* copy the variable, so the function can be called after without changing the return value. */
	return_value = Variable_ptr(function.get_return_value().get()->clone());
}

/* ------------------------------------------------------------------------- */

Block_node::Block_node(std::vector<Statement_ptr> _children) 
	: children(_children)
{
}

void Block_node::execute() {
	for(auto it = children.begin(); it != children.end(); ++it)
	{
		it->get()->execute();
	}
}

/* ------------------------------------------------------------------------- */

Return_node::Return_node(Function & _function, Expression_node & _child) 
	: function(_function), child(_child) {

}

void Return_node::execute() {
	child.execute();
	function.return_value = child.get_return_value();
}

/* ------------------------------------------------------------------------- */

Int_node::Int_node(){
}

void Int_node::set_value(int value){
	return_value = Variable_ptr(new Int(value));
}

/* ------------------------------------------------------------------------- */

Float_node::Float_node(){
}

void Float_node::set_value(float value){
	return_value = Variable_ptr(new Float(value));
}

/* ------------------------------------------------------------------------- */

String_node::String_node(){
}

void String_node::set_value(std::string value){
	return_value = Variable_ptr(new String(value));
}

/* ------------------------------------------------------------------------- */

Read_node::Read_node(std::string _variable_identifier) 
    : variable_identifier(_variable_identifier) {
}

void Read_node::execute() {
    return_value = std::shared_ptr<Variable>(Stack::get_instance()[variable_identifier].clone());
}