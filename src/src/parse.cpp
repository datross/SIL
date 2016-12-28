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
#include "function_pool.h"
#include "parse.h"

#include "json.hpp"

using namespace sil;
using namespace function;
using namespace std;

using json = nlohmann::json;



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
      
      return json::parse(string_file);
    }
  else  
    cerr << "The file required is missing." << endl;
}



/******************** Expression parsing ************************/
std::shared_ptr<Float_node> Parser::parse_float(json j){
  auto float_node_return = pool.add<Float_node>();
  float_node_return->set_value( (float) j["float"] );  
  return float_node_return; 
}

std::shared_ptr<Int_node> Parser::parse_int(json j){
  auto int_node_return = pool.add<Int_node>();
  int_node_return->set_value( (int) j["int"] );  
  return int_node_return;
}

std::shared_ptr<String_node> Parser::parse_string(json j){
  auto string_node_return = pool.add<String_node>();
  string_node_return->set_value(j["string"].get<string>());  
  return string_node_return;
}

std::shared_ptr<Read_node> Parser::parse_read(json j){
  return pool.add<Read_node>(j["read"].get<string>());
}

std::shared_ptr<Expression_node> Parser::parse_expression(json j){
  if(j["int"])
    return this->parse_int(j);
  else if(j["string"])
    return this->parse_string(j);
  else if(j["int"])
    return this->parse_int(j);
  else if(j["read"])
    return this->parse_read(j);
  else
    cerr << "parser error : this is not the name of an expression"<< endl;
      
}





/**************** Statement parsing **********************/

std::shared_ptr<Allocate_node> Parser::parse_allocate(json j){
  
  return pool.add<Allocate_node>(
			       string_to_type( j["allocate"]["type"]),
			       j["allocate"]["name"]);
}

std::shared_ptr<Write_node> Parser::parse_write(json j){
  
  auto write_return = pool.add<Write_node>(j["write"].get<string>());
  write_return->set_child(parse_expression(j["expr"]));
  return write_return;
}


std::shared_ptr<Block_node> Parser::parse_block(json j){
  vector<Statement_ptr> children = {};
  for (json::iterator it = j.begin(); it != j.end(); ++it) {
    children.push_back(parse_statement(*it));
  }
  return pool.add<Block_node>(children);
}


std::shared_ptr<Return_node> Parser::parse_return(json j){
  return pool.add<Return_node>(function_pool.get_last(),parse_expression(j["return"]));
}


std::shared_ptr<Call_node> Parser::parse_call(json j){
  auto call_ret = pool.add<Call_node>(function_pool.get(j["call"].get<string>()));
  vector<Expression_ptr> children = {};
  for (json::iterator it = j["args"].begin(); it != j["args"].end(); ++it) {
    children.push_back(parse_expression(*it));
  }
  call_ret->set_children(children);
  return call_ret;
  
}

std::shared_ptr<Statement_node> Parser::parse_statement(json j){
  if(j["allocate"])
    return this->parse_allocate(j);
  else if(j["write"])
    return this->parse_write(j);
  else if(j["block"])
    return this->parse_block(j);
  else if(j["return"])
    return this->parse_return(j);
  else if(j["call"])
    return this->parse_return(j);
  else
    cerr << "parser error : this is not the name of a statement"<< endl;
      
}



vartype::variable_type Parser::string_to_type(string s){
  if(s=="int")
    return vartype::INT;
  else if(s=="float")
    return vartype::FLOAT;
  else if(s=="string")
    return vartype::STRING;
  else if(s=="notype")
    return vartype::NOTYPE;
  else
    cerr<<"Parser error : the type "<<s<<" does not exist."<<endl;
}

