#include "function_node.h"
#include "function.h"

#include "int.h"

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

void Call_node::execute() {
	function.execute();
	/* copy the variable, so the function can be called after without changing
	   the return value. */
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