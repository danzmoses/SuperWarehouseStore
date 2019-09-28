#include <string>

#ifndef ITEM_H
#define ITEM_H

struct Item
{
    std::string name;
    double price;
    Item(std::string n = "", double p = 0) {name = n; price = p;}
};

#endif // ITEM_H
