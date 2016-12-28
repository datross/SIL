#include "function_pool.h"

using namespace sil;
using namespace function;

Function_pool::Function_pool() {
}

Function_ptr Function_pool::add(std::string name, 
                     vartype::variable_type return_type, 
                     std::vector<Function_parameter> parameters) {
        functions[name] = Function_ptr(new Function(name, return_type, parameters));
        last = functions[name];
        return functions[name];
}

void Function_pool::add(Function_ptr function) {
  functions[function->get_name()] = function;
}

Function_ptr Function_pool::get(std::string name) {
    return functions[name];
}

Function_ptr Function_pool::get_last() const {
    return last;
}
