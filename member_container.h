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
    public:
        vector<Member> members;

    public:

        MemberContainer();
        MemberContainer(string file);


        Member& operator[](int index) { return this->members[index]; }
        int size() { return this->members.size(); }
        bool empty() { return this->members.empty(); }

        void view_purchases(int member_id);
        void view_single_member_purchases(string name);
        void view_all_member_purchases(string type = "All");
        void view_grand_total_purchases();
        void view_expiration_dates(int month);
        void view_membership_dues(string type = "All");
        void view_preferred_members_rebate();

        string sales_report(Date date);
        string member_information(int index);

        void add_member(Member m);
        void remove_member(int index);
        void sort_by_member_id();
        void sort_by_name();

        void load(string file)
        {
            ifstream inFile;
            Date date;
            string nameHolder;
            string idHolder;
            string member_typeHolder;
            string dateHolder;

            inFile.open(file);

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

};

#endif /* MEMBER_CONTAINER_H */
