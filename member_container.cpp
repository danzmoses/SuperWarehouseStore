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

string MemberContainer::sales_report(const Date& date)
{
    stringstream stream;    // Convert output to a string
    string answer;          // Return string
    int basic = 0;          // Count for every basic member
    int preferred = 0;      // Count for every preferred member

    // This vector stored the item name, amount, and its price on a day, but seperated by members
    vector<tuple<string, int, double>> list;
    stream << left << setw(15) << "Items" << setw(15) << "Amount"
           << setw(15) << "Total" << endl;
    answer += stream.str();
    // Processing
    for (size_t i = 0; i < members.size(); i++)
    {
        vector<Sale> sales = members[i].get_purchases().getSales();
        int amount = 0;
        string itemName;
        vector<string> itemCounted;
        for (size_t j = 0; j < sales.size(); j++)
        {
            itemName = sales[j].item.name;
            // To avoid from repeating counting, if the item name has been counted, then
            // we do nothing, else we count the amount of it, and store name to another vector
            // that store counted name
            if (find(itemCounted.begin(), itemCounted.end(), itemName) == itemCounted.end())  //If not found, that means a item has not been counted yet.
            {
                // This loop check the date and item name and count the amount
                // And the reason is that one member may buy a same thing twice on the different day of 
                for (size_t k = 0; k < sales.size(); k++)
                {
                    if (sales[k].date_of_purchase == date && sales[k].item.name == itemName)
                    {
                        amount+=sales[k].quantity;
                    }
                }
                list.push_back({itemName, amount, sales[j].item.price});
                itemCounted.push_back(itemName);
            }
        }
        if (amount > 0 && members[i].getType() == "Basic")
        {
            basic++;
        }
        else if (amount > 0 && members[i].getType() == "Preferred")
        {
            preferred++;
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
    double final_total = 0;
    for (size_t i = 0; i < list2.size(); i++)
    {
        stream << left << setw(15) << get<0>(list2[i]) << setw(15) << get<1>(list2[i]) 
           << setw(15) << get<2>(list2[i])  << endl;
        answer += stream.str(); 
        final_total += get<2>(list2[i]);
    }
    stream << left << setw(30) << "Final Total: " << final_total << endl;
    answer += stream.str();
    stream << left << setw(30) << "Basic: " << basic << endl;
    answer += stream.str();
    stream << left << setw(30) << "Preferred: " << preferred << endl;
    answer += stream.str();
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