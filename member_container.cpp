#include "member_container.h"

MemberContainer::MemberContainer()
{
    ;
}

void MemberContainer::view_purchases(int member_id)
{
    ;
}

void MemberContainer::view_purchases(string name)
{
    ;
}

void MemberContainer::view_all_purchases(string type = "All")\
{
    ;
}

void MemberContainer::view_expiration_dates(int month)
{
    ;
}

void MemberContainer::view_membership_dues(string type = "All")
{
    ;
}

void MemberContainer::view_preferred_members_rebate()
{
    ;
}

string MemberContainer::sales_report(const ItemContainer& items,
                                     const Date& date)
{
    stringstream stream;    // Convert output to an string
    string answer;          // Returning

    // This vector stored the item name, amount, and its price, but sperated by members
    vector<tuple<string, int, double>> list;
    stream << right << setw(15) << "Items" << setw(15) << "Amount"
           << setw(15) << "Total" << endl;
    answer += stream.str();
    for (size_t i = 0; i < this->members.size(); i++)
    {
        vector<Sale> sales = members[i].get_purchases().getSales;
        int amount = 0;
        string itemName;
        vector<string> itemCounted;
        for (size_t j = 0; j < sales.size(); j++)
        {
            itemName = sales[j].item.name;
            // To avoid from repeating counting, if the item name has been counted, then
            // we do nothing, else we count the amount of it, and store name to another vector
            // that store counted name
            if (find(itemCounted.begin(), itemCounted.end(), itemName) == itemCounted.end())  //If not found
            {
                itemName = sales[j].item.name;
                // This loop check the date and item name and count the amount
                for (size_t k = 0; k < sales.size(); k++)
                {
                    if (sales[k].date_of_purchase == date && sales[k].item.name == itemName)
                    {
                        amount++;
                    }
                }
                list.push_back({itemName, amount, sales[j].item.price});
                itemCounted.push_back(itemName);
            }
        }
    }
    vector<tuple<string, int, double>> list2;   // This vector is a general vector, item name, amount and total
    vector<string> itemCounted;
    // Push back a general list vector
    for (size_t i = 0; i < list.size(); i++)
    {
        string itemName = get<0>(list[i]);
        int amount = 0;
        if (find(itemCounted.begin(), itemCounted.end(), itemName) == itemCounted.end())
        {
            for (size_t j = 0; j < list.size(); j++)
            {
                if(itemName == get<0>(list[j]))
                {
                    amount+= get<1>(list[j]);
                }
            }
            list2.push_back({itemName, amount, get<2>(list[i]) * amount});
            itemCounted.push_back(itemName);
        }
    }
    for (size_t i = 0; i < list2.size(); i++)
    {
        stream << right << setw(15) << get<0>(list[i]) << setw(15) << get<1>(list[i]) 
           << setw(15) << get<2>(list[i])  << endl;
        answer += stream.str(); 
    }
    return answer;
}

void MemberContainer::add_member()
{
    ;
}

void MemberContainer::remove_member()
{
    ;
}