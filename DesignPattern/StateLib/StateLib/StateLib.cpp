// StateLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OpenState.h"
#include "CloseState.h"
#include "ConnectionState.h"

int main()
{
    std::cout << "Hello World!\n";

    State* state = OpenState::getInstance();
    state->operation1();

    State* state3 = new CloseState();
    state3->operation1();

    State* state2 = new ConnectionState();
    state2->operation1();

    cout << OpenState::m_Instance << endl;
}

