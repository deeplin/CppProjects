// TestMySql.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AsyncMysql.h"

using namespace std;

int main()
{
    AsyncMysql mysql;
    mysql.Init();
    std::cout << "Hello World!\n";
}