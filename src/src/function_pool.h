#ifndef FUNCTION_POOL_H
#define FUNCTION_POOL_H

#include "function.h"
#include "tree_utilities.h"
#include <map>
#include <string>

namespace sil {
namespace function {
    
class Function_pool {
private:
    std::map<std::string, Function_ptr> functions;
    Function_ptr last;
public:
    Function_pool();
    
    /* Create a function with given parameters, and a 
       shared_ptr on it. */
    Function_ptr add(std::string name, 
                     vartype::variable_type return_type, 
                     std::vector<Function_parameter> parameters);
    
    /* Returns a shared_ptr on the function with the given name. */
    Function_ptr get(std::string name);
    
    /* Returns  shared_ptr on the last function added to the pool (NULL if no function has been added yet). */
    Function_ptr get_last() const;
};

}
}

#endif