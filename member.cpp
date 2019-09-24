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

string Member::getName()
{
    return this->name;
}

int Member::getId()
{
    return this->member_id;
}

string Member::getType()
{
    return this->type;
}

Date& Member::getExpiration_date()
{
    return this->expiration_date;
}

double Member::getTotal()
{
    return this->total_amount_spent;
}

double Member::getRebate()
{
    return this->rebate;
}

SaleContainer& Member::get_purchases()
{
    return this->purchases;
}

double Member::getAnnual_dues()
{
    return this->annual_dues;
}

void Member::add_purchase(Item i, Date d)
{
    this->purchases.add_sale(Sale(i, d));
}

void Member::update_expiration_date(Date d)
{
    this->expiration_date = d;
}