#include <iostream>
using T = int;
size_t size = 10;
T value = 20;

int foo() {
  T* d = new T[size];
  for (size_t i = 0; i < size; ++i) {
    d[i] = value;
  }
  long long sum = 0;
  for (size_t i = 0; i < size; ++i) {
    sum += d[i];
  }
  delete [] d;
  return static_cast< int >(sum);
}
int bar() {
  T* d = static_cast< T* >(::operator new(sizeof(T) * size));
  size_t constructed = 0;
  for (size_t i = 0; i < size; ++i) {
    new (d + i) T(value);
    ++constructed;
  }
  long long sum = 0;
  for (size_t i = 0; i < constructed; ++i) {
    sum += d[i];
  }

  for (size_t i = 0; i < constructed; ++i) {
    (d + i)->~T();
  }
  ::operator delete(d);
  return static_cast< int >(sum);
}