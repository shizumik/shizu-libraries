#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton
{
public:
	static Singleton* Instance();
protected:
	Singleton() {}
private:
	static Singleton* _instance;
};

Singleton* Singleton::_instance = 0;

Singleton* Singleton::Instance()
{
	if (_instance == 0)    // what is called lazy initialize
		_instance = new Singleton;
	return _instance;
}

//more flexible -> registry of singleton

class SingletonReg
{
public: 
	static void Register(const char* name, SingletonReg*);
	static SingletonReg* Instance();
protected:
	static SingletonReg* Lookup(const char* name);
private:
	static SingletonReg* _instance;
	static List<NameSingletonPair>* _registry;
};

#endif // !SINGLETON_H
