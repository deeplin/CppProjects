#pragma once
#include "State.h"

using namespace std;
class CloseState :
    public State
{
private:
	static State* m_Instance;
public:
	static State* getInstance() {
		if (m_Instance == nullptr) {
			m_Instance = new CloseState();
		}
		return m_Instance;
	}

	virtual void operation1() override {
		//pNext = ConnectionState::getInstance();
	}

	virtual void operation2() override {
		//pNext = OpenState::getInstance();
	}
};