#include "Date.hpp"
#include <stdexcept>

static const int minimum_year = 1900;

Date::Date()
{
  year = 1900;
  month = JAN;
  day = 1;
}

Date::Date(int y, MONTH m, int d)
{
  set_year(y);
  month = JAN;
  day = d;
}

int Date::get_year() const
{
  return year;
}

MONTH Date::get_month() const
{
  return month;
}

int Date::get_day() const
{
  return day;
}

bool Date::set_year(int y)
{
  if (y<minimum_year){
    throw std::invalid_argument("Invalid year");
  }
  year = y;
  return true;
}

bool Date::set_month(MONTH m)
{
  month = m;
  return true;
}

bool Date::set_day(int d)
{
  day = d;
  return true;
}

bool Date::operator==(const Date &another_date)
{
  if (another_date.day == day && another_date.month == month && another_date.year == year)
  {
    return true;
  }

  return false;
}

bool Date::operator<(Date another_date)
{
  return false;
}
