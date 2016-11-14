#ifndef VARIABLES_H
#define VARIABLES_H

namespace sil {

namespace vartype {
    enum variable_type {
        INT, FLOAT, STRING, NOTYPE
    };
}

class Variable {
private:
    void* value;
    const vartype::variable_type type;
public:
	Variable();
    Variable(vartype::variable_type);
    Variable(const Variable&);
    ~Variable();
    vartype::variable_type get_type() const;
};

/*class Int : public Variable {
};

class Float : public Variable {
};

class String : public Variable {
};*/

}

#endif