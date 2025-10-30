// This is circle_area_starter.cpp
// Try cmake . && make && ./circle_area_starter in terminal
// But from now on, use CMake side bar to automate the process

#include <iostream> // due to the usage of cout below
#include <cmath>
#include <iomanip>

int main()
{
    char answer='y';
    while (answer =='y'||answer=='Y'){
    int radius;
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;

    if (!std::cin.good()){
        std::cout<<"Invalid input!"<<std::endl;
        return EXIT_FAILURE;
    }
    if (radius < 0)
    {
        std::cout << "the radius must be positive!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "the area is: ";
    std::cout <<std::fixed <<std::setprecision(5);
    std::cout << M_PI * pow(radius, 2) << std::endl;

    std::cout<<"Do you want to calculate another area? (y/n): ";
    std::cin>>answer;
}
}