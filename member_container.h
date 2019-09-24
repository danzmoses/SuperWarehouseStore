#include "member.h"
#include "date.h"
#include "item_container.h"
#include <vector>
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

        void view_purchases(int member_id);
        void view_purchases(string name);
        void view_all_purchases(string type = "All");
        void view_expiration_dates(int month);
        void view_membership_dues(string type = "All");
        void view_preferred_members_rebate();
        string sales_report(const Date& date);
        void add_member();
        void remove_member();
};

#endif /* MEMBER_CONTAINER_H */