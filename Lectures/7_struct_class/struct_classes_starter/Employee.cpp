#include "Employee.hpp"

static const double minimum_wage = 7.5;

Employee::Employee() : name(""), hourly_paid(0)
{
}

Employee::Employee(std::string n, int h_rate, Date s_day)
{
  name = n;
  hourly_paid = h_rate;
  start_date = s_day;
}

Employee::Employee(std::string n, int h_rate)
{
  name = n;
  hourly_paid = h_rate;
  Date default_d(2000, JAN, 1);
  start_date = default_d;
}

std::string Employee::get_name() const
{
  return name;
}

int Employee::get_hourly_rate() const
{
  return hourly_paid;
}

Date Employee::get_start_date() const
{
  return start_date;
}

bool Employee::set_name(std::string n)
{
  name = n;
  return true;
}

bool Employee::set_hourly_rate(int h_rate)
{
  hourly_paid = h_rate;
  return true;
}

bool Employee::set_start_date(Date sd)
{
  start_date = sd;
  // int day1 = sd.get_day();
  // int month1 = sd.get_month();
  // int year1 = sd.get_year();
  // start_date(year1, month1, day1);
  return true;
}
