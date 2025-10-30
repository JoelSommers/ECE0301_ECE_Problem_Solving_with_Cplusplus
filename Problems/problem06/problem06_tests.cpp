#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

#include "database.hpp"
#include "constants.hpp"

/* Provided test cases */

TEST_CASE("Test initialize", "[database]")
{
    // create the database as a dynamic array
    // ENTRIES and COLS are defined in constants.hpp
    // as the number of rows and columns in DATA, respectively
    double *db = new double[ENTRIES * COLS];
    // use the provided initialize function to fill db with entries from DATA
    initialize(db);

    // Get each value in the dynamic array db, and confirm that it matches
    // the corresponding value in DATA.
    // This tests that the initialize function called above
    // has correctly copied all of the values from DATA into db.
    double dbval, ref, diff;
    bool db_matches_DATA = true; // define a boolean to reduce REQUIRE statements in the loop
    for (int r = 0; r < ENTRIES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            // use the index function to get a 1D index for db from the row,column
            dbval = db[index(r, c)];
            // use double brackets to index DATA as a static 2D array
            ref = DATA[r][c];
            // these are double values, so we should check that their difference
            // is within a threshold instead of using ==
            diff = std::abs(dbval - ref);
            db_matches_DATA = (diff <= THRESHOLD);
            if (!db_matches_DATA)
            {
                // if any mismatch is detected, stop the comparisons
                break;
            }
        }
        if (!db_matches_DATA)
        {
            // need a second break to break out of the outer loop
            break;
        }
    }
    // check whether the loops completed without a mismatch
    REQUIRE(db_matches_DATA);

    // always deallocate at the end of each test case
    // when allocating with "new" in that test case
    delete[] db;
}

TEST_CASE("Test search", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // search for each DATA value in the corresponding column of db
    std::string field;
    double value;
    bool db_search = true;
    for (int r = 0; r < ENTRIES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            // defining field and value outside of the function call
            // makes debugging easier
            field = FIELDS[c];
            value = DATA[r][c];
            db_search = search(field, value, db, ENTRIES);
            if (!db_search)
            {
                break;
            }
        }
        if (!db_search)
        {
            break;
        }
    }
    REQUIRE(db_search);
    delete[] db;
}

TEST_CASE("Test search 2", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // search for a non-existing field
    std::string field = "Temperature";
    double value = 10;
    bool db_search = search(field, value, db, ENTRIES);
    REQUIRE_FALSE(db_search);

    // search for a non-existing value at a given field
    field = "Class";
    value = 2;
    db_search = search(field, value, db, ENTRIES);
    REQUIRE_FALSE(db_search);
    delete[] db;
}

TEST_CASE("Test add_entry", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // create a rows variable and new_row to pass into add_entry function
    int rows = ENTRIES;
    const double new_row[6] = {301, 3, 1737.4, 7.349e22, 3.3437, 27.321582};

    // search for element
    REQUIRE_FALSE(search("ID", 301, db, rows));

    // check if add_entry was successful
    REQUIRE(add_entry(new_row, db, rows));

    // search for element
    REQUIRE(search("ID", 301, db, rows));

    delete[] db;
}

TEST_CASE("Test add_entry 2", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // create a rows variable and new_row to pass into add_entry function
    int rows = ENTRIES;
    const double new_row[6] = {10, 0, 695700, 1988500e24, 1.408, 0};

    // search for element
    REQUIRE(search("ID", 10, db, rows));

    // check if add_entry was unsuccessful
    REQUIRE_FALSE(add_entry(new_row, db, rows));

    // search for element
    REQUIRE(search("ID", 10, db, rows));

    delete[] db;
}

TEST_CASE("Test remove_entry", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // create a rows variable to pass into remove_entry function
    int rows = ENTRIES;

    // search for element
    REQUIRE(search("ID", 299, db, rows));

    // check if remove_entry was successful
    REQUIRE(remove_entry(299, db, rows));

    // search for element
    REQUIRE_FALSE(search("ID", 299, db, rows));

    delete[] db;
}

TEST_CASE("Test add_entry then remove_entry", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // create a rows variable and new_row to pass into add_entry function
    int rows = ENTRIES;
    const double new_row[6] = {301, 3, 1737.4, 7.349e22, 3.3437, 27.321582};

    // check if add_entry was successful
    REQUIRE(add_entry(new_row, db, rows));

    // search for element
    REQUIRE(search("ID", 301, db, rows));

    // check if remove_entry was successful
    REQUIRE(remove_entry(301, db, rows));

    // search for element
    REQUIRE_FALSE(search("ID", 301, db, rows));

    delete[] db;
}

// On the 5th attempt I added the add then remove test case above.

TEST_CASE("Test Part 2 A", "[database]")
{
    //test search()
    double *db = new double[ENTRIES * COLS];
    initialize(db);
    REQUIRE_FALSE(search("Color", 10, db, ENTRIES));

    //test add duplicate
    const double new_row[6] = {10, 0, 695700, 1988500e24, 1.408, 0};
    int rows = ENTRIES;
    REQUIRE_FALSE(add_entry(new_row, db, rows));
    REQUIRE(rows == 5);

    //static array and dynamic array
    int arr[4]={1,4,9,16};
    int *arr2=new int[4];
    for (int i=0;i<4;i++){
        arr2[i]=arr[i];
    }
    std::cout<<arr<<std::endl;
    std::cout<<arr2<<std::endl;

    delete [] arr2;
    delete [] db;

    // create st_arr with valid content
    int st_arr[4] = {1, 4, 9, 16};

    std::cout << st_arr <<std::endl;
    std::cout << *st_arr <<std::endl;

    // create st_arr2 with empty content
    int st_arr2[4];

    // st_arr2 = st_arr // there will be an error because we can't change the address of static array

    // create dy_arr with valid content
    int *dy_arr = new int[4]{1, 4, 6, 9};

    // create dy_arr2 with empty content
    int *dy_arr2 = new int[4];

    dy_arr2 = dy_arr; // the dy_arr2 will now point to the contects of dy_arr but there will be a memory leak for the data of dy_arr2

    // create vec with valid content
    std::vector<int> vec = {1, 4, 6, 9};
    // create vec2 with empty content
    std::vector<int> vec2;

    vec2 = vec; // vec2 will now have the contents of vec. We are essentially setting two objects equal to each other.

    delete[] dy_arr;
}