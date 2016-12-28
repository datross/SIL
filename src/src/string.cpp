#include "string.h"

using namespace sil;
using namespace std;

String::String() : Variable(vartype::STRING) {
	value = new string("");
}

String::String(string v) : Variable(vartype::STRING) {
	value = new string(v);
}

String::String(const String& source) : Variable(vartype::STRING) {
    *this = source;
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