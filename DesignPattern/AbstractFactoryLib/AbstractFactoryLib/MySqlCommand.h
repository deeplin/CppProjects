#pragma once
#include "ICommand.h"
class MySqlCommand :
    public ICommand
{
public:
    virtual string operation() override {
        return "mysql command";
    }
};

