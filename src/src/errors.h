#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>

namespace sil {

namespace error {
	
class undeclared_variable : public std::runtime_error {
public:
	undeclared_variable(const std::string name) : std::runtime_error(std::string("SIL error: '") + std::string(name) + std::string("' not declared.")) {}
};

}
	
}

#endif
