#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector> // this header file has to be included
#include <cmath>

TEST_CASE("Vector init", "[vector-empty]")
{
    // declare vector of type <int>, <double>
    std::vector<int> vec1;

    // without any modifier after vec1, it is initialized as empty
    REQUIRE(vec1.empty());
    REQUIRE(vec1.size() == 0);
}

TEST_CASE("Vector init with size", "[vector-size]")
{
    std::vector<int> vec1(5);
    REQUIRE_FALSE(vec1.empty());

    for (int i=0;i<5;i++){
        REQUIRE(vec1[i]==0);
    }

    REQUIRE(vec1.size()==5);

    vec1[0] = 4;
    vec1[1] = 9;
    vec1[2] = 16;

    REQUIRE(vec1[0] == 4);
    REQUIRE(vec1[1] == 9);
    REQUIRE(vec1[2] == 16);

    std::vector<double> vec_d(3);

    vec_d[0]=3.14;
    vec_d[1]=2.72;
    vec_d[2]=sqrt(2);

    const double threshold=0.01;

    REQUIRE(std::abs(vec_d[2]-1.414)<=threshold);
}

TEST_CASE("Vector updating size via push and pop", "[vector-update]")
{
    std::vector<int> vec1(6);
    for (int i=0;i<5;i++){
        vec1[i]=i;
    }
    vec1.push_back(7);
    REQUIRE(vec1.size()==7);

    REQUIRE(vec1[vec1.size()-1] == 7);

    vec1.pop_back();
    vec1.pop_back();

    REQUIRE(vec1.size()==5);
    REQUIRE(vec1[4] == 4);

    vec1.pop_back();
    vec1.pop_back();
    vec1.pop_back();
    vec1.pop_back();
    vec1.pop_back();
    REQUIRE(vec1.size()==0);
    REQUIRE(vec1.empty());

    //vec1.pop_back();
}

TEST_CASE("Vector insert and erase", "[vector-insert-erase]")
{
    std::vector<int> vec2 = {1,4,9,16,25};
    
    //e.g. target vec looks like {1,4,10,11,16,25}

    vec2[2]=10;
    //vec2.insert(3,11);
    vec2.insert(vec2.begin()+3,11);

    REQUIRE(vec2.size()==6);

    // another target vec looks like {1,4,10,11,25}
    vec2.erase(vec2.begin()+4);
    REQUIRE(vec2.size() == 5);
    REQUIRE(vec2[4]==25);
    REQUIRE(vec2[3]==11);
}

TEST_CASE("Vector indexing via []", "[vector-index]")
{
    std::vector<int> vec2 = {1, 4, 9, 16, 25};
    std::cout<<vec2[5]<<std::endl;
    std::cout << vec2[10] << std::endl;
}

TEST_CASE("Vector indexing via at", "[vector-index]")
{
    std::vector<int> vec2 = {1, 4, 9, 16, 25};
    std::cout << vec2.at(1) << std::endl;
    std::cout << vec2.at(2) << std::endl;

    REQUIRE_THROWS_AS(vec2.at(6),std::out_of_range);
}

TEST_CASE("Vector of other data type and ADT", "[vector-ADT]")
{
    struct Student{
        int id;
        std::string name;
    };
    Student pitt_student{1234,"tim"};

    REQUIRE(pitt_student.id==1234);
    REQUIRE(pitt_student.name=="tim");

    std::vector<Student> students={{1234,"tim"},{1235,"tom"}};

    REQUIRE(students[0].id==1234);
    REQUIRE(students[1].id==1235);


    std::vector<double> vec1={1.1,2.728,5.2};
    std::vector<char> vec2={'e','c','e'};
    REQUIRE(std::abs(vec1[1]-2.728)<=1e-9);
    REQUIRE(vec2[1]=='c');

    struct Entry{
        char name;
        int val;
    };

    std::vector<Entry>vec3={{'e',14},{'c',12},{'e',14}};
    REQUIRE(vec3.size()==3);
    REQUIRE(vec3.at(0).name=='e');
    REQUIRE(vec3.at(0).val==14);
    REQUIRE(vec3.at(1).name == 'c');
    REQUIRE(vec3.at(1).val == 12);
    REQUIRE(vec3.at(2).name == 'e');
    REQUIRE(vec3.at(2).val == 14);
}