#pragma once
using namespace std;

unordered_map <string, function<void(void*)>> tableBaseVirtualMethods;
unordered_map <string, function<void(void*)>> tableDerivedVirtualMethods;

#define BaseBody(Class)                                                                   \
	Class() {                                                                             \
		virtualTablePointer = &tableBaseVirtualMethods;                                                        \
	}                                                                                     \
	unordered_map <string, function<void(void*)>> *virtualTablePointer;                   \

#define DerivedBody(Class)                                                                \
	Class() {                                                                             \
		virtualTablePointer = &tableDerivedVirtualMethods;                                                     \
	}                                                                                     \

#define BaseEnd(Class) string baseClass = #Class;


#define VirtualCall(Class, Func)                                                          \
(*((Class)->virtualTablePointer->find(#Func))).second((void*)(Class));


#define FuncDef(Class, Func, ...) {                                                       \
	auto thisFunc = [](void* classPointer) {                                              \
		Class *self = reinterpret_cast<Class*>(classPointer); __VA_ARGS__                 \
	}                                                                                     \

#define FuncWorkFlow(Class, Func, ...)                                                    \
	if (baseClass != #Class) \
		tableDerivedVirtualMethods[#Func] = thisFunc;                                     \
	else if (tableDerivedVirtualMethods.find(#Func) == tableDerivedVirtualMethods.end()) {\
		tableBaseVirtualMethods[#Func] = thisFunc;                                        \
		tableDerivedVirtualMethods[#Func] = thisFunc;                                     \
	}                                                                                     \
	else tableBaseVirtualMethods[#Func] = thisFunc;                                       \
} 
