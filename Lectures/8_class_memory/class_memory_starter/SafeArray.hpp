#ifndef _SAFE_ARRAY_HPP
#define _SAFE_ARRAY_HPP

class SafeArray
{
private:
  int *dataptr;
  int size;

public:
  SafeArray();
  SafeArray(int);
  ~SafeArray();

  SafeArray(const SafeArray &);

  SafeArray &operator=(SafeArray);//pass by value

  int get_size() const;
  int operator[](int) const;
  int &operator[](int);
};

#endif