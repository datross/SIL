#include "function_pool.h"
#include <iostream>

using namespace sil;
using namespace function;

Function_pool::Function_pool() {
}

Function_ptr Function_pool::add(std::string name, 
                     vartype::variable_type return_type, 
                     std::vector<Function_parameter> parameters) {
        last = Function_ptr(new Function(name, return_type, parameters));
        functions[name] = last;
        return last;
}

void Function_pool::add(Function_ptr function) {
  functions[function->get_name()] = function;
}

Function_ptr Function_pool::get(std::string name) {
    auto it = functions.find(name);
    if(it == functions.end())
        return NULL;
    else
        return it->second;
}

Function_ptr Function_pool::get_last() const {
    return last;
}
