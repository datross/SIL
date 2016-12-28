#ifndef VAR_INT_H
#define VAR_INT_H

#include "variable.h"
#include "float.h"
#include "string.h"

namespace sil {
	
class Int : public Variable {
public:
	Int();
	Int(int);
	virtual ~Int();
        
        /* cast function */
        virtual std::shared_ptr<Int> to_Int() const;
        virtual std::shared_ptr<Float> to_Float() const;
        virtual std::shared_ptr<String> to_String() const;
        
        static Int make();
	
	void operator=(const Int&);
	virtual Int * clone();
	
	/* debug */
	int get_val() { return *(int*)value; }
};

}

#endif
