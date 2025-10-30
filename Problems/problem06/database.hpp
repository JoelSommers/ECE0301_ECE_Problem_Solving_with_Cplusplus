#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <cstdlib>
#include <string>

#include "constants.hpp"

/* Provided functions */
int index(int row, int col)
{
    /* Calculates a 1D index from a row and column.
        A 2D matrix can be represented in memory with a 1D array,
        assuming that indices 0 to COLS-1 are the items in the first row,
        indices COLS to 2*COLS-1 are the items in the second row, etc.
        So if we want to access data at a specific row and column,
        we calculate that index as row*COLS + column
    */
    return row * COLS + col;
}

int column_index(std::string field)
{
    /* Uses parallel arrays to determine the integer column index
        given the string field name.
        FIELDS is defined in constants.hpp. This function does a linear
        search over the FIELDS array to find and return the index of the
        column with the specified field name.
        Returns -1 if field name is not valid.
    */
    for (int c = 0; c < COLS; c++)
    {
        if (FIELDS[c] == field)
        {
            return c;
        }
    }
    return -1;
}

void initialize(double *database)
{
    /* Fills the dynamic array database with data from the constant DATA.
        Note the use of the index function to get the index for the dynamic array
        database, versus using double brackets for the the static 2D array DATA.
    */
    for (int r = 0; r < ENTRIES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            database[index(r, c)] = DATA[r][c];
        }
    }
}

/* Functions to implement */
bool search(const std::string field, const double value,
            const double *database, const int rows)
{
    // check if field is non-existant (added after 1st attempt)!!!
    if (column_index(field) == -1)
    {
        return false;
    }

    // find the columns index
    int col = column_index(field);

    // loop through the database and sequentially search each element in the specified field.
    int ind;
    for (int i = 0; i < rows; i++)
    {
        ind = index(i, col);

        // approximate equality due to floating point values
        if (std::abs(value - database[ind]) <= THRESHOLD)
        {
            return true;
        }
    }

    return false;
}

bool add_entry(const double new_row[],
               double *&database, int &rows)
{
    // after 3rd attmpt: I realized that I created a new dynamically allocated array before the error case which is causing errors in the test case.

    // check for duplicates before adding new entry
    if (search(FIELDS[0], new_row[0], database, rows))
    {
        return false;
    }

    // copy the old arr into a pointer to keep a copy of it
    double *old_database = database;

    // create new dynamically allocated array with a new size of (rows+1)*COLS
    database = new double[(rows + 1) * COLS];

    // element-wise copy
    for (int i = 0; i < rows * COLS; i++)
    {
        database[i] = old_database[i];
    }

    // assign the new_row to the end of the array
    for (int j = 0; j < COLS; j++)
    {
        database[rows * COLS + j] = new_row[j];
    }

    // update the rows
    rows++;

    // deallocate the old database
    delete[] old_database;

    return true;
}

bool remove_entry(const double id,
                  double *&database, int &rows)
{

    // after 3rd attmpt: I realized that I created a new dynamically allocated array before the error case which is causing errors in the test case.

    // check for valid ID
    if (!search("ID", id, database, rows))
    {
        return false;
    }

    // copy the old arr into a pointer to keep a copy of it
    double *old_database = database;

    // create new dynamically allocated array with a new size of (rows-1)*COLS
    database = new double[(rows - 1) * COLS];

    // element-wise copy every row except for the one that has the id
    int iter = 0;
    for (int i = 0; i < rows * COLS; i++)
    {
        // {1,2,3,4}, {2,2,3,4}, {3,2,3,4}
        if (old_database[i] == id)
        {
            i = i + COLS;
            if (i == rows * COLS)
            {
                break;
            }
        }
        database[iter] = old_database[i];
        iter++;
    }

    // update rows
    rows--;

    // deallocate the old database
    delete[] old_database;

    return true;
}

#endif

//after 2nd attmempt i tried deallocating the memory before returning false
