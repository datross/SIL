#include <iostream>

#include "stack.h"
#include "int.h"
#include "string.h"
#include "function.h"
#include "function_node.h"

using namespace std;

int main(int argc, char * argv[])
{
	/*sil::Stack stack;

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
	}*/

	sil::function::Function function("main", sil::vartype::INT, std::vector<sil::function::Function_parameter>());
	sil::function::Expression_ptr return_value(new sil::function::Int_node);
	((sil::function::Int_node*)return_value.get())->set_value(12);
	sil::function::Statement_ptr return_node(new sil::function::Return_node(function, *return_value));
	function.set_root(return_node);

	function.execute();

	cout << ((sil::Int*)function.get_return_value().get())->get_val() << endl;

    return 0;
}
