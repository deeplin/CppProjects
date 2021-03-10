// TestMyAql.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AsyncMySql.h"

int main()
{
	AsyncMySql mysql;
	mysql.Init();

    std::cout << "Hello World!\n";
	getchar();
}