#pragma once
#include "State.h"

using namespace std;

class OpenState:public State
{
private:
public:
	static State* m_Instance;
	static State* getInstance() {
		if (m_Instance == nullptr) {
			m_Instance = new OpenState();
		}
		return m_Instance;
	}

	virtual void operation1() override;

	virtual void operation2() override;
};

