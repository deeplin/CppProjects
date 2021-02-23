// BridgeLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Implementation.h"
#include "BlueImplementation.h"
#include "RedImplementation.h"
#include "RoundAbstraction.h"

int main()
{
	Implementation* blueImplementation = new BlueImplementation();
	Implementation* redImplementation = new RedImplementation();

	Abstraction* abstraction = new Abstraction(blueImplementation);
	Abstraction* abstraction2 = new RoundAbstraction(blueImplementation);
	Abstraction* abstraction3 = new RoundAbstraction(redImplementation);

	cout << abstraction->operation() << endl;
	cout << abstraction2->operation() << endl;
	cout << abstraction3->operation() << endl;

	delete abstraction3;
	delete abstraction2;
	delete abstraction;
	delete blueImplementation;
}