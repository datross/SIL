#ifndef PARSE_H
#define PARSE_H

#include <iostream>

#include "stack.h"
#include "int.h"
#include "string.h"
#include "function.h"
#include "function_node.h"
#include "stdlib_functions.h"
#include "node_pool.h"
#include "function_pool.h"

#include "json.hpp"

using json = nlohmann::json;

namespace sil{
    
class Parser {
public :
    Parser();
    std::shared_ptr<sil::function::Function_pool> parse_file(std::string);
private :
    std::shared_ptr<sil::function::Float_node> parse_float(json);
    std::shared_ptr<sil::function::Int_node> parse_int(json);
    std::shared_ptr<sil::function::String_node> parse_string(json);
    std::shared_ptr<sil::function::Read_node> parse_read(json);
    std::shared_ptr<sil::function::Expression_node> parse_expression(json);
    
    std::shared_ptr<sil::function::Write_node> parse_write(json);
    std::shared_ptr<sil::function::Allocate_node> parse_allocate(json);
    std::shared_ptr<sil::function::Block_node> parse_block(json);
    std::shared_ptr<sil::function::Return_node> parse_return(json);
    std::shared_ptr<sil::function::Call_node> parse_call(json);
    std::shared_ptr<sil::function::While_node> parse_while(json);
    std::shared_ptr<sil::function::If_else_node> parse_if_else(json);
    std::shared_ptr<sil::function::Statement_node> parse_statement(json);
    
    sil::function::Function_parameter parse_parameter (json);
    sil::function::Function_ptr parse_function(json);
    
    //transforms a string looking like "int" to parstype::type
    vartype::variable_type string_to_type(std::string);
    
    //Reads a file and converse it into a json object
    json file_to_json(std::string);
    
    sil::function::Node_pool pool;
    std::shared_ptr<sil::function::Function_pool> function_pool;
};
    
    
    
}
#endif
