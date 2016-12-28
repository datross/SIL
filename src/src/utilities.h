#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <sstream>

/* Gathering of general useful functions. */
class Utilities {
private:
    Utilities(){}
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
};

#endif