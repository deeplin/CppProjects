#pragma once
#include <iostream>
using namespace std;
class Singleton
{
private:
	Singleton() {}
	Singleton(const Singleton&){}
	static Singleton* m_Instance;
public:
	static Singleton* getInstance() {
		if (m_Instance == nullptr) {
			if (m_Instance == nullptr) {
				m_Instance = new Singleton();
			}
		}
		return m_Instance;
	};
	void fun() {
		cout << "singleton" << endl;
	}
	~Singleton() {
		delete m_Instance;
	}
};