#include "stdlib_nodes.h"
#include <iostream>

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