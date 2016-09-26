//.dll 2

#include <windows.h>
#include <forward_list>
#include "..\API\API.h"

// concrete binary plugin to perform addition
class Summator: public IBinaryPlugin
{
public:
  void operation(int* object1,const int* object2)
  {
    (*object1) = (*object1) + (*object2);
  }
  char * stringType()
  {
    return "Summator";
  }
};

// concrete binary plugin to perform subtraction
class Subtractor: public IBinaryPlugin
{
public:
  void operation(int* object1, const int* object2)
  {
    (*object1) = (*object1) - (*object2);
  }
  char * stringType()
  {
    return "Subtractor";
  }
};

// list of constructed plugins to perform memory managment
std::forward_list<IBinaryPlugin*> plugin_list;

// entry point in the dll
extern "C" __declspec(dllexport)
  IPlugin* registerPlugins(const char* type)
{
  if (strcmp(type,"summator")==0)
  {
    plugin_list.push_front(new Summator);
    return plugin_list.front();
  }
  if (strcmp(type,"subtractor")==0)
  {
    plugin_list.push_front(new Subtractor);
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