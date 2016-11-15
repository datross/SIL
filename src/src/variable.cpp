#include "variable.h"
#include <cstdlib>

#include <string>

using namespace sil;

Variable::Variable()
	: value(NULL), type(vartype::NOTYPE)
{
}


/*Variable::Variable(vartype::variable_type _type)
    : value(NULL), type(_type) {
}*/

/*Variable::Variable(const Variable& source)
    : value(NULL), type(source.type) {    
}*/

Variable::Variable(const  vartype::variable_type _type) : type(_type) {
}

vartype::variable_type Variable::get_type() const {
    return type;
}
