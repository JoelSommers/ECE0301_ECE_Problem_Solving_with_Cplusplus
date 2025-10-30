#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Employee.hpp"
#include "Date.hpp"

TEST_CASE("Class test setters and getters", "[employee-class]")
{
  Employee new_hire;
  REQUIRE(new_hire.get_name() == "");
  REQUIRE(new_hire.get_hourly_rate() == 0);

  new_hire.set_name("Spiderman");
  new_hire.set_hourly_rate(20);

  REQUIRE(new_hire.get_name() == "Spiderman");
  REQUIRE(new_hire.get_hourly_rate() == 20);

  Employee second_hire("Tim", 15);
  REQUIRE(second_hire.get_name() == "Tim");
  REQUIRE(second_hire.get_hourly_rate() == 15);

  Date random_date;
  random_date.set_year(2025);
  REQUIRE(random_date.get_year() == 2025);
}

TEST_CASE("Class test setters and getters", "[employee-class]")
{
  Employee new_hire;
  REQUIRE(new_hire.get_name() == "");
  REQUIRE(new_hire.get_hourly_rate() == 0);

  Date example(2025, MAY, 1);
  Employee hire2("Tom", 30, example);
  REQUIRE(hire2.get_name() == "Tom");
  REQUIRE(hire2.get_hourly_rate() == 30);
  REQUIRE(hire2.get_start_date().get_day() == 1);
  REQUIRE(hire2.get_start_date().get_month() == MAY);
  REQUIRE(hire2.get_start_date().get_year() == 2025);

  REQUIRE(hire2.get_start_date() == example);
  REQUIRE(hire2.get_start_date().operator==(example));

  Employee hire3("Tom", 30);
  REQUIRE(hire3.get_name() == "Tom");
  REQUIRE(hire3.get_hourly_rate() == 30);
  REQUIRE(hire3.get_start_date().get_day() == 1);
  REQUIRE(hire3.get_start_date().get_month() == JAN);
  REQUIRE(hire3.get_start_date().get_year() == 2000);

  REQUIRE(hire3.get_start_date().minimum_year == 1900);
  REQUIRE(hire3.minimum_wage == 7.5);

  REQUIRE_THROWS_AS(Date example2(1700, MAY, 1), std::invalid_argument);
}