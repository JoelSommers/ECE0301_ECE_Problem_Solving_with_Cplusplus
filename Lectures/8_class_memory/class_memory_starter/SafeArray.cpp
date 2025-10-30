#include "SafeArray.hpp"
#include <stdexcept>
#include <algorithm>

SafeArray::SafeArray() : size(0), dataptr(nullptr)
{
  // size=0;
  // dataptr=nullptr;
}

SafeArray::SafeArray(int s)
{
  size = s;
  dataptr = new int[size];
  for (int i = 0; i < size; i++)
  {
    dataptr[i] = 0;
  }
}

SafeArray::~SafeArray()
{
  delete[] dataptr;
}

SafeArray::SafeArray(const SafeArray &arr_copy)
{
  size = arr_copy.size;
  dataptr = new int[size];
  for (int i = 0; i < size; i++)
  {
    dataptr[i] = arr_copy.dataptr[i];
  }
}

SafeArray &SafeArray::operator=(SafeArray arr_copy)
{
  size = arr_copy.size;
  std::swap(dataptr, arr_copy.dataptr);
  return *this;
}

int SafeArray::get_size() const
{

  return size;
}

int SafeArray::operator[](int idx) const
{
  if (idx < 0 || idx >= size)
  {
    throw std::out_of_range("Index out of range");
  }
  return dataptr[idx];
}

int &SafeArray::operator[](int idx)
{
  if (idx < 0 || idx >= size)
  {
    throw std::out_of_range("Index out of range");
  }
  return dataptr[idx];
}
