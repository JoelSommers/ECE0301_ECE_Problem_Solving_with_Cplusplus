#ifndef _EXAM1_HPP
#define _EXAM1_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

/* For example, Exam 1 Question 1*/
int your_function()
{
    return 0;
}

void arrfunc(int arr[], int &size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] <= 5 || i > 3)
        {
            arr[i]++;
        }
    }
    size--;
}
#endif