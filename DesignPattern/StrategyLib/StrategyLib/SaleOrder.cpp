#include "SaleOrder.h"

double SaleOrder::calculate(double value)
{
    return m_TaxStrategy->calculate(value);
}
