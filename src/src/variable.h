#ifndef VARIABLE_H
#define VARIABLE_H

#include <memory>

namespace sil {

namespace vartype {
    enum variable_type {
        INT    = 0, 
        FLOAT  = 1, 
        STRING = 2, 
        NOTYPE = 3
    };
}

class Variable;
class Int;
class Float;
class String;

/* Base class for every variables */
class Variable {
protected:
    void* value;
    const vartype::variable_type type;
    Variable(const vartype::variable_type);
public:
    Variable();
    virtual Variable * clone();
//     Variable(vartype::variable_type);
    Variable(const Variable&);
    Variable& operator =(const Variable&);
    
    /* cast function */
    virtual std::shared_ptr<Int> to_Int()       const { return NULL; }
    virtual std::shared_ptr<Float> to_Float()   const { return NULL; }
    virtual std::shared_ptr<String> to_String() const { return NULL; }
    
    virtual ~Variable() {};
    vartype::variable_type get_type() const;
    const void * get() const;
};

typedef std::shared_ptr<Variable> Variable_ptr;

}

#endif
