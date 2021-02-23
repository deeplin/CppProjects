// HelloMemory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <thread>
#include "Allocate.h"
#include "MemoryBlock.h"
#include "TimeStamp.h"

using namespace std;

#define MAX 1000000
#define NUMBER_COUNT MAX/THREAD_COUNT
#define THREAD_COUNT 10

void DoWork() {
	char* data[NUMBER_COUNT];
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		//int rand = std::rand() % 1024;
		data[i] = new char[i % 128 + 1];
	}

	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		delete[] data[i];
	}
}

int main()
{
	TimeStamp timeStamp;

	thread t[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		t[i] = thread(DoWork);
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		t[i].join();
	}

	cout << "TIME: " << timeStamp.GetElapsedTimeInMilliSec() << endl;

    std::cout << "Hello World!\n";
}
