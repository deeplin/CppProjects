#pragma once

#include <iostream>
#include "ClassA.h"
#include "ObjectPool.h"

using namespace std;

int main(int argc, char** argv) {

	ClassA * c = new ClassA;
	delete c;

	ClassA* a = ClassA::NewObj();
	ClassA::DeleteObject(a);

	ClassA* b = ClassA::NewObj(200, 300);


	ClassA::DeleteObject(b);

	cout << "hello" << endl;
	return 0;
}