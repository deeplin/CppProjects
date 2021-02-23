#pragma once
class State
{
public:
	State* pNext;
	virtual void operation1() = 0;
	virtual void operation2() = 0;
	virtual ~State() {}
};