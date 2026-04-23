#include <iostream>
#include <cstring>
#include <iterator>
#include "pe-vector.hpp"
using knk::Vector;

bool testConstructAndDestruct(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}
bool testDefaultVectorIsEmpty(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}
bool testSizeOfEmptyVector(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  return !v.getSize();
}
bool testSizeOfNonEmptyVector(const char** pname) {
  *pname = __func__;
  constexpr size_t size = 2;
  Vector< int > v(size, 5);
  return v.getSize() == size;
}
bool testElementCheckedAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  try {
    int& r = v.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}
bool testElementCheckedConstAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int& r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}
bool testElementCheckedOutOfBoundAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}
bool testElementCheckedOutOfBoundConstAccess(const char** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}
bool testCopyConstructor(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2};
  Vector< int > yav = v;
  if (v.isEmpty() || yav.isEmpty()) {
    throw std::logic_error("Vectors expected to be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

bool testCapacityOfDefaultVector(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.getCapcity() == 0;
}

bool testCapacityNotLessThanSize(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  for (int i = 0; i < 20; ++i) {
    v.pushBack(i);
    if (v.getCapcity() < v.getSize()) {
      return false;
    }
  }
  return true;
}

bool testPopBackDecreasesSize(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  v.popBack();
  if (v.getSize() != 2) {
    return false;
  }
  return v[0] == 1 && v[1] == 2;
}

bool testInsertByIndex(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 3};
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testEraseByIndexRange(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3, 4};
  v.erase(1, 3);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 4;
}

bool testInsertByIteratorRange(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 4};
  int add[] = {2, 3};
  v.insert(v.begin() + 1, std::begin(add), std::end(add));
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;
}

bool testEraseByIterator(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  auto it = v.erase(v.begin() + 1);
  if (v.getSize() != 2 || v[0] != 1 || v[1] != 3) {
    return false;
  }
  return it == v.begin() + 1;
}

bool testEqualityOperator(const char** pname) {
  *pname = __func__;
  Vector< int > a{1, 2, 3};
  Vector< int > b{1, 2, 3};
  Vector< int > c{1, 2};
  return (a == b) && !(a == c);
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct,
      "Vector must be default"
      " constructable" },
    { testDefaultVectorIsEmpty,
      "Default constructed"
      " vector must be empty" },
    { testSizeOfEmptyVector,
      "Size of empty vector"
      " must be zero" },
    { testSizeOfNonEmptyVector,
      "Size of non-empty vector"
      " must be greater than zero" },
    { testElementCheckedAccess, "Inbound access must return lvalue reference to indexed value" },
    { testElementCheckedOutOfBoundAccess, "Out of bound access must generate exception with specific text" },
    { testElementCheckedConstAccess, "Same as inbound access but const" },
    { testElementCheckedOutOfBoundConstAccess, "Same as out of bound but const" },
    { testCopyConstructor, "Copied vector must be equal to original" },
    { testCapacityOfDefaultVector, "Capacity of default vector must be zero" },
    { testCapacityNotLessThanSize, "Capacity must be >= size after pushBack" },
    { testPopBackDecreasesSize, "popBack must decrease size and preserve order" },
    { testInsertByIndex, "insert(id, value) must insert at position" },
    { testEraseByIndexRange, "erase(beg, end) must remove a range" },
    { testInsertByIteratorRange, "Iterator-range insert must work" },
    { testEraseByIterator, "erase(iterator) must remove one and return next" },
    { testEqualityOperator, "operator== must compare elementwise" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[NOT RUN] " << testName << "\n";
      std::cout << "\t" << "Reason: " << e.what() << "\n";
      ++failed;
      continue;
    }
    if (!r) {
      ++failed;
      std::cout << "[FAIL] " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}