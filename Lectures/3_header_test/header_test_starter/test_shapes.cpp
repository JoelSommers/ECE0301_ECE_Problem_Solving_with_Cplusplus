#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "shapes.hpp"

TEST_CASE("Test my conversion")
{
  REQUIRE(conversion("a = 3.15") == 3.15);
  REQUIRE(conversion("t = 412") == 412);
  REQUIRE(conversion("t + 412") == -1);
  REQUIRE(conversion("t = xyz") == -1);
}

TEST_CASE("Test my overloaded functions")
{
  double a = 1.0;
  double threshold = 1e-3;
  double result = 3.14159 * 1.0 * 1.0;
  REQUIRE(std::abs(result - area(a)) <= threshold);
  double w = 3, l = 6;
  REQUIRE(area(w, l) == 18.0);
  a = 3.0;
  double b = 4.0, sinC = 0.5;
  REQUIRE(area(a, b, sinC) == 3.0);
  a = 3.0;
  b = 4.0;
  float c = 5.0;
  REQUIRE(area(a, b, c) == 6.0);

  a = 301;
  b = 1;
  REQUIRE(sum(a, b) == 302);
  std::cout << "a outside the function is " << a << std::endl;
  
  int x =301;
  int y=1;
  REQUIRE(sum2(x, y) == 302);
  std::cout << "a outside the function is " << a << std::endl;
}

TEST_CASE("Test functions with default arguements"){
  double a =1.0;
  REQUIRE(area(a)==M_PI);

  double w=3, l=6;
  REQUIRE(area(w,l)==18.0);

  REQUIRE(area_with_default(w)==30.0);

}