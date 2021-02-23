#pragma once
#include "IConnection.h"
class MySqlConnection :
    public IConnection
{
public:
    virtual string operation() override {
        return "mysql connection";
    }
};

