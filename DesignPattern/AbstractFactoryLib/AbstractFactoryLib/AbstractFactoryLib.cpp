// AbstractFactoryLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "IDBFactory.h"
#include "MySqlFactory.h"

int main()
{
	IDBFactory* factory = new MySqlFactory();
	cout << factory->createCommand()->operation() << endl;
	cout << factory->createConnection()->operation() << endl;
	cout << factory->createReader()->operation() << endl;
}