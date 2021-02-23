#pragma once
#include <string>
using namespace std;
class Implementation
{
public:
	virtual ~Implementation() {}
	virtual string operation() const = 0;
};

