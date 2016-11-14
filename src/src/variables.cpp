#include "variables.h"
#include <cstdlib>

#include <string>

using namespace sil;

Variable::Variable(vartype::variable_type _type)
    : type(_type) {
}

Variable::Variable(const Variable& source)
    : type(source.type) {
        
}

Variable::~Variable() {
    switch(type) {
        case vartype::INT: delete (int*)value; break;
        case vartype::FLOAT: delete (float*)value; break;
        case vartype::STRING: delete (std::string*)value; break;
        default: break;
    }
}

vartype::variable_type Variable::get_type() const {
    return type;
}