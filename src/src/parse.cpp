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


std::shared_ptr<Expression_node> Parser::parse_expression(json j){
  if(j["int"])
    this->parse_int(j);
  else if(j["string"])
    this->parse_string(j);
  else if(j["int"])
    this->parse_int(j);
  else if(j["read"])
    this->parse_read(j);
  else if(j["allocate"])
    this->parse_allocate(j);
  else if(j["write"])
    this->parse_write(j);
  else
    cerr << "parser error : this is not the name of an expression"<< endl;
      
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

