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

Variable::Variable(const Variable& source)
    : value(NULL), type(source.type) {
}

/* This function must not be called. */
Variable& Variable::operator =(const Variable& source) {
    return *this;
}

Variable::Variable(const  vartype::variable_type _type) : type(_type) {
}

vartype::variable_type Variable::get_type() const {
    return type;
}

const void * Variable::get() const {
    return value;
}