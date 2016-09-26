//main application


#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "..\API\API.h"

class PluginManager: public IPluginManager
{
	vector <IUnaryPlugin*> unPlugins;//IUnaryPlugin*
  vector <IBinaryPlugin*> binPlugins;//IBinaryPlugin*
public:
  /************************************
   * setters. Inherited from superclass
   ************************************/
  // registers unary plugins
	virtual void RegisterUnaryPlugin(IUnaryFactory* factory)
	{
		IUnaryPlugin* plugin = factory->Create();
		if (plugin)
			unPlugins.push_back(plugin);
	}

  // registers binary plugins in the manages
	virtual void RegisterBinaryPlugin(IBinaryFactory* factory) 
	{
		IBinaryPlugin* plugin = factory->Create();
		if (plugin)
			binPlugins.push_back(plugin);
	}

  /************************************
   * Getters
   ************************************/
  vector<IUnaryPlugin*> &GetUnaryPlugins()
  {
    return unPlugins;
  }

  vector<IBinaryPlugin*> &GetBinaryPlugins()
  {
    return binPlugins;
  }
};
			  
// singleton plugin manager
PluginManager manager;

int findDLLs(const char *in_pluginsDir, vector<string> &out_file_names)
{
  char *buffer = new char [strlen(in_pluginsDir) + 1000];

  HANDLE hFind = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATA ffd;
  strcpy(buffer,in_pluginsDir);
  buffer = strcat(buffer,"\\*.dll");
  hFind = FindFirstFile(buffer, &ffd);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    // List all the files in the directory with some info about them.
    do
    {
      cout << ffd.cFileName << endl;
      out_file_names.push_back(ffd.cFileName);
    }
    while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);
    hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
      cerr << "Unexpected error while reading files" << endl;
      exit(dwError);
    }
  }
  else
  {
    cerr << "no files in directory" << endl;
    delete [] buffer;
    return -1;
  }
  delete [] buffer;
  return out_file_names.size();
}

int LoadDLLs(const char *in_pluginsDir, const vector<string> &in_file_names,
  HMODULE *out_pLib, vector<string> &out_lib_names)
{
  auto files_num = in_file_names.size();
  char *buffer = new char[strlen(in_pluginsDir) + 1000];
  int k=0;
	for (size_t i=0; i<files_num; i++)
	{
		strcpy(buffer,in_pluginsDir);
		buffer = strcat(buffer, "\\");
		buffer = strcat(buffer, in_file_names[i].c_str());
		
		out_pLib[k] = LoadLibrary(buffer);
		if (out_pLib[k] != NULL)
		{
			out_lib_names.push_back(buffer);
			k++;
		}
		else
		{
			DWORD dwerr = GetLastError();
			cerr << dwerr << endl;
		}
	}
  delete [] buffer;
  return k;
}

void LoadPlugins(HMODULE *in_pLib, const vector<string> &in_pLibNames)
{
  auto fLength = in_pLibNames.size();
	for (int i=0; i<fLength; i++)//free libraries
	{
		regFuncType function = (regFuncType) GetProcAddress(in_pLib[i],"registerPlugins");
		if (function == NULL)
			cout << "Library " << in_pLibNames[i] << " is not a plugin" << endl;
		else
		{
			cout << "Library " << in_pLibNames[i] << " is a plugin" << endl;
			//try to Register
			function(&manager);
		}
	}
}

void UserUnaryOperation(vector<IUnaryPlugin*> &plugList)
{
	if (plugList.size() > 0)
	{
		cout << "Choose unary plugins" << endl;
		for (int i=0; i<plugList.size(); i++)
			cout << '[' << i << ']' <<  (plugList[i])->stringType() << endl;

		int pluginIndex = -1;
		while (pluginIndex>=plugList.size()|| pluginIndex < 0)
		{
			cin >> pluginIndex;
			if (pluginIndex>=plugList.size()|| pluginIndex < 0)
			{
				cerr << "Invalid input: out of range " << "0-" << plugList.size() << endl;
			}
		}
		cout << "Input value: " << endl;
		int a;
		cin >> a;
		((IUnaryPlugin*)plugList[pluginIndex])->operation(&a);
		cout << "Answer is " << a << endl;
	}

}

void UserBinaryOperation(vector<IBinaryPlugin*> &plugList)
{
	if (plugList.size() > 0)
	{
		cout << "Choose binary plugins" << endl;
		for (int i=0; i<plugList.size(); i++)
			cout << '[' << i << ']' <<  (plugList[i])->stringType() << endl;

		int pluginIndex = -1;
		while (pluginIndex>=plugList.size()|| pluginIndex < 0)
		{
			cin >> pluginIndex;
			if (pluginIndex>=plugList.size()|| pluginIndex < 0)
			{
				cerr << "Invalid input: out of range " << "0-" << plugList.size() << endl;
			}
		}
		cout << "Input values: " << endl;
		int a,b;
		cin >> a >> b;
		((IBinaryPlugin*)plugList[pluginIndex])->operation(&a,&b);
		cout << "Answer is " << a << endl;
	}
	
}

int main(int argc, char*argv[]){

	char pluginsDir[] = "plugins";
	char *tmpStr = new char [strlen(pluginsDir) + 1000];
	
	cout << "File name is:\t" << pluginsDir << endl;

	vector<string> files;
	vector<string> pLibNames;

  // find all dlls in a folder specified by the pluginDir
  int fLength = findDLLs(pluginsDir, files);
	cout << fLength << " .dll files was found in dir " << pluginsDir <<endl;

	// array of dll handles
	HMODULE *pLib = new HMODULE [fLength];
  fLength = LoadDLLs(pluginsDir, files, pLib, pLibNames);
  LoadPlugins(pLib, pLibNames);

  UserUnaryOperation(manager.GetUnaryPlugins());
	UserBinaryOperation(manager.GetBinaryPlugins());
	

	for (int i=0; i<fLength; i++)//free libraries
	{
		BOOL success = FreeLibrary(pLib[i]);
		if (!success)
			cerr << "FreeLibrary error";
	}
	delete[] pLib;
	delete[] tmpStr;
}
