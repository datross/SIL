#include <iostream>
#include <string>

#include "stack.h"
#include "int.h"
#include "string.h"
#include "function.h"
#include "function_node.h"
#include "stdlib_functions.h"
#include "node_pool.h"
#include "parse.h"
#include "utilities.h"

#include "json.hpp"

using namespace sil;
using namespace function;

using json = nlohmann::json;

int main(int argc, char * argv[])
{
    /* Check if there is an input file */
    if(argc < 2) {
        std::cerr << "SIL - No input file." << std::endl;
        std::cerr << "Syntax : 'sil [--verbose|-v] input_file'" << std::endl;
    }
    
    /* Check if it is verbose */
    if(argc == 3 && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--verbose")) {
        Utilities::toggle_verbose_stream(true);
    } else {
        Utilities::toggle_verbose_stream(false);
    }
    
    /* Adjust argc in case it's more than 3. */
    if(argc > 3) argc = 3;
    
    Parser parser;
    auto program = parser.parse_file(std::string(argv[argc - 1]));
    auto function_main = program->get("main");
    /* If main() exists in the code. */
    if(function_main) {
        /* run the main */
        function_main->execute();
        
        /* prints return value of the main */
        std::cout << "Program exited with value : " << function_main->get_return_value()->to_String()->get_val() << std::endl;
    }
    
    return 0;
}
