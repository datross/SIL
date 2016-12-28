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

class file_error : public std::runtime_error {
public:
	file_error(const std::string name) : std::runtime_error(std::string("SIL Parsing error: '") + std::string(name) + std::string("' openning failed.")) {}
};

}	
}

#endif
