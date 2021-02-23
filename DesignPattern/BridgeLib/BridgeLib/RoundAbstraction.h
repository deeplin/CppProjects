#pragma once
#include "Abstraction.h"
class RoundAbstraction :
    public Abstraction
{
public:
    RoundAbstraction(Implementation* implementation) : Abstraction(implementation) {
    }

    virtual string operation() const override {
        return "round " + m_Implementation->operation();
    }
};

