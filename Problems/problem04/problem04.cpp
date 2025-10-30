#include <cstdlib>
#include <iostream>
#include <fstream> //library to read or write to a file
#include <string>  //string library
#include <iomanip> //needed for precisions
#include <cmath>   //for calculations
#include "circuits.hpp"

int main(int argc, char *argv[])
{
    // set default files
    std::string input_file = "../tests/test_input.txt";
    std::string output_file = "../tests/my_test_output.txt";

    // test CLI
    if (argc == 2)
    {
        input_file = argv[1];
    }

    else if (argc == 3)
    {
        input_file = argv[1];
        output_file = argv[2];
    }

    // create and open file objects
    std::ifstream infile(input_file);
    std::ofstream outfile(output_file);

    // check if file exists
    if (infile.fail())
    {
        std::cout << "Input file error" << std::endl;
        infile.close();
        return EXIT_FAILURE;
    }
    else if (outfile.fail())
    {
        std::cout << "Output file error" << std::endl;
        outfile.close();
        return EXIT_FAILURE;
    }

    // comma index
    int comma_index;

    std::string line;

    while (getline(infile, line))
    {
        // find where the comma is and error check
        comma_index = line.find(",");
        if (comma_index == std::string::npos)
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        // create two substrings to hold the two values of each line
        std::string element1 = line.substr(0, comma_index);
        std::string element2 = line.substr(comma_index + 2, std::string::npos);

        // report error if there is another comma in the second substring
        if (element2.find(",") != std::string::npos)
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }
        // declare variables for values in substrings and call function to get the value
        double value1 = get_value(element1);
        double value2 = get_value(element2);

        // check if value1=-1 and value2=-1
        if (value1 == -1)
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        if (value2 == -1)
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        // define boolean flags to determine which element is missing
        bool missingRes = false, missingCur = false, missingPow = false;

        // code to determine which is missing from each line and toggle that flag
        char value_name1 = element1[0];
        char value_name2 = element2[0];

        // error check to find if there are repeated values
        if (value_name1 == value_name2)
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        // error check to find if a value name is invalid
        if (value_name1 != 'I' && value_name1 != 'R' && value_name1 != 'P')
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }
        if (value_name2 != 'I' && value_name2 != 'R' && value_name2 != 'P')
        {
            log_invalid_input();
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        if (value_name1 != 'I' && value_name2 != 'I')
        {
            missingCur = true;
        }

        if (value_name1 != 'R' && value_name2 != 'R')
        {
            missingRes = true;
        }

        if (value_name1 != 'P' && value_name2 != 'P')
        {
            missingPow = true;
        }

        double cur, res, power;
        if (missingRes)
        {
            if (value_name1 == 'I')
            {
                cur = value1;
                power = value2;

                // calculate missing resistance using function
                res = get_resistance(cur, power);

                // print output to outfile
                // apply precision
                outfile << std::fixed << std::setprecision(3) << "If I = " << cur << " Amps and P = " << power << " Watts, then R = " << res << " Ohms." << std::endl;
            }
            else
            {
                cur = value2;
                power = value1;
                res = get_resistance(cur, power);
                outfile << std::fixed << std::setprecision(3) << "If P = " << power << " Watts and I = " << cur << " Amps, then R = " << res << " Ohms." << std::endl;
            }
        }
        else if (missingCur)
        {
            if (value_name1 == 'R')
            {
                res = value1;
                power = value2;

                // calculate missing current using function
                cur = get_current(res,power);

                // print output to outfile
                // apply precision
                outfile << std::fixed << std::setprecision(3) << "If R = " << res << " Ohms and P = " << power << " Watts, then I = " << cur << " Amps." << std::endl;
            }
            else
            {
                res = value2;
                power = value1;
                cur = get_current(res, power);
                outfile << std::fixed << std::setprecision(3) << "If P = " << power << " Watts and R = " << res << " Ohms, then I = " << cur << " Amps." << std::endl;
            }
        }
        else if (missingPow)
        {
            if (value_name1 == 'I')
            {
                cur = value1;
                res = value2;

                // calculate missing power using function
                power = get_power(cur,res);

                // print output to outfile
                // apply precision
                outfile << std::fixed << std::setprecision(3) << "If I = " << cur << " Amps and R = " << res << " Ohms, then P = " << power << " Watts." << std::endl;
            }
            else
            {
                cur = value2;
                res = value1;
                power = get_power(cur, res);
                outfile << std::fixed << std::setprecision(3) << "If R = " << res << " Ohms and I = " << cur << " Amps, then P = " << power << " Watts." << std::endl;
            }
        }
    }

    infile.close();
    outfile.close();

    return EXIT_SUCCESS;
}