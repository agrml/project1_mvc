//.dll 1

#include <windows.h>
#include <forward_list>
#include "..\API\API.h"

// concrete unary plugin to perform increment
class Increment: public IUnaryPlugin
{
public:
	void operation(int* object)
	{
		(*object)++;
	}
	char * stringType()
	{
		return "Increment";
	}
	
};

// concrete unary plugin to perform decrement
class Decrement: public IUnaryPlugin
{
public:
	void operation(int* object)
	{
		(*object)--;
	}
	char * stringType()
	{
		return "Decrement";
	}
};

// list of constructed plugins to perform memory managment
std::forward_list<IUnaryPlugin*> plugin_list;

// entry point in the dll
extern "C" __declspec(dllexport)
	IPlugin* registerPlugins(const char* type)
{
	if (strcmp(type,"increment")==0)
	{
		plugin_list.push_front(new Increment);
    return plugin_list.front();
	}
	if (strcmp(type,"decrement")==0)
	{
		plugin_list.push_front(new Decrement);
		return plugin_list.front();
	}
	return NULL;
}

// function that called then dll is attached and detached.
// Allows performing pre- and post processing.
BOOL APIENTRY DllMain( HANDLE hModule,   
                       DWORD ul_reason_for_call,   
                       LPVOID lpReserved    
                     ) 
{
  switch( ul_reason_for_call ) {
  case DLL_PROCESS_ATTACH:
  case DLL_THREAD_ATTACH:
    //do nothing
    break;
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    //release memory
    for (auto it = plugin_list.begin(); it != plugin_list.end(); it++)
      delete *it;
    plugin_list.clear();
  }
  return TRUE;
}