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

#include "json.hpp"



using json = nlohmann::json;

namespace sil{
  
  class Parser {
  public :
    
    Parser();
    
    //Reads a file and converse it into a json object
    json file_to_json(std::string);
    
    std::shared_ptr<sil::function::Float_node> parse_float(json);
  
  private :
    sil::function::Node_pool pool;
  
  };



}
#endif
