#include "float.h"

using namespace sil;

Float::Float() : Variable(vartype::FLOAT) {
	value = new Float;
	*(float*)value = 0;
}

Float::Float(float v) : Variable(vartype::FLOAT) {
	value = new Float;
	*(float*)value = v;
}

Float::~Float() {
	delete (float*)value;
}

void Float::operator=(const Float& var) {
	*(float*)value = *(float*)var.value;
}

Float * Float::clone(){
	Float * copy = new Float();
	*copy = *this;
	return copy;
}