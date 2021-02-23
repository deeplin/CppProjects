#pragma once
#include "Implementation.h"
class Abstraction
{
protected:
	Implementation* m_Implementation;
public:
	Abstraction(Implementation* implementation) : m_Implementation(implementation) {
	}
	virtual ~Abstraction(){}

	virtual string operation() const{
		return "abstraction " + m_Implementation->operation();
	}
};

