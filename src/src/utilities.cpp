#include "utilities.h"

std::ostream Utilities::dummy(0);
std::ostream * Utilities::logging_stream_ptr = &std::cout; 