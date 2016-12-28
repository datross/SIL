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
    
    //Reads a file and converse it into a json object
    json file_to_json(std::string);

    std::shared_ptr<sil::function::Float_node> parse_float(json);
    std::shared_ptr<sil::function::Int_node> parse_int(json);
    std::shared_ptr<sil::function::String_node> parse_string(json);
    std::shared_ptr<sil::function::Read_node> parse_read(json);
    std::shared_ptr<sil::function::Expression_node> parse_expression(json);

    std::shared_ptr<sil::function::Write_node> parse_write(json);
    std::shared_ptr<sil::function::Allocate_node> parse_allocate(json);
    std::shared_ptr<sil::function::Block_node> parse_block(json);
    std::shared_ptr<sil::function::Return_node> parse_return(json);
    std::shared_ptr<sil::function::Statement_node> parse_statement(json);
    
  private :
    //transforme une chaîne du type "int" en type
    vartype::variable_type string_to_type(std::string);
    sil::function::Node_pool pool;
    sil::function::Function_pool function_pool;
  
  };



}
#endif
