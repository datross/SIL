#include "string.h"
#include "utilities.h"

using namespace sil;
using namespace std;

String::String() : Variable(vartype::STRING) {
	value = new string("");
}

String::String(string v) : Variable(vartype::STRING) {
	value = new string(v);
}

std::shared_ptr<Int> String::to_Int() const {
    return std::shared_ptr<Int>(new Int( Utilities::convert<int, std::string>(*(std::string*)value) ));
}
std::shared_ptr<Float> String::to_Float() const {
    return std::shared_ptr<Float>(new Float( Utilities::convert<float, std::string>(*(std::string*)value) ));
}
std::shared_ptr<String> String::to_String() const {
    return std::shared_ptr<String>(new String(*(std::string*)value));
}

String::~String() {
	delete (string*)value;
}

String String::make() {
    return String();
}

void String::operator=(const String& var) {
	*(string*)value = *(string*)var.value;
}

String * String::clone(){
	String * copy = new String();
	*copy = *this;
	return copy;
}