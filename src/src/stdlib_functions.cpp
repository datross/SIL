#include "stdlib_functions.h"
#include <vector>

using namespace sil;
using namespace function;
using namespace sil_std;

Function_ptr Stdlib_functions::print;
Node_pool Stdlib_functions::node_pool;
Stdlib_functions Stdlib_functions::instance;

Stdlib_functions::Stdlib_functions()
{
    Function * fun_tmp;
    
    /* 'print' */
    std::vector<Function_parameter> params = { Function_parameter("parameter", vartype::NOTYPE) };
    fun_tmp = new Function("print", vartype::INT, params);
    auto return_value = node_pool.add<Int_node>();
    auto return_statement = node_pool.add<Return_node>(*fun_tmp, *return_value);
    auto print_value = node_pool.add<Read_node>("parameter");
    auto print_statement = node_pool.add<Output_node>();
    print_statement->set_child(print_value);
    std::vector<Statement_ptr> block_children = { print_statement, return_statement };
    auto block_statement = node_pool.add<Block_node>(block_children);
    print = Function_ptr(fun_tmp);
}