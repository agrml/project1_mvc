//.dll 1

#include <windows.h>
#include <vector>
using namespace std;

#include "..\API\API.h"

// concrete unary plugin to perform increment
class Increment: public IUnaryPlugin
{
public:
	virtual void operation(int* object)
	{
		(*object)++;
	}
	virtual char * stringType()
	{
		return "Increment";
	}
	
};

// concrete unary plugin to perform decrement
class Decrement: public IUnaryPlugin
{
public:
	virtual void operation(int* object)
	{
		(*object)--;
	}
	virtual char * stringType()
	{
		return "Decrement";
	}
};

// concrete factory producing Increment plugins
class IncrementFactory: public IUnaryFactory
{
	vector<void*> pInstances;//IUnaryPlugin*
public:
	virtual IUnaryPlugin* Create()
	{
		IUnaryPlugin* ret = new Increment;
		pInstances.push_back((void*)ret);
		return ret;
	}
	~IncrementFactory()
	{
		for (int i=0; i<pInstances.size(); i++)
			delete pInstances[i];
	}
};

// concrete factory producing Decrement plugins
class DecrementFactory: public IUnaryFactory
{
	vector<void*> pInstances;//IUnaryPlugin*
public:
	virtual IUnaryPlugin* Create()
	{
		IUnaryPlugin* ret = new Decrement;
		pInstances.push_back((void*)ret);
		return ret;
	}
	~DecrementFactory()
	{
		for (int i=0; i<pInstances.size(); i++)
			delete pInstances[i];
	}
};

// singleton factories producing plugins
IncrementFactory Factory1;
DecrementFactory Factory2;

// dll entry point. Registers all plugins realized in the dll
extern "C" __declspec(dllexport)
	void registerPlugins(IPluginManager * pluginManager)
{
	if (pluginManager != 0)
	{
		pluginManager->RegisterUnaryPlugin(&Factory1);
		pluginManager->RegisterUnaryPlugin(&Factory2);
	}
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
    //release memory in destructor
    ;
  }
  return TRUE;
}