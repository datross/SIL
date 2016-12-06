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

Statement_node::Statement_node() {

}

void Statement_node::execute() {

}

Return_node::Return_node(Function & _function, Expression_node & _child) 
	: function(_function), child(_child) {

}

void Return_node::execute() {
	child.execute();
	function.return_value = child.get_return_value();
}

Int_node::Int_node(){
}

void Int_node::set_value(int value){
	return_value = Variable_ptr(new Int(value));
}