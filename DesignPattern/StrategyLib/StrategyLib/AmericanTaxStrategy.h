#pragma once
#include "BaseTaxStrategy.h"
class AmericanTaxStrategy :
    public BaseTaxStrategy
{
public:
    double calculate(double);
};

