#ifndef _CIRCUITS_HPP
#define _CIRCUITS_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath> //for calculations

void log_invalid_input()
{
    std::cout << "Invalid input format." << std::endl;
}

double get_value(std::string expr_string)
{
    // find where the equals is in string
    int equals_index = expr_string.find("=");

    // error check to see if there is an equal sign
    if (equals_index == std::string::npos)
    {
        return -1;
    }

    // error check to see if there are multiple equal signs
    std::string check = expr_string.substr(equals_index + 1, expr_string.length());
    int check_equal = check.find("=");

    if (check_equal != std::string::npos)
    {
        return -1;
    }

    // create substring for number
    std::string num_element = expr_string.substr(equals_index + 2, expr_string.length());

    // try catch to convert string to double (error-checking built in)

    double value;
    try
    {
        value = std::stod(num_element);
    }
    catch (std::invalid_argument)
    {
        return -1;
    }

    return value;
}

double get_current(double resistance, double power)
{
    // test for negative input values
    if (resistance < 0 || power < 0)
    {
        return -1;
    }
    // calculate missing current
    double cur = std::sqrt(power / resistance);
    return cur;
}

double get_resistance(double current, double power)
{
    // test for negative input values
    if (current < 0 || power < 0)
    {
        return -1;
    }
    // calculate missing resistance
    double res = power / std::pow(current, 2);
    return res;
}

double get_power(double current, double resistance)
{
    // test for negative input values
    if (resistance < 0 || current < 0)
    {
        return -1;
    }
    // calculate missing power
    double power = std::pow(current, 2) * resistance;
    return power;
}

double get_power(float current, double resistance)
{
    if (resistance < 0)
    {
        return -1;
    }
    double power=std::pow(current, 2)*resistance;
    return power;
}

double get_divider_power(double source_power, double resistance1, double resistance2)
{
    if (source_power < 0 || resistance1 < 0 || resistance2 < 0)
    {
        return -1;
    }
    double power = source_power * (resistance2 / (resistance1 + resistance2));
    return power;
}


#endif