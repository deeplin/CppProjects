#pragma once
#include <iostream>
#include "Command.h"
using namespace std;
class AnalogCommand
	:public Command
{
public:
	virtual void execute() override{
		cout << "Analog" << endl;
	}
};

