#pragma once

#include <iostream>
#include "ClassA.h"
#include "ObjectPool.h"
#include "TimeStamp.h"
using namespace std;

#define MAX 12
#define THREAD_COUNT 1
#define NUMBER_COUNT MAX/THREAD_COUNT

void DoWork() {
	ClassA* data[NUMBER_COUNT];
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		data[i] = new ClassA();
	}

	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		delete data[i];
	}
}

int main(int argc, char** argv) {

	TimeStamp timeStamp;

	thread t[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		t[i] = thread(DoWork);
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		t[i].join();
	}

	cout << sizeof(ClassA) << " hello" << endl;
	return 0;
}