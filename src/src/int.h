#ifndef VAR_INT_H
#define VAR_INT_H

#include "variable.h"

namespace sil {
	
class Int : public Variable {
public:
	Int();
	Int(int);
	Int(const Variable&);
	virtual ~Int();
};

#endif
