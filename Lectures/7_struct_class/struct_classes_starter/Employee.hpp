#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <string>
#include "Date.hpp"

class Employee
{
private: // set the attributes of a class, private
  std::string name;
  int hourly_paid;
  Date start_date;

public: // define our public functions of a class, API
  Employee();
  Employee(std::string n, int h_rate, Date d_day);
  Employee(std::string n, int h_rate);

  std::string get_name() const; // think of this as a prototype
  int get_hourly_rate() const;  // think of this as a prototype
  Date get_start_date() const;

  bool set_name(std::string n);
  bool set_hourly_rate(int h_rate);
  bool set_start_date(Date sd);

  static const double minimum_wage;
};

#endif