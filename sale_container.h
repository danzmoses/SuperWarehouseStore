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

        Sale operator[](int index) { return this->sales[index]; }
        int size() { return this->sales.size(); }
        void add_sale(Sale s);
};

#endif /* SALE_CONTAINER */
