#include "member.h"

Member::Member(string n, int id, string member_type, Date d)
{
    this->name = n;
    this->member_id = id;
    this->type = member_type;
    this->expiration_date = d;

    this->total_amount_spent = 0;
    this->rebate = 0;

    if (this->type == "Basic")
        this->annual_dues = 60;
    else if (this->type == "Preferred")
        this->annual_dues = 75;
}

void Member::calc_rebate()
{
    double total = 0;
    for (int i = 0; i < purchases.size(); i++)
    {
        // Here I'm calc rebate for all even though basic members have no rebate
        // but i need the rebate in the  is_convert() function
        total += purchases[i].item.price * purchases[i].quantity;
    }

    rebate = total * 0.05;
}

bool Member::is_convert()
{
    if (rebate >= 75 && type == "basic")
    {
        return true;  // A basic member needs to convert to preferred
    }
    else if (rebate < 75 && type == "preferred")
    {
        return true;  // A preferred member needs to convert to preferred
    }
    else
    {
        return false;
    }
}

SaleContainer Member::get_purchases()
{
    return this->purchases;
}


void Member::add_purchase(Item i, Date d, int quantity)
{
    this->purchases.add_sale(Sale(i, d, quantity));
}

void Member::update_expiration_date(Date d)
{
    this->expiration_date = d;
}

double Member::get_total_amount_spent()
{
    double total = 0;
    for (unsigned int i = 0; i < this->purchases.size(); ++i)
        total += this->purchases[i].item.price;
    return total;
}
