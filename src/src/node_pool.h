#ifndef NODE_POOL_H
#define NODE_POOL_H

#include "function_node.h"
#include "tree_utilities.h"

#include <list>
#include <type_traits>

namespace sil {
namespace function {
 
/* This class is a utility to manage nodes,
   and destroy them. */
    
class Node_pool {
private:
    std::list<Statement_ptr> statements;
    std::list<Expression_ptr> expressions;
    
    void push(Expression_ptr);
    void push(Statement_ptr);
public:
    Node_pool();
    ~Node_pool();
    
    template<class node_type, class... ctor_args>
    std::shared_ptr<node_type> add(ctor_args... args) {
        std::shared_ptr<node_type> ptr(new node_type(args...));
        push(ptr);
        return ptr;
    }
};
    
}
}

#endif