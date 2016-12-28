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
#include "utilities.h"

#include "json.hpp"

using namespace sil;
using namespace function;
using namespace std;

using json = nlohmann::json;

Parser::Parser() 
    : function_pool(new Function_pool()) {
    /* On ajout la librairie standard dans les fonctions. */
    function_pool->add(sil_std::Stdlib_functions::print);
}

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
    } else {
        cerr << "The file required is missing : " << name_file << endl;
    }
}


/******************** Expression parsing ************************/

std::shared_ptr<Float_node> Parser::parse_float(json j) {
    log_stream << "float" << std::endl;
    
    auto float_node_return = pool.add<Float_node>();
    float_node_return->set_value( (float) j["float"] );  
    return float_node_return; 
}

std::shared_ptr<Int_node> Parser::parse_int(json j) {
    log_stream << "int" << std::endl;
    
    auto int_node_return = pool.add<Int_node>();
    int_node_return->set_value( (int) j["int"] );  
    return int_node_return;
}

std::shared_ptr<String_node> Parser::parse_string(json j) {
    log_stream << "string" << std::endl;
    
    auto string_node_return = pool.add<String_node>();
    string_node_return->set_value(j["string"].get<string>());  
    return string_node_return;
}

std::shared_ptr<Read_node> Parser::parse_read(json j) {
    log_stream << "read : " << j["read"].get<string>() << std::endl;
    return pool.add<Read_node>(j["read"].get<string>());
}

std::shared_ptr<Expression_node> Parser::parse_expression(json j) {
    log_stream << "Parsing expression : ";
    
    if(j.find("int") != j.end())
        return this->parse_int(j);
    else if(j.find("string") != j.end())
        return this->parse_string(j);
    else if(j.find("float") != j.end())
        return this->parse_float(j);
    else if(j.find("read") != j.end())
        return this->parse_read(j);
    else
        cerr << "parser error : this is not the name of an expression"<< endl;
    
}


/**************** Statement parsing **********************/

std::shared_ptr<Allocate_node> Parser::parse_allocate(json j) {
    log_stream << "allocate : " << j["allocate"]["type"].get<string>() << " " << j["allocate"]["name"].get<string>() << std::endl;
    
    return pool.add<Allocate_node>(
        string_to_type( j["allocate"]["type"].get<string>()),
                                   j["allocate"]["name"].get<string>());
}

std::shared_ptr<Write_node> Parser::parse_write(json j) {
    log_stream << "write : " << j["write"].get<string>() << std::endl;
    
    auto write_return = pool.add<Write_node>(j["write"].get<string>());
    write_return->set_child(parse_expression(j["expr"]));
    return write_return;
}


std::shared_ptr<Block_node> Parser::parse_block(json j) {
    log_stream << "block" << std::endl;
    
    vector<Statement_ptr> children = {};
    for (json::iterator it = j["block"].begin(); it != j["block"].end(); ++it) {
        children.push_back(parse_statement(*it));
    }
    return pool.add<Block_node>(children);
}


std::shared_ptr<Return_node> Parser::parse_return(json j) {
    log_stream << "return" << std::endl;
    
    return pool.add<Return_node>(function_pool->get_last(),parse_expression(j["return"]));
}


std::shared_ptr<Call_node> Parser::parse_call(json j) {
    log_stream << "call : " << j["call"].get<string>() << std::endl;
    
    auto call_ret = pool.add<Call_node>(function_pool->get(j["call"].get<string>()));
    vector<Expression_ptr> children = {};
    for (json::iterator it = j["args"].begin(); it != j["args"].end(); ++it) {
        children.push_back(parse_expression(*it));
    }
    call_ret->set_children(children);
    return call_ret;
}

std::shared_ptr<Statement_node> Parser::parse_statement(json j) {
    log_stream << "Parsing statement : ";
    
    if(j.find("allocate") != j.end())
        return this->parse_allocate(j);
    else if(j.find("write") != j.end())
        return this->parse_write(j);
    else if(j.find("block") != j.end())
        return this->parse_block(j);
    else if(j.find("return") != j.end())
        return this->parse_return(j);
    else if(j.find("call") != j.end())
        return this->parse_call(j);
    else
        cerr << "parser error : this is not the name of a statement"<< endl;    
}


/****************************** Main function *************************/

Function_parameter Parser::parse_parameter (json j) {
    return Function_parameter(j["param"].get<string>(),string_to_type(j["type"].get<string>()));
}



Function_ptr Parser::parse_function(json j) {
            log_stream << "  > Function : ";
    
    vector<Function_parameter> parameters = {};
    for (json::iterator it = j["parameters"].begin(); it != j["parameters"].end(); ++it) {
        parameters.push_back(parse_parameter(*it));
    }
    auto function_ret = function_pool->add(
        j["function"].get<string>(), string_to_type(j["type"].get<string>()), 
        parameters);
            log_stream << function_ret->get_name() << std::endl;
    function_ret->set_root(parse_statement(j["statement"]));
    return function_ret;
}



shared_ptr<Function_pool> Parser::parse_file(string file) {
    log_stream << "Parsing file : " << file << "\n------------" << std::endl;
    json j = file_to_json(file);
    
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        parse_function(*it);
    }
    
    log_stream << "  => Running program...\n------------" << std::endl;
    
    return function_pool;
}


/****************************** Miscellaneous **************************/

vartype::variable_type Parser::string_to_type(string s) {
    if(s == "int")
        return vartype::INT;
    else if(s == "float")
        return vartype::FLOAT;
    else if(s == "string")
        return vartype::STRING;
    else if( s== "notype")
        return vartype::NOTYPE;
    else
        cerr<< "Parser error : the type " << s << " does not exist." <<endl;
}

