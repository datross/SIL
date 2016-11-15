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

void Int::operator=(const Int& var) {
	*(int*)value = *(int*)var.value;
}
