#ifndef _DATE_H
#define _DATE_H
#include <string>

enum MONTH {JAN=1,FEB, MAR, APR, MAY, JUN};


class Date
{
private:
  int year;
  MONTH month;
  int day;

public: 
  Date();
  Date(int y, MONTH m, int d);                        
  int get_year() const;
  MONTH get_month() const;
  int get_day() const;
  
  bool set_year(int y);
  bool set_month(MONTH m);
  bool set_day(int d);
  
  bool operator==(const Date &another_date);//getter function
  bool operator<(Date another_date);

  static const int minimum_year;
};

#endif