#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "pointers_starter.hpp"

TEST_CASE("Test array initialization in dynamic memory", "[ptr-dynamic]")
{
  int a=5;
  int *static_ptr=&a;
  std::cout<<static_ptr<<std::endl;

  //use dereference op to get the value of a
  std::cout<<*static_ptr<<std::endl;

  (*static_ptr)++; //a++
  std::cout << *static_ptr << std::endl;

  int *b_ptr=new int(7);
  std::cout<<*b_ptr<<std::endl;

  int *arr_ptr=new int[5]{0,1,2,3,4};
  std::cout<<arr_ptr<<std::endl; //this will be a hex address
  std::cout << *arr_ptr << std::endl; // this will be the first cell

  for (int i=0; i<5;i++){
    REQUIRE(arr_ptr[i]==i);
  }

  double *db_ptr=new double(3.14);
  double *dbarr_ptr = new double[3]{3.14,3.15,3.16};

  int *arr_ptr2;
  arr_ptr2=new int[5];

  for (int i = 0; i < 5; i++)
  {
    arr_ptr2[i]=arr_ptr[i];
    REQUIRE(arr_ptr2[i]==i);
  }

  REQUIRE_FALSE(arr_ptr2==arr_ptr);
  delete b_ptr;
  delete [] arr_ptr;
  delete db_ptr;
  delete dbarr_ptr;
  delete [] arr_ptr2;
  //...
  b_ptr=nullptr;
}

TEST_CASE("Test array copy in dynamic memory", "[ptr-copy]")
{
  int size=5;
  int *arr = new int[size]{0,1,2,3,4};
  int *arr_copy = new int[size];
  for (int i = 0; i < size; i++)
  {
    arr_copy[i] = arr[i];
    REQUIRE(arr_copy[i] == i);
  }

  //at this moment I will no longer use original array
  delete [] arr;
  arr_copy[3]=9;
  REQUIRE(arr_copy[3]==9);
  

}

TEST_CASE("Test bad array copy in dynamic memory", "[ptr-copy-bad]")
{
  int size = 5;
  int *arr = new int[size]{0, 1, 2, 3, 4};
  int *arr_copy = arr;

  delete [] arr;
  // arr_copy[3] = 9;
  // std::cout<<arr_copy[10]<<std::endl;
  // delete [] arr_copy;
}

TEST_CASE("Test array copy function in dynamic memory", "[ptr-fnc]")
{
  int size = 5;
  int *arr = new int[size]{0, 1, 2, 3, 4};
  int *arr_copy = new int [size];
  arr_copy=copy(arr,size);
  //int * arr_copy=copy(arr,size); //you can do the code above on one line
  
  for (int i=0;i<size;i++){
    REQUIRE(arr_copy[i]==arr[i]);
  }

  REQUIRE_FALSE(arr_copy==arr);

  delete[] arr;
  delete[] arr_copy;
}

TEST_CASE("Test array append function in dynamic memory", "[ptr-apd]")
{
  int size = 5;
  int *arr = new int[size]{0, 1, 2, 3, 4};

  append(arr,80,size);
  
  REQUIRE(size==6);
  REQUIRE(arr[5]==80);
  for (int i=0;i<5;i++){
    arr[i]=i;
  }

}