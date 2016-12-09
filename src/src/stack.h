#ifndef STACK_H
#define STACK_H

#include <vector>
#include <map>
#include <string>

#include "variable.h"

namespace sil {


//!\ finir singleton !
class Stack {
private:
    std::vector< std::map<std::string, Variable> > data;
    Stack();

    Stack(Stack const&);
    void operator=(Stack const&);
public:
    ~Stack();

    void push();
    void pop();
    
    Variable& operator[](const std::string);
    void create_variable(std::string, const Variable&);
};

}

#endif
