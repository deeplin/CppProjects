#pragma once
#include "Implementation.h"
class BlueImplementation : public Implementation
{
	virtual string operation() const override{
		return "blue ";
	}
};
