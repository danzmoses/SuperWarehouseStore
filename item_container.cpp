#include "item_container.h"
#include <iostream>

ItemContainer::ItemContainer()
{
    ;
}

ItemContainer::ItemContainer(string file)
{
    ifstream in_file;
    in_file.open(file);
    if (!in_file)
    {
        cout << "ERROR: file not opened" << endl;
        exit(1);
    }

    string item_name;
    string item_price;
    while (getline(in_file, item_name))
    {
        getline(in_file, item_price);
        this->add_item(Item(item_name, stod(item_price)));
    }
}

void ItemContainer::add_item(Item i)
{
    this->items.push_back(i);
}
