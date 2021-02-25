#pragma once

#include <iostream>
#include "ClassA.h"
using namespace std;

int main(int argc, char** argv) {

	ClassA* a = ClassA::NewObj();


	ClassA* b = ClassA::NewObj(200, 300);

	ClassA::DeleteObject(a);
	ClassA::DeleteObject(b);

	cout << "hello" << endl;
	return 0;
}