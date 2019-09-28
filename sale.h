#include "item.h"
#include "date.h"

struct Sale
{
    Item item;
    Date date_of_purchase;
    int quantity = 0;
    Sale(Item i, Date d, int q) {item = i; date_of_purchase = d, quantity = q; }
};
