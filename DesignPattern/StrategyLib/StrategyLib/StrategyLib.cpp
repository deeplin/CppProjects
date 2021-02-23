// StrategyLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BaseTaxStrategy.h"
#include "ChinaTaxStrategy.h"
#include "AmericanTaxStrategy.h"
#include "SaleOrder.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    BaseTaxStrategy* taxStrategy = new ChinaTaxStrategy();
    SaleOrder saleOrder(taxStrategy);

    BaseTaxStrategy* taxStrategy2 = new AmericanTaxStrategy();
    SaleOrder saleOrder2(taxStrategy2);

    cout << saleOrder.calculate(100) << endl;
    cout << saleOrder2.calculate(100) << endl;
}