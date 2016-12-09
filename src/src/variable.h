#ifndef VARIABLE_H
#define VARIABLE_H

#include <memory>

namespace sil {

namespace vartype {
    enum variable_type {
        INT, FLOAT, STRING, NOTYPE
    };
}

class Variable {
protected:
    void* value;
    const vartype::variable_type type;
    Variable(const vartype::variable_type);
public:
	Variable();
    virtual Variable * clone();
    //Variable(vartype::variable_type);
    //Variable(const Variable&);
    virtual ~Variable() {};
    vartype::variable_type get_type() const;
};

typedef std::shared_ptr<Variable> Variable_ptr;

}

#endif
