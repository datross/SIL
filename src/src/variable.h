#ifndef VARIABLE_H
#define VARIABLE_H

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
    //Variable(vartype::variable_type);
    //Variable(const Variable&);
    virtual ~Variable() {};
    vartype::variable_type get_type() const;
};

}

#endif
