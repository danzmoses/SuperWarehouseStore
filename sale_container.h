#include "sale.h"
#include <vector>

#ifndef SALE_CONTAINER
#define SALE_CONTAINER

class SaleContainer
{
    private:
        vector<Sale> sales;

    public:
        SaleContainer();

        void sales_report(Date d);

        void add_sale(Sale s);
};

#endif /* SALE_CONTAINER */