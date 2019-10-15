#include "item.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class ItemContainer
{
    private:
        vector<Item> items;

    public:
        ItemContainer();
        ItemContainer(string file);

        Item operator[](int index) const { return this->items[index]; }
        int size() const { return this->items.size(); }

        void clear() { this->items.clear(); }
        void add_item(Item i);

        void load(string file)
        {
            ifstream in_file;

            in_file.open(file);
            if (!in_file)
            {
                cout << "ERROR: file could not open" << endl;
                exit(1);
            }

            string item_name;
            string item_price;
            while (getline(in_file, item_name))
            {
                if(item_name != "")
                {
                    getline(in_file, item_price);
                    this->add_item(Item(item_name, stod(item_price)));
                }
            }
        }

};
