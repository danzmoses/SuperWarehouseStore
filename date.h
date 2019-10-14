#include <string>
#include <sstream>
using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
    private:
        unsigned day;       // IN/OUT: day of the month
        unsigned month;     // IN/OUT: month of the year
        string monthName;   // IN/OUT: month as a string
        unsigned year;      // IN/OUT: year

    public:
    /******************************** 
    ********* CONSTRUCTORS *********
    ********************************/

        Date();
        Date(unsigned m, unsigned d, unsigned y);
        Date(const string &mn, unsigned d, unsigned y);

    /***************
     ** ACCESSORS **
     ***************/
        void printNumeric() const;
        void printAlpha() const;
        Date addDays(int days) const;
        unsigned get_day() { return this->day; }
        unsigned get_month() { return this->month; }
        unsigned get_year() { return this->year; }
        bool operator==(const Date& other);
        string returnNumeric() const;
        string returnAlpha() const;

    private:
    /***************
     ** ACCESSORS **
     ***************/    
        bool isLeap(unsigned) const;
        unsigned daysPerMonth(unsigned m, unsigned y) const;
        string name(unsigned m) const;
        unsigned number(const string &mn) const;
};
/***************************************************************** 
 * Date Class
 * 
 * This class represents a date. The attributes are the day, month,
 *  and year as integers, and the name of the month as a string.
 ****************************************************************/

/******************************** 
 ** CONSTRUCTORS               **
 ********************************/

/***************************************************************** 
 * Date ();
 * Constructor; Default constructor; set to January 1, 2000
 * Parameters: none
 * Return: none
 ****************************************************************/

/***************************************************************** 
 * Date ( unsigned m, unsigned d, unsigned y );
 * Constructor; Initialize date with the given month as integer
 * Parameters: none
 * Return: none
 ****************************************************************/

/***************************************************************** 
 * Date ( const string &mn, unsigned d, unsigned y );
 * Constructor; Initialize date with the given month as a string
 * Parameters: none
 * Return: none
 ****************************************************************/

/***************
 ** ACCESSORS **
 ***************/

/****************************************************************
 * void printNumeric() const;
 * 
 *   Accessor (Public); This method will print the numeric date
 *                       (i.e --> 1/1/2000)
 * --------------------------------------------------------------
 *   Parameters: None
 * --------------------------------------------------------------
 *   Return: None; prints numeric date
 ***************************************************************/

/****************************************************************
 * void printAlpha() const;
 * 
 *   Accessor (Public); This method will print the alphabetic date
 *                       (i.e --> January 1, 2000)
 * --------------------------------------------------------------
 *   Parameters: None
 * --------------------------------------------------------------
 *   Return: None; prints alphabetical date
 ***************************************************************/

/****************************************************************
 * void isLeap( unsigned ) const;
 * 
 *   Accessor (Private); This method will determine whether or not 
 *                        a given year is a leap year              
 * --------------------------------------------------------------
 *   Parameters: y (unsigned int)   // IN: year to check
 * --------------------------------------------------------------
 *   Return: true/false (bool)
 ***************************************************************/

/****************************************************************
 * unsigned daysPerMonth( unsigned m, unsigned y ) const;
 * 
 *   Accessor (Private); This method will determine how many days
 *                        are in the given month/year            
 * --------------------------------------------------------------
 *   Parameters: m (unsigned int)   // IN: month to check
 *               y (unsigned int)   // IN: year (matters if leap year)
 * --------------------------------------------------------------
 *   Return: days in the month (unsigned int)
 ***************************************************************/

/****************************************************************
 * string name( unsigned m ) const;
 * 
 *   Mutator (Private); This method converts an integer month to
 *                       its string equivalent name
 * *                     (i.e 1 -> "January")
 * --------------------------------------------------------------
 *   Parameters: m (unsigned int)   // IN: month to convert
 * --------------------------------------------------------------
 *   Return: month name as a string
 ***************************************************************/

/****************************************************************
 * unsigned number( const string &mn ) const;
 * 
 *   Mutator (Private); This method converts a string month to
 *                       its integer equivalent 
 *                       (i.e "March" -> 3)
 * --------------------------------------------------------------
 *   Parameters: m (unsigned int)   // IN: month to convert
 * --------------------------------------------------------------
 *   Return: month as an integer
 ***************************************************************/
#endif /* DATE_H */
