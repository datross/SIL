#ifndef VAR_FLOAT_H
#define VAR_FLOAT_H

#include "variable.h"

namespace sil {
	
class Float : public Variable {
public:
	Float();
	Float(float);
	virtual ~Float();
	
	void operator=(const Float&);
	
	/* debug */
	float get_val() { return *(float*)value; }
};

}

#endif
