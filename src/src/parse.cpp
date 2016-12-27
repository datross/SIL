#include <iostream>
#include <fstream>
#include <memory>

#include "stack.h"
#include "int.h"
#include "string.h"
#include "function.h"
#include "function_node.h"
#include "stdlib_functions.h"
#include "node_pool.h"
#include "parse.h"

#include "json.hpp"

using namespace sil;
using namespace function;
using namespace std;

using json = nlohmann::json;

Node_pool pool;

Parser::Parser() {}


json Parser::file_to_json(string name_file) {
    
  ifstream file(name_file, ios::in);
  
  if(file)  
    {
      string string_file = "";
      string line;
      while (getline(file,line)){
	string_file += line;
      }
      file.close();
      cout << string_file<<endl;
      
      return json::parse(string_file);
    }
  else  
    cerr << "The file required is missing." << endl;
}

std::shared_ptr<Float_node> Parser::parse_float(json j){
  auto float_node_return = pool.add<Float_node>();
  float_node_return->set_value(j["float"]);
  return float_node_return;
  
}

