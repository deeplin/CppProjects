#include "OpenState.h"
#include "ConnectionState.h"
#include "CloseState.h"
#include "State.h"

State* OpenState::m_Instance = nullptr;

void OpenState::operation1()
{
	ConnectionState* state = new ConnectionState();
	ConnectionState::m_Instance;

}

void OpenState::operation2()
{
	//pNext = CloseState::getInstance();
}