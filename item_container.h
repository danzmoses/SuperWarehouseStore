#include "item.h"
#include <vector>
using namespace std;

class ItemContainer
{
    private:
        vector<Item> items;

    public:
        ItemContainer();
        void add_item(Item i);
};