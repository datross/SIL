#include "stdlib_nodes.h"
#include "utilities.h"
#include <iostream>
#include <string>

using namespace sil;
using namespace function;
using namespace sil_std;

Output_node::Output_node() {
}

void Output_node::set_child(Expression_ptr _child) {
    child = _child;
}

void Output_node::execute() {
    child->execute();
    // TODO je crois bien qu'on est obligé de mettre un embranchement...
    if(child->get_return_value()->get_type() == vartype::INT) {
        std::cout << ((Int*)(child->get_return_value().get()))->get_val();
    } else if(child->get_return_value()->get_type() == vartype::FLOAT) {
        std::cout << ((Float*)(child->get_return_value().get()))->get_val();
    } else if(child->get_return_value()->get_type() == vartype::STRING) {
        std::cout << ((String*)(child->get_return_value().get()))->get_val();
    }
}

/* ------------------------------------------------------------------------- */

Input_node::Input_node() {
}

void Input_node::set_type(Expression_ptr child) {
    type = child;
}

void Input_node::execute() {
    type->execute();
    
    std::string line;
    std::getline(std::cin, line);
    
    if(type->get_return_value()->to_String()->get_val() == "int") {
        return_value = Variable_ptr(new Int( Utilities::convert<int, std::string>(line)));
    } else if(type->get_return_value()->to_String()->get_val() == "float") {
        return_value = Variable_ptr(new Float( Utilities::convert<float, std::string>(line)));
    } else if(type->get_return_value()->to_String()->get_val() == "string") {
        return_value = Variable_ptr(new String( line ));
    } else {
        // TODO throw exception
    }
}

/* ------------------------------------------------------------------------- */

Random_node::Random_node()
    : generator(std::chrono::system_clock::now().time_since_epoch().count()) {
}

void Random_node::set_inf(Expression_ptr child) {
    inf = child;
}

void Random_node::set_sup(Expression_ptr child) {
    sup = child;
}

void Random_node::set_type(function::Expression_ptr child) {
    type = child;
}

void Random_node::execute() {
    inf->execute();
    sup->execute();
    type->execute();
    
    if(type->get_return_value()->to_String()->get_val() == "int") {
        std::uniform_int_distribution<int>distribution(inf->get_return_value()->to_Int()->get_val(), sup->get_return_value()->to_Int()->get_val());
        return_value = Variable_ptr ( new Int( distribution(generator) ) );
    } else if(type->get_return_value()->to_String()->get_val() == "float") {
        std::uniform_real_distribution<float>distribution(inf->get_return_value()->to_Float()->get_val(), sup->get_return_value()->to_Float()->get_val());
        return_value = Variable_ptr ( new Float( distribution(generator) ) );
    } else {
        // TODO throw exception
    }
}