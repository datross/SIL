#ifndef VAR_FLOAT_H
#define VAR_FLOAT_H

#include "variable.h"
#include "int.h"

namespace sil {
	
class Float : public Variable {
public:
	Float();
	Float(float);
	virtual ~Float();
        
        /* cast function */
        virtual std::shared_ptr<Int> to_Int() const;
        virtual std::shared_ptr<Float> to_Float() const;
        virtual std::shared_ptr<String> to_String() const;
        
        static Float make();
	
	void operator=(const Float&);
	virtual Float * clone();
	
	/* debug */
	float get_val() { return *(float*)value; }
};

}

#endif
