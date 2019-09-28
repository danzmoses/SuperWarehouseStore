#include "sale_container.h"
#include <iostream>
SaleContainer::SaleContainer()
{
    ;
}

void SaleContainer::add_sale(Sale s)
{
    this->sales.push_back(s);
}
