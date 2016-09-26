//abstract plugin
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

class IBinaryPlugin: public IPlugin
{
public:
  // applies binary operation and returns result to the first parameter
	virtual void operation(int* object1, const int* object2) = 0;
};

// abstract factory
template<typename Interface> class IFactory 
{
public:
	virtual Interface* Create() = 0;
};

// abstract factory to create unary and binary plugins
typedef IFactory<IUnaryPlugin> IUnaryFactory;
typedef IFactory<IBinaryPlugin> IBinaryFactory;

// abstract plugin manager
class IPluginManager 
{
public:
  // registers plugins
	virtual void RegisterUnaryPlugin(IUnaryFactory* factory) = 0;
	virtual void RegisterBinaryPlugin(IBinaryFactory* factory) = 0;
};



// type of an entry point
typedef void (*regFuncType)(IPluginManager *);