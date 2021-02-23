// SingletonLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Singleton.h"
int main()
{
	Singleton* singletone = Singleton::getInstance();
	singletone->fun();
}