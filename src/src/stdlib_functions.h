#ifndef STDLIB_FUNCTIONS_H
#define STDLIB_FUNCTIONS_H

#include <memory>

#include "function_node.h"
#include "stdlib_nodes.h"
#include "function.h"
#include "node_pool.h"

namespace sil {
namespace sil_std {
    
/* This class handles the standard library functions. */

class Stdlib_functions {
private:
    /* This constructor builds every standard functions */
    Stdlib_functions();
    
    /* Unique instance of this class */
    static Stdlib_functions instance;

    /* pool which contains every node used by the functions. */
    static function::Node_pool node_pool;
public:    
    /**** stdlib functions ****/
    
    /* 'int print(value : NOTYPE)' */
    static function::Function_ptr print;
    
    /* 'type input(str_type: string)' with 'type' either int, float or string. */
    static function::Function_ptr input;
    
    /* 'type random(str_type : string, inf : NOTYPE, sup : NOTYPE)' */
    static function::Function_ptr random;
};
    
}
}

#endif