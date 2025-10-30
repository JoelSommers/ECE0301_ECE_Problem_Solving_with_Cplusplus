#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <cmath>

#include "circuits.hpp"

TEST_CASE("Test Current", "[Circuits]")
{
    double resistance = 1000;
    double power = 2.5000;
    double current=get_current(resistance, power);
    REQUIRE(current == sqrt(power / resistance));
}

TEST_CASE("Test Current 2", "[Circuits]")
{
    double resistance = 2000;
    double power = 5;
    REQUIRE(get_current(resistance, power) == sqrt(power / resistance));
}

TEST_CASE("Test Current 3", "[Circuits]")
{
    double resistance = -2000;
    double power = 5;
    REQUIRE(get_current(resistance, power) == -1);

    resistance = 2000;
    power = -5;
    REQUIRE(get_current(resistance, power) == -1);
}

TEST_CASE("Test Resistance", "[Circuits]")
{
    double current = 0.05;
    double power = 2.5000;
    REQUIRE(get_resistance(current, power) == power / pow(current, 2));
}

TEST_CASE("Test Resistance 2", "[Circuits]")
{
    double current = 1;
    double power = 5;
    REQUIRE(get_resistance(current, power) == power / pow(current, 2));
}

TEST_CASE("Test Resistance 3", "[Circuits]")
{
    double current = -1;
    double power = 5;
    REQUIRE(get_resistance(current, power) == -1);

    current = 1;
    power = -5;
    REQUIRE(get_resistance(current, power) == -1);
}

TEST_CASE("Test Power Overload", "[Circuits]"){
    double current = 0.05;
    double resistance = 1000;
    double power = get_power(current, resistance);
    REQUIRE(power == pow(current, 2) * resistance);

    float current2 = 0.5;
    double resistance2 = 1000;
    double power2 = get_power(current2, resistance2);
    REQUIRE(power2 == pow(current2, 2) * resistance2);

    float current3 = -0.5;
    double resistance3 = 1000;
    double power3 = get_power(current3, resistance3);
    REQUIRE(power3 == pow(current3, 2) * resistance3);

    float current4 = -0.5;
    double resistance4 = -1;
    double power4 = get_power(current4, resistance4);
    REQUIRE(power4 == -1);
}

TEST_CASE("Test Power", "[Circuits]")
{
    double current = 0.05;
    double resistance = 1000;
    REQUIRE(get_power(current, resistance) == pow(current, 2) * resistance);
}

TEST_CASE("Test Power 2", "[Circuits]")
{
    double current = 1;
    double resistance = 2000;
    REQUIRE(get_power(current, resistance) == pow(current, 2) * resistance);
}

TEST_CASE("Test Power 3", "[Circuits]")
{
    double current = -1;
    double resistance = 2000;
    REQUIRE(get_power(current, resistance) == -1);

    current = 1;
    resistance = -2000;
    REQUIRE(get_power(current, resistance) == -1);
}

TEST_CASE("Test getValue Parsing", "[Circuits]")
{
    std::string test_string = "R = 1000.0";
    REQUIRE(get_value(test_string) == 1000.0);
}

TEST_CASE("Test getValue Parsing 2", "[Circuits]")
{
    std::string test_string = "R == 5";
    REQUIRE(get_value(test_string) == -1);
}

TEST_CASE("Test getValue Parsing 3", "[Circuits]")
{
    std::string test_string = "R 5";
    REQUIRE(get_value(test_string) == -1);
}

TEST_CASE("Test divider power","[Circuits]")
{
    double resistance1=100;
    double resistance2=200;
    double source_power=50;
    double power=source_power*(resistance2/(resistance1+resistance2));
    double threshold = 1e-3;
    REQUIRE(std::abs(power-get_divider_power(source_power,resistance1,resistance2))<=threshold);
}

TEST_CASE("Test divider power 2", "[Circuits]")
{
    double resistance1 = -100;
    double resistance2 = 200;
    double source_power = 50;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == -1);

    resistance1 = 100;
    resistance2 = -200;
    source_power = 50;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == -1);

    resistance1 = 100;
    resistance2 = 200;
    source_power = -50;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == -1);
}
