#include <iostream>

#include "stack.h"
#include "int.h"
#include "string.h"

using namespace std;

int main(int argc, char * argv[])
{
	sil::Stack stack;

	stack.push();

	sil::String a = sil::String("Hello");
	stack.create_variable("a", a);
	//cout << ((sil::String&)stack["a"]).get_val() << std::endl;

	//(sil::String&)stack["a"] = string("hey!");
	stack.pop();

	try {
		cout << ((sil::String&)stack["a"]).get_val() << std::endl;
	} catch(const std::exception & e) {
		cout << e.what() << std::endl;
	}
    return 0;
}
