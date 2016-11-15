#ifndef STACK_H
#define STACK_H

#include <vector>
#include <map>
#include <string>

#include "variable.h"

namespace sil {

class Stack {
private:
    std::vector< std::map<std::string, Variable> > data;
public:
    Stack();
    ~Stack();
    void push();
    void pop();
    
    Variable& operator[](const std::string);
    void create_variable(std::string, const Variable&);
};

}

#endif
