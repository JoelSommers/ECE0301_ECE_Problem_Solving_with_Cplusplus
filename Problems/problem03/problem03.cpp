#include <cstdlib>
#include <iostream>
#include <fstream> //library to read or write to a file
#include <string>  //string library
#include <iomanip> //needed for precisions
#include <cmath>   //for calculations

int main(int argc, char *argv[])
{
    // set default files
    std::string input_file = "../test_input.txt";
    std::string output_file = "../output.txt";

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
            std::cout << "Invalid input format." << std::endl;
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
            std::cout << "Invalid input format." << std::endl;
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }
        // declare variables for values in substrings
        double first_value;
        double second_value;

        // find where the equals is in both elements
        int equals_index1 = element1.find("=");
        int equals_index2 = element2.find("=");

        // error check to see if there is an equal sign
        if (equals_index1 == std::string::npos)
        {
            std::cout << "Invalid input format." << std::endl;
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        if (equals_index2 == std::string::npos)
        {
            std::cout << "Invalid input format." << std::endl;
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }
        // create substrings for numbers
        std::string num_element1 = element1.substr(equals_index1 + 2, element1.length());
        std::string num_element2 = element2.substr(equals_index2 + 2, element2.length());

        // try catch to convert string to double (error-checking built in)
        double value1;
        double value2;

        try
        {
            value1 = std::stod(num_element1);
        }
        catch (std::invalid_argument)
        {
            std::cout << "Invalid input format." << std::endl;
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        try
        {
            value2 = std::stod(num_element2);
        }
        catch (std::invalid_argument)
        {
            std::cout << "Invalid input format." << std::endl;
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
            std::cout << "Invalid input format." << std::endl;
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }

        // error check to find if a value name is invalid
        if (value_name1 != 'I' && value_name1 != 'R' && value_name1 != 'P')
        {
            std::cout << "Invalid input format." << std::endl;
            infile.close();
            outfile.close();
            return EXIT_FAILURE;
        }
        if (value_name2 != 'I' && value_name2 != 'R' && value_name2 != 'P')
        {
            std::cout << "Invalid input format." << std::endl;
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

                // calculate missing resistance
                res = power / std::pow(cur, 2);

                // print output to outfile
                // apply precision
                outfile << std::fixed << std::setprecision(3) << "If I = " << cur << " Amps and P = " << power << " Watts, then R = " << res << " Ohms." << std::endl;
            }
            else
            {
                cur = value2;
                power = value1;
                res = power / std::pow(cur, 2);
                outfile << std::fixed << std::setprecision(3) << "If P = " << power << " Watts and I = " << cur << " Amps, then R = " << res << " Ohms." << std::endl;
            }
        }
        else if (missingCur)
        {
            if (value_name1 == 'R')
            {
                res = value1;
                power = value2;

                // calculate missing current
                cur = std::sqrt(power / res);

                // print output to outfile
                // apply precision
                outfile << std::fixed << std::setprecision(3) << "If R = " << res << " Ohms and P = " << power << " Watts, then I = " << cur << " Amps." << std::endl;
            }
            else
            {
                res = value2;
                power = value1;
                cur = std::sqrt(power / res);
                outfile << std::fixed << std::setprecision(3) << "If P = " << power << " Watts and R = " << res << " Ohms, then I = " << cur << " Amps." << std::endl;
            }
        }
        else if (missingPow)
        {
            if (value_name1 == 'I')
            {
                cur = value1;
                res = value2;

                // calculate missing power
                power = std::pow(cur, 2) * res;

                // print output to outfile
                // apply precision
                outfile << std::fixed << std::setprecision(3) << "If I = " << cur << " Amps and R = " << res << " Ohms, then P = " << power << " Watts." << std::endl;
            }
            else
            {
                cur = value2;
                res = value1;
                power = std::pow(cur, 2) * res;
                outfile << std::fixed << std::setprecision(3) << "If R = " << res << " Ohms and I = " << cur << " Amps, then P = " << power << " Watts." << std::endl;
            }
        }
    }

    infile.close();
    outfile.close();

    return EXIT_SUCCESS;
}