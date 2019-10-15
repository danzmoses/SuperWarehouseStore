#include "member_container.h"

MemberContainer::MemberContainer()
{
    ;
}

MemberContainer::MemberContainer(string file)
{
    ifstream inFile;
    inFile.open(file);
    Date date;
    string nameHolder;
    string idHolder;
    string member_typeHolder;
    string dateHolder;

    if(!inFile)
    {
        cout << "Error: Can't Open File.\n";
        exit(1);
    }

    while(getline(inFile, nameHolder))
    {
        getline(inFile, idHolder);
        getline(inFile, member_typeHolder);
        getline(inFile, dateHolder);
        date = Date(stoi(dateHolder.substr(0, 2)),
                    stoi(dateHolder.substr(3, 2)),
                    stoi(dateHolder.substr(6, 4)));

        members.push_back(Member(nameHolder, stoi(idHolder), member_typeHolder, date));
    }
}

void MemberContainer::view_purchases(int member_id)
{
    ;
}

void MemberContainer::view_single_member_purchases(string name)
{
    unsigned int index = 0;
    while (index < this->members.size() && this->members[index].get_name() != name)
        ++index;
    if (index == this->members.size())
    {
        cout << "ERROR: member not found" << endl;
        exit(0);
    }

    cout << "ID: " << this->members[index].get_member_id() << endl;
    cout << "Total Amount Spent: " << this->members[index].get_total_amount_spent() << endl;
}

void MemberContainer::view_all_member_purchases(string type)
{
    ;
}

void MemberContainer::view_grand_total_purchases()
{
    double total = 0;
//    this->sort_by_member_id();
    cout << "ID\tTotal Purchase Amount" << endl;
    for (unsigned int i = 0; i < this->members.size(); ++i)
    {
        cout << this->members[i].get_member_id() << "\t$" << this->members[i].get_total_amount_spent() << endl;
        total += this->members[i].get_total_amount_spent();
    }
    cout << "------------------------------------------" << endl;
    cout << "Total: $" << total << endl;

}

void MemberContainer::view_expiration_dates(int month)
{
    MemberContainer temp;
    for (unsigned int i = 0; i < this->members.size(); ++i)
        if (this->members[i].get_expiration_date().get_month() == month)
            temp.add_member(this->members[i]);
        
//    temp.sort_by_member_id();
    for (unsigned int i = 0; i < temp.members.size(); ++i)
    {
        cout << "ID: " << temp.members[i].get_member_id() << "\tExpiration Date: ";
        temp.members[i].get_expiration_date().printNumeric();
    }
}

void MemberContainer::view_membership_dues(string type)
{
    MemberContainer basic;
    MemberContainer preferred;

    for (unsigned int i = 0; i < this->members.size(); ++i)
    {
        if (this->members[i].get_type() == "Basic")
            basic.add_member(this->members[i]);
        else
            preferred.add_member(this->members[i]);
    }
//    basic.sort_by_name();
//    preferred.sort_by_name();

    if (type == "Basic" || type == "All")
        for (unsigned int i = 0; i < basic.members.size(); ++i)
            cout << "Name: " << basic.members[i].get_name() << "\tDues: " << basic.members[i].get_annual_dues() << endl;
    if (type == "Preferred" || type == "All")
        for (unsigned int i = 0; i < preferred.members.size(); ++i)
            cout << "Name: " << preferred.members[i].get_name() << "\tDues: " << preferred.members[i].get_annual_dues() << endl;

}

void MemberContainer::view_preferred_members_rebate()
{
    ;
}

