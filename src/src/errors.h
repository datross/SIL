#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>

namespace sil {

namespace error {
	
class undeclared_variable : public std::runtime_error {
public:
	undeclared_variable(const std::string name) : std::runtime_error(name) {}
	virtual const char* what() {
		return (std::string("SIL error: '") + std::string(what()) + std::string("' not declared.")).c_str();
	}
};

}
	
}

#endif
