#include <iostream>

#include "stack.h"
#include "int.h"
#include "string.h"
#include "function.h"
#include "function_node.h"
#include "stdlib_functions.h"

using namespace std;

int main(int argc, char * argv[])
{
// 	sil::Stack& stack = sil::Stack::get_instance();
// 
// 	stack.push();
// 
// 	sil::String a = sil::String("Hello");
// 	stack.create_variable("a", a);
// 	cout << ((sil::String&)stack["a"]).get_val() << std::endl;
// 
// 	//(sil::String&)stack["a"] = string("hey!");
// 	stack.pop();
// 
// 	try {
// 		cout << ((sil::String&)stack["a"]).get_val() << std::endl;
// 	} catch(const std::exception & e) {
// 		cout << e.what() << std::endl;
// 	}

        //on créé la fonction
	sil::function::Function_ptr function(new sil::function::Function("main", sil::vartype::INT, std::vector<sil::function::Function_parameter>()));
        
        // noeud de la valeur du retour de la fonction
	sil::function::Expression_ptr return_value(new sil::function::Int_node);
	std::dynamic_pointer_cast<sil::function::Int_node>(return_value)->set_value(5);
        
        // noeud de retour de la fonction
	sil::function::Statement_ptr return_node(new sil::function::Return_node(function, return_value));
        
        // noeud de la chaine à afficher
	sil::function::Expression_ptr print_value(new sil::function::String_node());	std::dynamic_pointer_cast<sil::function::String_node>(print_value)->set_value("Hello world!\n");
        
        // noeud de call de 'print'
        sil::function::Statement_ptr print_call(new sil::function::Call_node(*(sil::sil_std::Stdlib_functions::print)));
        std::vector<sil::function::Expression_ptr> print_parameters = { print_value };
        std::dynamic_pointer_cast<sil::function::Call_node>(print_call)->set_children(print_parameters);
        
        // noeud de block de la fonction 'main'
        std::vector<sil::function::Statement_ptr> block_children = { print_call, return_node };
        sil::function::Statement_ptr block_node(new sil::function::Block_node(block_children));
        
        // on assigne le noeud de retour à la fonction
	function->set_root(block_node);

	function->execute();

        // affiche la valeur de retour de la fonction 'main'
// 	cout << "Retour de la fonction 'main' : " << ((sil::Int*)function->get_return_value().get())->get_val() << endl;

    return 0;
}
