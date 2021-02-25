// HelloMemory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <thread>
#include <Memory>
#include "Allocate.h"
#include "MemoryBlock.h"
#include "TimeStamp.h"

using namespace std;

#define MAX 200
#define NUMBER_COUNT MAX/THREAD_COUNT
#define THREAD_COUNT 30

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

using namespace std;

class TT {
public:
	~TT() {
		cout << "DT" << endl;
	}
	int num;
	TT() {
		cout << "CT" << endl;
	}
	void Print() {
		cout << "P" << endl;
	}
};

void fun(shared_ptr<TT>& a) {
	a->Print();
}

int main()
{
	TimeStamp timeStamp;

	//thread t[THREAD_COUNT];
	//for (int i = 0; i < THREAD_COUNT; i++) {
	//	t[i] = thread(DoWork);
	//}

	//for (int i = 0; i < THREAD_COUNT; i++) {
	//	t[i].join();
	//}

	//TT * a = new TT;
	//delete a;
	shared_ptr<TT> b = make_shared<TT>();
	fun(b);

	cout << sizeof(b) << " TIME: " << timeStamp.GetElapsedTimeInMilliSec() << endl;

    std::cout << "Hello World!\n";
}
