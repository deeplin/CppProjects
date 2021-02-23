#pragma once
#include <iostream>
#include "Command.h"
using namespace std;
class StatusCommand :
    public Command
{
public:
    virtual void execute() override {
        cout << "Status" << endl;
    }
};

