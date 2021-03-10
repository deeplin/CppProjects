// TestMyAql.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AsyncMySql.h"
#include "AsyncLog.h"

int main()
{
	AsyncMySql mysql;
	mysql.Init();

	//AsyncLog::GetInstance().SetLogPath("AsyncMySqlDebug.txt", "w");
	//AsyncLog::Info("test async debug2");


	mysql.Close();
    std::cout << "Hello World!\n";
	getchar();
}