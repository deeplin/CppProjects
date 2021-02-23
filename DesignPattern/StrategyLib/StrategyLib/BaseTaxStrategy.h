#pragma once
class BaseTaxStrategy
{
public:
	BaseTaxStrategy() {
	}
	virtual ~BaseTaxStrategy() {}
	virtual double calculate(double) = 0;
};

