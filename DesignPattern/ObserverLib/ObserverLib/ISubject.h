#pragma once
#include "IObserver.h"

template <typename T>
class ISubject
{
public:
	virtual void Attach(IObserver<T>*) = 0;
	virtual void Detach(IObserver<T>*) = 0;
};

