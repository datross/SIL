#include <iostream>

#include "stack.h"
#include "int.h"
#include "string.h"
#include "function.h"
#include "function_node.h"
#include "stdlib_functions.h"
#include "node_pool.h"

#include "json.hpp"

using namespace sil;
using namespace function;

using json = nlohmann::json;

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
        
        Node_pool pool;

        //on créé la fonction
	Function_ptr function(new Function("main", sil::vartype::INT, std::vector<Function_parameter>()));
        
        // noeud de la valeur du retour de la fonction
	auto return_value = pool.add<Int_node>();
	return_value->set_value(5);
        
        // noeud de retour de la fonction
	auto return_node = pool.add<Return_node>(function, return_value);
        
        // noeud d'allocation de la variable
        auto alloc_variable = pool.add<Allocate_node>(vartype::STRING, "chaine");
        
        // noeud de la chaine à afficher
	auto chaine = pool.add<String_node>();
        chaine->set_value("Hello world!\n");
        
        // noeud d'écriture de la variable
        auto write_variable = pool.add<Write_node>("chaine");
        write_variable->set_child(chaine);
        
        // noeud de lecture de la variable_identifier
        auto read_variable = pool.add<Read_node>("chaine");
        
        // noeud de call de 'print'
        auto print_call = pool.add<Call_node>(sil::sil_std::Stdlib_functions::print);
        std::vector<Expression_ptr> print_parameters = { read_variable };
        print_call->set_children(print_parameters);
        
        // noeud de block de la fonction 'main'
        std::vector<Statement_ptr> block_children = { alloc_variable, write_variable, print_call, return_node };
        auto block_node = pool.add<Block_node>(block_children);
        
        // on assigne le noeud de retour à la fonction
	function->set_root(block_node);

	function->execute();

        // affiche la valeur de retour de la fonction 'main'
// 	cout << "Retour de la fonction 'main' : " << ((sil::Int*)function->get_return_value().get())->get_val() << endl;

    return 0;
}
