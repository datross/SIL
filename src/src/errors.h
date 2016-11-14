#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>

namespace sil {

namespace error {
	
class undeclared_variable : public std::exception {
	const std::string message;
	//const char* message;
public:
	undeclared_variable(const std::string name) : message("SIL error: variable '" + name + "' undeclared.") {}
	virtual ~undeclared_variable() throw() {}
	const char* what() const throw() {
		return message.c_str();
	}
};

}
	
}

#endif