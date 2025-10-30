#ifndef _POINTERS_HPP
#define _POINTERS_HPP

/**
 * Copies the contents of the given integer array into a new array.
 *
 * @param arr The original array to copy.
 * @param size The number of elements in the array.
 * @return A pointer to the newly allocated array that contains the copied elements.
 */
int *copy(const int *arr, const int size)
{
  int * arr_copy = new int[size];
  for (int i=0;i<size;i++){
    arr_copy[i]=arr[i];
  }
  return arr_copy; // a new dynamically created array
}

/**
 * Appends a new integer value to the end of the given array.
 *
 * @param arr Reference to the pointer of the array to which the new value should be appended.
 * @param newval The new integer value to append to the array.
 * @param size Reference to the integer representing the current size of the array; will be updated after appending.
 */
void append(int *&arr, const int newval, int &size)
{
  //store the old arr somewhere
  int *old_arr = arr;

  //assign the arr with new empty size+1
  arr = new int[size+1];

  //copy the first n element from old to new
  for (int i=0;i<size;i++){
    arr[i]=old_arr[i];
  }

  //assign the last element to be the newval
  arr[size]=newval;
  
  //update size accordingly
  size++;

  delete [] old_arr;

}

#endif