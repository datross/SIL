#include <iostream>

#include "stack.h"
#include "int.h"

using namespace std;

int main(int argc, char * argv[])
{
	sil::Stack stack;
	sil::Int a = sil::Int(5);
	stack.create_variable("a", a);
	cout << ((sil::Int&)stack["a"]).get_val() << std::endl;
	(sil::Int&)stack["a"] = 7;
	try {
		cout << ((sil::Int&)stack["b"]).get_val() << std::endl;
	} catch(const std::exception & e) {
		cout << e.what() << std::endl;
	}
    return 0;
}
