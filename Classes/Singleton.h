#ifndef SINGLETON_H_
#define SINGLETON_H_

#define Singleton(Class)                    \
	public: static Class &getSingleton()    \
    {                                       \
		static Class *single = nullptr;     \
		if(single == nullptr)               \
			single = new Class();           \
		return *single;                     \
    }                                       \
	public: ~Class();                       \
	protected: Class();                     \
    Class& operator=(const Class& rhs)      \
    {                                       \
        return getSingleton();              \
    }                                       \
    Class(Class& c) {}
#endif