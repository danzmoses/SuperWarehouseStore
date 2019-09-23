#include "item.h"
#include "date.h"

struct Sale
{
    Item item;
    Date date_of_purchase;
    Sale(Item i, Date d) {item = i; date_of_purchase = d;}
};