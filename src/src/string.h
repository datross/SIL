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

	void operator=(const String&);

	/* debug */
	std::string get_val() { return *(std::string*)value; }
};

}

#endif