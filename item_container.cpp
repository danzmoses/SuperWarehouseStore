#include "item_container.h"

ItemContainer::ItemContainer()
{
    ;
}

void ItemContainer::add_item(Item i)
{
    this->items.push_back(i);
}