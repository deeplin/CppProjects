#pragma once
#include <iostream>

using namespace std;
class Stream
{
public:
	virtual ~Stream() {}
	virtual string operation() = 0;
};

