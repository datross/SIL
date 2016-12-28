#include "stdlib_functions.h"
#include <vector>

using namespace sil;
using namespace function;
using namespace sil_std;

Function_ptr Stdlib_functions::print;
Function_ptr Stdlib_functions::input;
Function_ptr Stdlib_functions::random;

Node_pool Stdlib_functions::node_pool;
Stdlib_functions Stdlib_functions::instance;

Stdlib_functions::Stdlib_functions()
{    
    /* 'print' */
    {
        std::vector<Function_parameter> params = { Function_parameter("parameter", vartype::NOTYPE) };
        print = Function_ptr(new Function("print", vartype::INT, params));
        auto return_value = node_pool.add<Int_node>();
        return_value->set_value(0);
        auto return_statement = node_pool.add<Return_node>(print, return_value);
        auto print_value = node_pool.add<Read_node>("parameter");
        auto print_statement = node_pool.add<Output_node>();
        print_statement->set_child(print_value);
        std::vector<Statement_ptr> block_children = { print_statement, return_statement };
        auto block_statement = node_pool.add<Block_node>(block_children);
        print->set_root(block_statement);
    }
    
    /* 'input' */
    {
        std::vector<Function_parameter> params = { Function_parameter("type", vartype::STRING) };
        input = Function_ptr(new Function("input", vartype::NOTYPE, params));
        auto type_value = node_pool.add<Read_node>("type");
        auto return_value = node_pool.add<Input_node>();
        return_value->set_type(type_value);
        auto return_statement = node_pool.add<Return_node>(input, return_value);
        input->set_root(return_statement);
    }
    
    /* 'random' */
    {
        std::vector<Function_parameter> params = { Function_parameter("type", vartype::STRING), Function_parameter("inf", vartype::NOTYPE), Function_parameter("sup", vartype::NOTYPE) };
        random = Function_ptr(new Function("random", vartype::NOTYPE, params));
        auto type_value = node_pool.add<Read_node>("type");
        auto inf_value = node_pool.add<Read_node>("inf");
        auto sup_value = node_pool.add<Read_node>("sup");
        auto random_value = node_pool.add<Random_node>();
        random_value->set_inf(inf_value);
        random_value->set_sup(sup_value);
        random_value->set_type(type_value);
        auto return_statement = node_pool.add<Return_node>(random, random_value);
        random->set_root(return_statement);
    }
}