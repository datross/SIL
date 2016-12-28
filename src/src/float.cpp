#include "float.h"
#include "utilities.h"

using namespace sil;

Float::Float() : Variable(vartype::FLOAT) {
	value = new float;
	*(float*)value = 0.;
}

Float::Float(float v) : Variable(vartype::FLOAT) {
	value = new float;
	*(float*)value = v;
}

std::shared_ptr<Int> Float::to_Int() const {
    return std::shared_ptr<Int>(new Int( (int)(*(float*)value) ));
}
std::shared_ptr<Float> Float::to_Float() const {
    return std::shared_ptr<Float>(new Float(*(float*)value));
}
std::shared_ptr<String> Float::to_String() const {
    return std::shared_ptr<String>(new String(Utilities::convert<std::string, float>(*(float*)value)));
}

Float::~Float() {
	delete (float*)value;
}

Float Float::make() {
    return Float();
}

void Float::operator=(const Float& var) {
	*(float*)value = *(float*)var.value;
}

Float * Float::clone(){
	Float * copy = new Float();
	*copy = *this;
	return copy;
}