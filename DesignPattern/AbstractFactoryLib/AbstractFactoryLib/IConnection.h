#pragma once
#include <string>
using namespace std;
class IConnection
{
public:
	virtual string operation() = 0;
};

