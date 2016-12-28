#include "int.h"
#include "utilities.h"

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

std::shared_ptr<Int> Int::to_Int() const {
    return std::shared_ptr<Int>(new Int(*(int*)value));
}
std::shared_ptr<Float> Int::to_Float() const {
    return std::shared_ptr<Float>(new Float((float)(*(int*)value)));
}
std::shared_ptr<String> Int::to_String() const {
    return std::shared_ptr<String>(new String(Utilities::convert<std::string, int>(*(int*)value)));
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