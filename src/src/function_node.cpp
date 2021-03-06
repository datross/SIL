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

Call_node::Call_node(Function_ptr _function)
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
        auto it_params   = function->get_parameters().begin();
        auto it_children = children.begin();
        for(; it_children != children.end() && it_params != function->get_parameters().end(); ++it_children, ++it_params) {
            (*it_children)->execute();
            sil::Stack::get_instance().create_variable(it_params->name, (*it_children)->get_return_value());
        }
        
        /* function can be executed now. */
	function->execute();
        
        /* function has been executed, scope can be popped. */
        sil::Stack::get_instance().pop();
        
	/* copy the variable, so the function can be called after without changing the return value. */
	return_value = Variable_ptr(function->get_return_value()->clone());
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

Return_node::Return_node(Function_ptr _function, Expression_ptr _child) 
	: function(_function), child(_child) {

}

void Return_node::execute() {
	child->execute();
	function->return_value = child->get_return_value();
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
    return_value = Variable_ptr(Stack::get_instance()[variable_identifier]->clone());
}

/* ------------------------------------------------------------------------- */

Allocate_node::Allocate_node(vartype::variable_type _type, std::string _name)
    : type(_type), name(_name) {
}

void Allocate_node::execute() {
    Variable_ptr tmp;
    if(type == vartype::INT) {
        tmp = Variable_ptr(new Int());
    } else if(type == vartype::FLOAT) {
        tmp = Variable_ptr(new Float());
    } else if(type == vartype::STRING) {
        tmp = Variable_ptr(new String());
    } else {
        // TODO !
    }
        
    sil::Stack::get_instance().create_variable(name, tmp);
}

/* ------------------------------------------------------------------------- */

Write_node::Write_node(std::string _name)
    : name(_name) {
}

void Write_node::set_child(Expression_ptr _child) {
    child = _child;
}

void Write_node::execute() {
    child->execute();
    sil::Stack::get_instance()[name] = child->get_return_value();
}

/* ------------------------------------------------------------------------- */

Binary_math_node::Binary_math_node(binary_operation_type _type)
    : type(_type) {
}

Binary_math_node::Binary_math_node() {
}

void Binary_math_node::set_left_child(Expression_ptr child) {
    left_child = child;
}

void Binary_math_node::set_right_child(Expression_ptr child) {
    right_child = child;
}

/* Utility local functions */

template<class Major, class Minor>
Major add_variables(Variable& a, Variable& b) {
    return Major( (*(Minor*)a.get()) + (*(Minor*)a.get()) );
}

template<class Major, class Minor>
Major multiply_variables(Variable& a, Variable& b) {
    return Major( (*(Minor*)a.get()) * (*(Minor*)a.get()) );
}

