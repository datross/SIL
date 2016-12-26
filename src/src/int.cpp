#include "int.h"

using namespace sil;

Int::Int() : Variable(vartype::INT) {
	value = new int;
	*(int*)value = 0;
}

Int::Int(int v) : Variable(vartype::INT) {
	value = new int;
	*(int*)value = v;
}

Int::~Int() {
	delete (int*)value;
}

Int Int::make() {
    return Int();
}

void Int::operator=(const Int& var) {
	*(int*)value = *(int*)var.value;
}

Int * Int::clone(){
	Int * copy = new Int();
	*copy = *this;
	return copy;
}