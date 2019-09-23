#include <string>

struct Item
{
    std::string name;
    double price;
    Item(std::string n = "", double p = 0) {name = n; price = p;}
};