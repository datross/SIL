#ifndef TREE_DECLARATIONS_H
#define TREE_DECLARATIONS_H

#include <memory>

namespace sil {
namespace function {

class Function;
class Expression_node;
class Statement_node;

class Return_node;

typedef std::shared_ptr<Statement_node>  Statement_ptr;
typedef std::shared_ptr<Expression_node> Expression_ptr;
typedef std::shared_ptr<Function> Function_ptr;

}

// // /* Function which creates a variable with specified type */
// #include "variable.h"
// #include "int.h"
// #include "float.h"
// #include "string.h"
// Variable make_variable(vartype::variable_type);
    
}

#endif
