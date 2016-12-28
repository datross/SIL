#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <sstream>
#include <ostream>
#include <iostream>

/* Gathering of general useful functions. */
class Utilities {
private:
    Utilities();
    
    static std::ostream dummy;
public:
    /* works with stringstream, so one type must be a string. */
    template<class dst, class src>
    static dst convert(src s) {
        std::stringstream ss;
        ss << s;
        dst d;
        ss >> d;
        return d;
    }
    
    /* stream to work with */
    static std::ostream * logging_stream_ptr;
    
    /* obvious */
    static void toggle_verbose_stream(bool verbose) {
        if(verbose) logging_stream_ptr = &std::cout;
        else logging_stream_ptr = &dummy;    
    }
};

/* alias to use to prints log info. */
#define log_stream *Utilities::logging_stream_ptr

#endif