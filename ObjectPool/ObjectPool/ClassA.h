#pragma once

#include <iostream>
#include "BaseObject.h"

using namespace std;

class ClassA : public BaseObject<ClassA>{
public:
	ClassA() {
		cout << this << " class A" << endl;
	}

	ClassA(int a, int b) {
		cout << this <<" class A " << a << " " << b << endl;
	}

	~ClassA() {
		cout << "Delete " << this << endl;
	}
};