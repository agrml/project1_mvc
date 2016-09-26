// abstract plugin
class IPlugin
{
public:
  // returns string name of the plugin
	virtual char* stringType() = 0;
};

// abstract plugin to apply unary operation
class IUnaryPlugin: public IPlugin
{
public:
  // applies unary operation and returns result to the first parameter
	virtual void operation(int* object) = 0;
};

// abstract plugin to apply binary operation
class IBinaryPlugin: public IPlugin
{
public:
  // applies binary operation and returns result to the first parameter
	virtual void operation(int* object1, const int* object2) = 0;
};

// type of a function that searches plugins in the dll
typedef IPlugin* (*regFuncType)(const char*);