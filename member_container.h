#include "member.h"
#include <vector>

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

        void add_member();
        void remove_member();
};

#endif /* MEMBER_CONTAINER_H */