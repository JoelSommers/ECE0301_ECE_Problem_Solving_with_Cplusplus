#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SafeArray.hpp"

TEST_CASE("Test default construction", "[safearray]")
{
    SafeArray arr;
    REQUIRE(arr.get_size() == 0);

    SafeArray arr2(5);
    REQUIRE(arr2.get_size() == 5);

    for (int i = 0; i < 5; i++)
    {
        REQUIRE(arr2[i] == 0);
    }
    REQUIRE_NOTHROW(arr[4]);
    REQUIRE_THROWS_AS(arr2[-1], std::out_of_range);
    REQUIRE_THROWS_AS(arr2[5], std::out_of_range);

    arr2[0] = 9;
    arr2[1] = 7;
    arr2[2] = 5;
    arr2[3] = 3;
    REQUIRE(arr2[0] == 9);
    REQUIRE_THROWS_AS(arr2[-1] = 9, std::out_of_range);
    REQUIRE_THROWS_AS(arr2[5] = 9, std::out_of_range);

    // arr2 = 9 7 5 3 0

    SafeArray arr3 = arr2; // where the copy constructor is called

    REQUIRE(arr3[0] == 9);
    REQUIRE(arr3[1] == 7);
    REQUIRE(arr3[2] == 5);

    arr3[2]==50; // 9 7 50 3 0
    REQUIRE(arr2[2]==5);
    REQUIRE(arr3[2] == 50);

    SafeArray arr4(5);
    arr4=arr2; //where copy assignment operator is called
    REQUIRE(arr4[0] == 9);
    REQUIRE(arr4[1] == 7);
    REQUIRE(arr4[2] == 5);
}