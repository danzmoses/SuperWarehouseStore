#include "sale_container.h"
#include "date.h"
#include <iostream>

using namespace std;

#ifndef MEMBER_H
#define MEMBER_H

class Member
{
    private:
        // initialized members
        string name;
        int member_id;
        string type;
        Date expiration_date;

        double total_amount_spent;
        double rebate;
        SaleContainer purchases;
        double annual_dues;

    public:
        Member(string n, int id, string member_type, Date d);
        string getName();
        int getId();
        string getType();
        Date& getExpiration_date();
        double getTotal();
        double getRebate();
        SaleContainer& get_purchases();
        double getAnnual_dues();
        void add_purchase(Item i, Date d);
        void update_expiration_date(Date d);

};

#endif /* MEMBER_H */