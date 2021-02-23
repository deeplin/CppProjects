#pragma once
#include "IReader.h"
class MySqlReader :
    public IReader
{
public:
    virtual string operation() override {
        return "mysql reader";
    }
};

