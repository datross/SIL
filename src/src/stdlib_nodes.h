#ifndef STDLIB_NODE_H
#define STDLIB_NODE_H

#include "variable.h"
#include "int.h"
#include "float.h"
#include "string.h"
#include "tree_utilities.h"
#include "function_node.h"
#include "function.h"

#include <chrono>
#include <random>

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

/* ------------------------------------------------------------------------- */

/* Read from standard input */
class Input_node : public function::Expression_node {
private:
    function::Expression_ptr type;
public:
    Input_node();
    void set_type(function::Expression_ptr);
    virtual void execute();
};

/* ------------------------------------------------------------------------- */

/* Generate random number */
class Random_node : public function::Expression_node {
private:
    function::Expression_ptr inf, sup, type;
    std::minstd_rand0 generator;
public:
    Random_node();
    void set_inf(function::Expression_ptr);
    void set_sup(function::Expression_ptr);
    void set_type(function::Expression_ptr);
    
    virtual void execute();
};




}
}

#endif