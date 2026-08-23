#pragma once

#define CREATE_COMPONENT(TYPE)														\
Eclipse::Component* Create_##TYPE(unsigned char* address) {	\
	return new(address)TYPE();		\
}


#define COMPONENT_ENTRY(TYPE) { #TYPE, typeid(TYPE).name(), &Create_##TYPE, sizeof(TYPE) },

namespace Eclipse
{
	class Component;
}

struct ComponentEntry final
{
	const char* name;
	const char* rttiType;
	Eclipse::Component* (__cdecl* createFunc)(unsigned char* address);
	size_t size;
};

struct ComponentRegistrySnapshot final
{
	ComponentEntry* components = nullptr;
	int count = 0;
};

namespace Eclipse::Utilities
{
	class MainSingleton;
}

#ifndef _NO_EXPORT
extern "C"
{
	__declspec(dllexport) ComponentRegistrySnapshot __cdecl RegisterComponents();
#else
	ComponentRegistrySnapshot RegisterComponents();
#endif

#ifndef _NO_EXPORT
}
#endif