#ifndef STACK_H
#define STACK_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "variable.h"
#include "tree_utilities.h"
#include "stack.h"

namespace sil {

class Stack {
private:
    std::vector< std::map<std::string, Variable_ptr> > data;
    Stack();

    Stack(Stack const&);
    void operator=(Stack const&);
public:
    /* singleton instance getter */
    static Stack& get_instance();
    
    ~Stack();

    void push();
    void pop();
    
    Variable_ptr& operator[](const std::string);
    void create_variable(std::string, Variable_ptr);
};

}

#endif
