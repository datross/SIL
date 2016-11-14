#ifndef STACK_H
#define STACK_H

#include <vector>
#include <map>
#include <string>

#include "variables.h"

namespace sil {

class Stack {
private:
    std::vector< std::map<std::string, Variable> > data;
public:
    Stack();
    ~Stack();
    void push();
    void pop();
    
    const Variable& read_variable(const std::__cxx11::string name) const;
    void write_variable(std::string, const Variable&);
    void create_variable(std::string, const Variable&);
};

}

#endif