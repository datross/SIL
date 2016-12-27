#include "float.h"

#include <iostream>

using namespace sil;

Float::Float() : Variable(vartype::FLOAT) {
	value = new float;
	*(float*)value = 0.;
}

Float::Float(float v) : Variable(vartype::FLOAT) {
	value = new float;
	*(float*)value = v;
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