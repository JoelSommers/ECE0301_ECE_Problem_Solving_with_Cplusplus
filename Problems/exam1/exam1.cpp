#define CATCH_CONFIG_MAIN

#include <cstdlib>  //EXIT_SUCCESS
#include <iostream> //cout cin and endl
#include <iomanip>  //precision
#include <fstream>  //files
#include <string>   //strings
#include <cmath>    //math
using namespace std;

// Uncomment this part if doing catch test
#include "catch.hpp"
#include "exam1.hpp"
TEST_CASE("Your Exam 1 test cases", "[exam1]")
{
    int size = 5;
    int arr[size] = {5, 4, 7, 8, 1};
    arrfunc(arr, size);
    arrfunc(arr, size);

    // content of arr? and size?
    for (int i=0;i<5;i++){
        std::cout<<arr[i]<<std::endl;
    }
    std::cout<<"size = "<<size<<std::endl;
}
// Uncomment this part if doing regular coding
// int main(){
//     cout << "Good luck!" << endl;
//     return 0;
// }