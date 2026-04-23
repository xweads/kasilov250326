#include <vector>
#include <iostream>
#include <initializer_list>

struct A {
  std::vector< size_t > payload;
  A(size_t n, size_t value): payload(n, value) {
    std::cout << "A(size_t, size_t) called: n=" << n << ", value=" << value << "\n";
  }
  A(std::initializer_list< size_t > il): payload(il) {
    std::cout << "A(std::initializer_list<size_t>) called: size=" << payload.size() << "\n";
  }
};

static void printVec(const std::vector< size_t >& v, const char* name) {
  std::cout << name << ": size=" << v.size() << ", values=";
  for (auto x : v) {
    std::cout << x << ' ';
  }
  std::cout << "\n";
}

int main()
{
  A a{11ull, 11ull};
  A b(11ull, 11ull);
  printVec(a.payload, "a.payload");
  printVec(b.payload, "b.payload");
  std::vector< size_t > v1(11, 10);
  std::vector< size_t > v2{11, 10};
  printVec(v1, "v1(11, 10)");
  printVec(v2, "v2{11, 10}");
}