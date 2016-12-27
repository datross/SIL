#include "variable.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace sil;

Variable::Variable()
	: value(NULL), type(vartype::NOTYPE)
{
}

Variable * Variable::clone(){
    return NULL;
}

// Variable::Variable(vartype::variable_type _type)
//     : value(NULL), type(_type) {
// }

// TODO check tout ça, parce que c'est le bordel

Variable::Variable(const Variable& source)
    : value(NULL), type(source.type) {
}

Variable& Variable::operator =(const Variable& source) {
//     value = NULL;
//     type = source.type;
    return *this;
}

Variable::Variable(const  vartype::variable_type _type) : type(_type) {
}

vartype::variable_type Variable::get_type() const {
    return type;
}