#ifndef VAR_INT_H
#define VAR_INT_H

#include "variable.h"

namespace sil {
	
class Int : public Variable {
public:
	Int();
	Int(int);
	virtual ~Int();
	
	void operator=(const Int&);
	virtual Int * clone();
	
	/* debug */
	int get_val() { return *(int*)value; }
};

}

#endif