string MemberContainer::sales_report(Date date)
{
    stringstream stream;    // Convert output to a string
    string answer;          // Return string
    vector<string> basic;
    vector<string> preferred;
    string dashes(90, '-');

    // This vector stored the item name, amount, and its price on a day, but seperated by members
    vector<tuple<string, int, double>> list;
    stream << left << setw(30) << "Items" << setw(30) << "Amount" << setw(30) << "Total" << endl;
    stream << dashes << endl;
    // Processing
    for (size_t i = 0; i < members.size(); i++)
    {
        SaleContainer sales = members[i].get_purchases();
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
                amount = 0;
                for (size_t k = 0; k < sales.size(); k++)
                {

                    if (sales[k].date_of_purchase == date && sales[k].item.name == itemName)
                    {
                        amount += sales[k].quantity;
                    }
                }
                tuple<string, int, double> temp(itemName, amount, sales[j].item.price);
                list.push_back(temp);
                itemCounted.push_back(itemName);
            }
        }

        if (amount > 0 && members[i].get_type() == "Basic")
            basic.push_back(members[i].get_name());
        else if (amount > 0 && members[i].get_type() == "Preferred")
            preferred.push_back(members[i].get_name());
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
            tuple<string, int, double> temp(itemName, amount, get<2>(list[i]) * amount);
            list2.push_back(temp);
            itemCounted.push_back(itemName);
        }
    }
    double final_total = 0;
    for (size_t i = 0; i < list2.size(); i++)
    {
        stream << left << setw(30) << get<0>(list2[i]) << left << setw(30) << get<1>(list2[i]) << left << setw(30) << get<2>(list2[i]) << endl;
        final_total += get<2>(list2[i]);
    }
    stream << dashes << endl;
    stream << left << setw(60) << "Final Total: " << final_total << endl << endl;
    stream << "Basic: " << endl;
    for (unsigned int i = 0; i < basic.size(); ++i)
        stream << left << setw(60) << basic[i] << endl;
    stream << endl;
    stream << "Preferred: " << endl;
    for (unsigned int i = 0; i < preferred.size(); ++i)
        stream << left << setw(60) << preferred[i] << endl;
    stream << endl;
    answer += stream.str();
    cout << answer << endl;
    return stream.str();
}

string MemberContainer::member_information(int index)
{
    stringstream ss;
    string dashes(30, '-');
    Member* m = &this->members[index];
    SaleContainer s = m->get_purchases();

    ss << left << setw(60) << "Name:" << m->get_name() << endl;
    ss << left << setw(60) << "ID:" << m->get_member_id() << endl;
    ss << left << setw(60) << "Type:" << m->get_type() << endl;
    if (m->should_convert())
        if (m->get_type() == "Basic")
            ss << "ALERT: This basic member should be converted to a preferred member!" << endl;
        else
            ss << "ALERT: This preferred member should be converted to a basic member!" << endl;
    ss << endl;
    ss << left << setw(30) << "Item" << right << setw(30) << "Price" << endl;
    ss << dashes << endl;
    for (int i = 0; i < m->get_purchases().size(); ++i)
        ss << left << setw(30) << s[i].item.name << right << setw(30) << s[i].item.price << endl;
    ss << dashes << endl;
    ss << left << setw(30) << "Total:" << right << setw(30) << m->get_total_amount_spent() << endl;

    return ss.str();
}




void MemberContainer::add_member(Member m)
{
    this->members.push_back(m);
}

void MemberContainer::remove_member(int index)
{
    this->members.erase(this->members.begin() + index);
}

void MemberContainer::inputSales(const char* file_name)
{
    ifstream inFile;
    string line;
    inFile.open(file_name);
    int id;
    string item_name;
    string price;
    string quantity;
    string month, date, year;
    while (getline(inFile, line))
    {
        month += line[0];
        month += line[1];
        date += line[3];
        date += line[4];
        year += line.substr(6);
        
        getline(inFile, line);
        id = atoi(line.c_str());

        getline(inFile, line);
        item_name = line;

        getline(inFile, line);
        int i = 0;
        for (; line[i] != ' '; i++)
        {
            price += line[i];
        }
        quantity = line.substr(i);

        Date today(atoi(month.c_str()),
                    atoi(date.c_str()),
                    atoi(year.c_str()));
        Item addendItem(item_name, atof(price.c_str()));
        for (int k = 0; k < members.size(); k++)
        {
            if (members[k].get_member_id() == id)
            {
                members[k].add_purchase(addendItem, today,
                                        atoi(quantity.c_str()));
            }
        }
        month = "";
        date = "";
        year = "";
        price = "";
        quantity = "";
    }
    inFile.close();
}
