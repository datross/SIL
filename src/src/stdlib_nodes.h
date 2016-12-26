#ifndef STDLIB_NODE_H
#define STDLIB_NODE_H

#include "variable.h"
#include "int.h"
#include "float.h"
#include "string.h"
#include "tree_utilities.h"
#include "function_node.h"
#include "function.h"

namespace sil {
namespace sil_std {

// TODO pour l'instant en console, après peut-être dans un fichier ?
class Output_node : public function::Statement_node {
private:
    function::Expression_ptr child;
public:
    Output_node();
    void set_child(function::Expression_ptr);
    virtual void execute();
};
}
}

#endif