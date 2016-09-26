//.dll 2

#include <windows.h>
#include <vector>
using namespace std;

#include "..\API\API.h"

// concrete binary plugin to perform addition
class Summator: public IBinaryPlugin
{
public:
	virtual void operation(int* object1,const int* object2)
	{
		(*object1) = (*object1) + (*object2);
	}
	virtual char * stringType()
	{
		return "Summator";
	}
	
};

// concrete binary plugin to perform subtraction
class Subtractor: public IBinaryPlugin
{
public:
	virtual void operation(int* object1, const int* object2)
	{
		(*object1) = (*object1) - (*object2);
	}
	virtual char * stringType()
	{
		return "Subtractor";
	}
};

// concrete factory producing Summator plugins
class SummatorFactory: public IBinaryFactory
{
	vector<void*> pInstances;//IUnaryPlugin*
public:
	virtual IBinaryPlugin* Create()
	{
		IBinaryPlugin* ret = new Summator;
		pInstances.push_back((void*)ret);
		return ret;
	}
	~SummatorFactory()
	{
		for (int i=0; i<pInstances.size(); i++)
			delete pInstances[i];
	}
};

// concrete factory producing Subtractor plugins
class SubtractorFactory: public IBinaryFactory
{
	vector<void*> pInstances;//IUnaryPlugin*
public:
	virtual IBinaryPlugin* Create()
	{
		IBinaryPlugin* ret = new Subtractor;
		pInstances.push_back((void*)ret);
		return ret;
	}
	~SubtractorFactory()
	{
		for (int i=0; i<pInstances.size(); i++)
			delete pInstances[i];
	}
};

// singleton factories producing plugins
SummatorFactory Factory1;
SubtractorFactory Factory2;

// dll entry point. Registers all plugins realized in the dll
extern "C" __declspec(dllexport)
	void registerPlugins(IPluginManager * pluginManager)
{
	if (pluginManager != 0)
	{
		pluginManager->RegisterBinaryPlugin(&Factory1);
		pluginManager->RegisterBinaryPlugin(&Factory2);
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