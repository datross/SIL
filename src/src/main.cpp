#include <iostream>

#include "variables.h"

using namespace std;

class A {
public:
	virtual void print(){ cout << "A" << endl; }
};
class B1 : public A {
public:
	void print(){ cout << "B1" << endl; }
};
class B2 : public A {
public:
	void print(){ cout << "B2" << endl; }
};

void print(A& a){
	A * p = &a;
	p->print();
	//a.print();
}

int main(int argc, char * argv[])
{
	B1 b;
	print(b);
    return 0;
}