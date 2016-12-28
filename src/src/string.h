#ifndef VAR_STRING_H
#define VAR_STRING_H

#include "variable.h"
#include "int.h"
#include "float.h"

#include <string>

namespace sil {

class String : public Variable {
public:
	String();
	String(std::string);
	virtual ~String();
        
        /* cast function */
        virtual std::shared_ptr<Int> to_Int() const;
        virtual std::shared_ptr<Float> to_Float() const;
        virtual std::shared_ptr<String> to_String() const;
        
        static String make();

	void operator=(const String&);
	virtual String * clone();

	std::string get_val() { return *(std::string*)value; }
};

}

#endif