// HelloMemory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Allocate.h"
#include "MemoryBlock.h"
#include <random>

using namespace std;

#define MAX 1100
int main()
{
	char* data[MAX];
	for (size_t i = 0; i < MAX; i++)
	{
		cout << ":" << i << " ";
		//int rand = std::rand() % 1024;
		data[i] = new char[i];
	}

	for (size_t i = 0; i < MAX; i++)
	{
		delete[] data[i];
	}

	cout << sizeof(MemoryBlock) << endl;

    std::cout << "Hello World!\n";
}
