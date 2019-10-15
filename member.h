#ifndef MEMBER_H
#define MEMBER_H

#include "sale_container.h"
#include "date.h"
#include <iostream>
using namespace std;


class Member
{
    private:
        string name;
        int member_id;
        string type;
        Date expiration_date;

        SaleContainer purchases;
        double total_amount_spent;
        double rebate;
        double annual_dues;
        

    public:
        Member(string n, int id, string member_type, Date d);
        void add_purchase(Item i, Date d, int quantity);
        void update_expiration_date(Date d);

        // getters
        string get_name() { return this->name; }
        int get_member_id() { return this->member_id; }
        string get_type() { return this->type; }
        Date get_expiration_date() { return this->expiration_date; }

        SaleContainer get_purchases();
        double get_total_amount_spent();
        double get_annual_dues() { return this->annual_dues; }

        bool should_convert();
        double calculate_rebate();

};

#endif /* MEMBER_H */
