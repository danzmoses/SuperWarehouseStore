#include "item.h"
#include <vector>
#include <fstream>
using namespace std;

class ItemContainer
{
    private:
        vector<Item> items;

    public:
        ItemContainer();
        ItemContainer(string file);

        Item operator[](int index) { return this->items[index]; }
        int size() { return this->items.size(); }

        void clear() { this->items.clear(); }
        void add_item(Item i);
};
