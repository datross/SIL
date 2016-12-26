#ifndef VAR_STRING_H
#define VAR_STRING_H

#include "variable.h"
#include <string>

namespace sil {

class String : public Variable {
public:
	String();
	String(std::string);
	virtual ~String();
        
        static String make();

	void operator=(const String&);
	virtual String * clone();


	/* debug */
	std::string get_val() { return *(std::string*)value; }
};

}

#endif