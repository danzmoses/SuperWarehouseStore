#include "member.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <algorithm>

#ifndef MEMBER_CONTAINER_H
#define MEMBER_CONTAINER_H

class MemberContainer
{
    private:
        vector<Member> members;

    public:

        MemberContainer();
        MemberContainer(string file);


        Member& operator[](int index) { return this->members[index]; }
        int size() { return this->members.size(); }

        void view_purchases(int member_id);
        void view_single_member_purchases(string name);
        void view_all_member_purchases(string type = "All");
        void view_grand_total_purchases();
        void view_expiration_dates(int month);
        void view_membership_dues(string type = "All");
        void view_preferred_members_rebate();

        string sales_report(Date date);
        string member_information(int index);
        string expiration_dates_report(int month);

        void add_member(Member m);
        void remove_member(int index);
        void sort_by_member_id();
        void sort_by_name();
};

#endif /* MEMBER_CONTAINER_H */
