#pragma once
#include "Implementation.h"
class RedImplementation :
    public Implementation
{
    virtual string operation() const override {
        return "red ";
    }
};