void Binary_math_node::execute() {
    left_child->execute();
    right_child->execute();
    
    if(type == ADDITION) {
        /* String - whatever */
        if(left_child->get_return_value()->get_type()  == vartype::STRING || 
           right_child->get_return_value()->get_type() == vartype::STRING) {
            /* String - String */
            if(left_child->get_return_value()->get_type()  == vartype::STRING && 
               right_child->get_return_value()->get_type() == vartype::STRING) {
                return_value = Variable_ptr( 
                    add_variables<String, std::string>(
                        *(left_child->get_return_value()->to_String()), 
                        *(right_child->get_return_value()->to_String())
                    ).clone() 
                );
            } 
            /* String - other */
            else {
                std::cerr << "SIL Error: cannot add string with an other type." << std::endl;
            }
        }
        
        /* Int - Int */
        else if(left_child->get_return_value()->get_type()  == vartype::INT && 
                right_child->get_return_value()->get_type() == vartype::INT) {
            return_value = Variable_ptr( 
                add_variables<Int, int>(
                    *(left_child->get_return_value()->to_Int()), 
                    *(right_child->get_return_value()->to_Int())
                ).clone()
            );
        }
        
        /* Float - Int ou Float - Float */
        else if(left_child->get_return_value()->get_type()  == vartype::FLOAT || 
                right_child->get_return_value()->get_type() == vartype::FLOAT) {
            return_value = Variable_ptr( 
                add_variables<Float, float>(
                    *(left_child->get_return_value()->to_Float()), 
                    *(right_child->get_return_value()->to_Float())
                ).clone() 
            );
        }
    } 
    else if(type == MULTIPLICATION) {
        /* String - whatever */
        if(left_child->get_return_value()->get_type()  == vartype::STRING || 
           right_child->get_return_value()->get_type() == vartype::STRING) {
            std::cerr << "SIL Error: cannot multiply string with any type." << std::endl;
        }
        
        /* Int - Int */
        else if(left_child->get_return_value()->get_type()  == vartype::INT && 
                right_child->get_return_value()->get_type() == vartype::INT) {
            return_value = Variable_ptr( 
                multiply_variables<Int, int>(
                    *(left_child->get_return_value()->to_Int()), 
                    *(right_child->get_return_value()->to_Int())
                ).clone() 
            );
        }
        
        /* Float - Int ou Float - Float */
        else if(left_child->get_return_value()->get_type()  == vartype::FLOAT || 
                right_child->get_return_value()->get_type() == vartype::FLOAT) {
            return_value = Variable_ptr( 
                multiply_variables<Float, float>(
                    *(left_child->get_return_value()->to_Float()), 
                    *(right_child->get_return_value()->to_Float())
                ).clone() 
            );
        }
    }
    else if(type == GREATER) {
        /* String - whatever */
        if(left_child->get_return_value()->get_type()  == vartype::STRING || 
           right_child->get_return_value()->get_type() == vartype::STRING) {
            std::cerr << "SIL Error: cannot compare (greater) string with any type." << std::endl;
        }
        
        /* Float - Int ou Float - Float ou Int - Int */
        else {
            return_value = Variable_ptr( new Int(
                    left_child->get_return_value()->to_Float()->get_val() >
                    right_child->get_return_value()->to_Float()->get_val()
            ));
        }
    }
    else if(type == EQUAL) {
        /* String - whatever */
        if(left_child->get_return_value()->get_type()  == vartype::STRING || 
           right_child->get_return_value()->get_type() == vartype::STRING) {
            return_value = Variable_ptr( new Int(
                left_child->get_return_value()->to_String()->get_val() ==
                right_child->get_return_value()->to_String()->get_val()
            ));
        }
        
        /* Int - Int */
        else if(left_child->get_return_value()->get_type()  == vartype::INT && 
                right_child->get_return_value()->get_type() == vartype::INT) {
            return_value = Variable_ptr(new Int(
                    left_child->get_return_value()->to_Int()->get_val() == 
                    right_child->get_return_value()->to_Int()->get_val()
            ));
        }
        
        /* Float - Int ou Float - Float */
        else if(left_child->get_return_value()->get_type()  == vartype::FLOAT || 
                right_child->get_return_value()->get_type() == vartype::FLOAT) {
            return_value = Variable_ptr(new Int(
                    left_child->get_return_value()->to_Float()->get_val() ==
                    right_child->get_return_value()->to_Float()->get_val()
            ));
        }
    }
}

/* ------------------------------------------------------------------------- */

While_node::While_node() {
}

void While_node::set_condition_child(Expression_ptr child) {
    condition = child;
}

void While_node::set_loop_child(Statement_ptr child) {
    loop = child;
}

void While_node::execute() {
    while(true) {
        condition->execute();
        
        if(condition->get_return_value()->to_Int()->get_val() == 0)
            break;
        
        loop->execute();
    }
}

/* ------------------------------------------------------------------------- */

If_else_node::If_else_node() {
}

void If_else_node::set_condition_child(Expression_ptr child) {
    condition = child;
}

void If_else_node::set_statement_if(Statement_ptr child) {
    statement_if = child;
}

void If_else_node::set_statement_else(Statement_ptr child) {
    statement_else = child;
}

void If_else_node::execute() {
    condition->execute();
    if(condition->get_return_value()->to_Int()->get_val() != 0)
        statement_if->execute();
    else
        statement_else->execute();
}
