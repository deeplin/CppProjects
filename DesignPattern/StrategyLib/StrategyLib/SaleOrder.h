#pragma once
#include "BaseTaxStrategy.h"
class SaleOrder
{
public:
	SaleOrder(BaseTaxStrategy * baseStrategy) : m_TaxStrategy(baseStrategy) {
	}

	~SaleOrder() {
		delete m_TaxStrategy;
	}

	double calculate(double value);

private:
	BaseTaxStrategy* m_TaxStrategy;
};

