#include <iostream>
#include <string>
#include <functional>
#include <exception>
#include <unordered_map>
#include <utility>
#include "header.h"

using namespace std;

struct Base {
	int a = 0; //
	BaseBody(Base)
};
BaseEnd(Base)

struct Derived : public Base {
	int b = 1; //
	DerivedBody(Derived)
};
			
int main() {
    Base base;
	Derived derived;
	Base* reallyDerived = reinterpret_cast<Base*>(&derived);

	FuncDef(Base, Both, cout << "Base::Both a = " << self->a << endl;);
	FuncWorkFlow(Base, Both, cout << "Base::Both a = " << self->a << endl;)

	FuncDef(Base, OnlyBase, cout << "Base::OnlyBase" << endl;);
	FuncWorkFlow(Base, OnlyBase, cout << "Base::OnlyBase" << endl;)

	FuncDef(Derived, Both, cout << "Derived::Both b = " << self->b << endl;);
	FuncWorkFlow(Derived, Both, cout << "Derived::Both b = " << self->b << endl;)

	FuncDef(Derived, OnlyDerived, cout << "Derived::OnlyDerived" << endl;);
	FuncWorkFlow(Derived, OnlyDerived, cout << "Derived::OnlyDerived" << endl;)

	try {
		VirtualCall(&base, Both);
		VirtualCall(&base, OnlyBase);

		VirtualCall(&*reallyDerived, Both);
		VirtualCall(&*reallyDerived, OnlyBase);

		VirtualCall(&derived, Both);
		VirtualCall(&derived, OnlyBase);
		VirtualCall(&derived, OnlyDerived);
	}
	catch (const exception& exc) {
		cout << exc.what();
	}

	system("pause");
	return 0;
}
