#pragma once
#include "State.h"

using namespace std;
class ConnectionState : public State
{
public:
	static State* m_Instance;
	static State* getInstance() {
		//if (m_Instance == nullptr) {
		//	m_Instance = new ConnectionState();
		//}
		//return m_Instance;
		return m_Instance;
	}

	virtual void operation1() override {
		//pNext = OpenState::getInstance();
	}

	virtual void operation2() override {
		//pNext = CloseState::getInstance();
	}
};