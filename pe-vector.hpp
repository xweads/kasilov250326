#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
namespace knk {
  template< class T >
  class Vector {
   public:
    ~Vector();
    Vector();
    Vector(size_t size, const T& value);
    explicit Vector(std::initializer_list< T > il);
    Vector(const Vector< T >& rhs);
    Vector(Vector< T >&& rhs) noexcept;
    Vector< T >& operator=(const Vector< T >& rhs);
    Vector< T >& operator=(Vector< T >&& rhs) noexcept;
    void swap(Vector< T >& rhs) noexcept;
    void insert(size_t id, const T& t);
    void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end);
    void erase(size_t id);
    void erase(size_t beg, size_t end);
    struct VectorIterator {
      using iterator_category = std::random_access_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      pointer p_ = nullptr;

      VectorIterator() = default;
      explicit VectorIterator(pointer p): p_(p) {}

      reference operator*() const { return *p_; }
      pointer operator->() const { return p_; }

      VectorIterator& operator++() { ++p_; return *this; }
      VectorIterator operator++(int) { VectorIterator tmp(*this); ++(*this); return tmp; }
      VectorIterator& operator--() { --p_; return *this; }
      VectorIterator operator--(int) { VectorIterator tmp(*this); --(*this); return tmp; }

      VectorIterator& operator+=(difference_type n) { p_ += n; return *this; }
      VectorIterator& operator-=(difference_type n) { p_ -= n; return *this; }
      VectorIterator operator+(difference_type n) const { VectorIterator tmp(*this); return tmp += n; }
      VectorIterator operator-(difference_type n) const { VectorIterator tmp(*this); return tmp -= n; }
      difference_type operator-(const VectorIterator& rhs) const { return p_ - rhs.p_; }
      reference operator[](difference_type n) const { return p_[n]; }

      friend bool operator==(const VectorIterator& a, const VectorIterator& b) { return a.p_ == b.p_; }
      friend bool operator!=(const VectorIterator& a, const VectorIterator& b) { return !(a == b); }
      friend bool operator<(const VectorIterator& a, const VectorIterator& b) { return a.p_ < b.p_; }
      friend bool operator>(const VectorIterator& a, const VectorIterator& b) { return b < a; }
      friend bool operator<=(const VectorIterator& a, const VectorIterator& b) { return !(b < a); }
      friend bool operator>=(const VectorIterator& a, const VectorIterator& b) { return !(a < b); }
    };

    struct ConstVectorIterator {
      using iterator_category = std::random_access_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = const T*;
      using reference = const T&;

      pointer p_ = nullptr;

      ConstVectorIterator() = default;
      explicit ConstVectorIterator(pointer p): p_(p) {}
      ConstVectorIterator(const VectorIterator& it): p_(it.p_) {}

      reference operator*() const { return *p_; }
      pointer operator->() const { return p_; }

      ConstVectorIterator& operator++() { ++p_; return *this; }
      ConstVectorIterator operator++(int) { ConstVectorIterator tmp(*this); ++(*this); return tmp; }
      ConstVectorIterator& operator--() { --p_; return *this; }
      ConstVectorIterator operator--(int) { ConstVectorIterator tmp(*this); --(*this); return tmp; }

      ConstVectorIterator& operator+=(difference_type n) { p_ += n; return *this; }
      ConstVectorIterator& operator-=(difference_type n) { p_ -= n; return *this; }
      ConstVectorIterator operator+(difference_type n) const { ConstVectorIterator tmp(*this); return tmp += n; }
      ConstVectorIterator operator-(difference_type n) const { ConstVectorIterator tmp(*this); return tmp -= n; }
      difference_type operator-(const ConstVectorIterator& rhs) const { return p_ - rhs.p_; }
      reference operator[](difference_type n) const { return p_[n]; }

      friend bool operator==(const ConstVectorIterator& a, const ConstVectorIterator& b) { return a.p_ == b.p_; }
      friend bool operator!=(const ConstVectorIterator& a, const ConstVectorIterator& b) { return !(a == b); }
      friend bool operator<(const ConstVectorIterator& a, const ConstVectorIterator& b) { return a.p_ < b.p_; }
      friend bool operator>(const ConstVectorIterator& a, const ConstVectorIterator& b) { return b < a; }
      friend bool operator<=(const ConstVectorIterator& a, const ConstVectorIterator& b) { return !(b < a); }
      friend bool operator>=(const ConstVectorIterator& a, const ConstVectorIterator& b) { return !(a < b); }
    };

    using iterator = VectorIterator;
    using const_iterator = ConstVectorIterator;

    iterator begin() noexcept { return iterator(data_); }
    iterator end() noexcept { return iterator(data_ + size_); }
    const_iterator begin() const noexcept { return const_iterator(data_); }
    const_iterator end() const noexcept { return const_iterator(data_ + size_); }
    const_iterator cbegin() const noexcept { return const_iterator(data_); }
    const_iterator cend() const noexcept { return const_iterator(data_ + size_); }

    template< class FwdIterator >
    void insert(VectorIterator pos, FwdIterator begin, FwdIterator end);

    VectorIterator insert(VectorIterator pos, const T& t);
    VectorIterator insert(VectorIterator pos, size_t count, const T& t);
    VectorIterator insert(VectorIterator pos, std::initializer_list< T > il);

    VectorIterator erase(VectorIterator pos);
    VectorIterator erase(VectorIterator first, VectorIterator last);
    VectorIterator erase(VectorIterator pos, size_t count);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapcity() const noexcept;
    void pushBack(const T&);
    void pushBackRepeat(const T&, size_t k);
    void popBack();
    void pushFront(const T&);
    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

   private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t size);

    static T* allocateRaw(size_t n);
    static void deallocateRaw(T* p) noexcept;
    static void destroyRange(T* p, size_t n) noexcept;
    void reserve(size_t newCapacity);
  };
  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}
template< class T >
knk::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t j = 0;
  try {
    for (auto i = il.begin(); i != il.end(); ++i) {
      new (data_ + j) T(*i);
      ++j;
    }
    size_ = j;
  } catch (...) {
    destroyRange(data_, j);
    deallocateRaw(data_);
    data_ = nullptr;
    size_ = capacity_ = 0;
    throw;
  }
}

template< class T >
typename knk::Vector< T >::VectorIterator knk::Vector< T >::insert(VectorIterator pos, const T& t)
{
  const size_t id = static_cast< size_t >(pos - begin());
  insert(id, t);
  return iterator(data_ + id);
}

template< class T >
typename knk::Vector< T >::VectorIterator knk::Vector< T >::insert(VectorIterator pos, size_t count, const T& t)
{
  const size_t id = static_cast< size_t >(pos - begin());
  if (id > size_) {
    throw std::out_of_range("id out of bound");
  }
  if (!count) {
    return iterator(data_ + id);
  }

  Vector< T > tmp;
  tmp.reserve(size_ + count);
  size_t constructed = 0;
  try {
    for (size_t i = 0; i < id; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
    for (size_t i = 0; i < count; ++i) {
      new (tmp.data_ + constructed) T(t);
      ++constructed;
    }
    for (size_t i = id; i < size_; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
  } catch (...) {
    destroyRange(tmp.data_, constructed);
    deallocateRaw(tmp.data_);
    throw;
  }
  tmp.size_ = constructed;
  swap(tmp);
  return iterator(data_ + id);
}

template< class T >
typename knk::Vector< T >::VectorIterator knk::Vector< T >::insert(VectorIterator pos, std::initializer_list< T > il)
{
  const size_t id = static_cast< size_t >(pos - begin());
  insert(iterator(data_ + id), il.begin(), il.end());
  return iterator(data_ + id);
}

template< class T >
typename knk::Vector< T >::VectorIterator knk::Vector< T >::erase(VectorIterator pos)
{
  return erase(pos, 1);
}

template< class T >
typename knk::Vector< T >::VectorIterator knk::Vector< T >::erase(VectorIterator first, VectorIterator last)
{
  const size_t beg = static_cast< size_t >(first - begin());
  const size_t end = static_cast< size_t >(last - begin());
  erase(beg, end);
  return iterator(data_ + beg);
}

template< class T >
typename knk::Vector< T >::VectorIterator knk::Vector< T >::erase(VectorIterator pos, size_t count)
{
  const size_t id = static_cast< size_t >(pos - begin());
  if (id > size_) {
    throw std::out_of_range("id out of bound");
  }
  const size_t end = std::min(size_, id + count);
  erase(id, end);
  return iterator(data_ + id);
}

template< class T >
void knk::Vector< T >::pushBackRepeat(const T& t, size_t k)
{
  Vector< T > cpy(*this);
  for (size_t i = 0; i < k; ++i) {
    cpy.pushBack(t);
  }
  swap(cpy);
}
template< class T >
void knk::Vector< T >::pushBack(const T& t)
{
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  new (data_ + size_) T(t);
  ++size_;
}

template< class T >
void knk::Vector< T >::popBack()
{
  if (!size_) {
    return;
  }
  (data_ + (size_ - 1))->~T();
  --size_;
}

template< class T >
void knk::Vector< T >::pushFront(const T& t)
{
  insert(0, t);
}
template< class T >
T& knk::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}
template< class T >
const T& knk::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}
template< class T >
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
}
template< class T >
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}
template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  size_t constructed = 0;
  try {
    for (; constructed < rhs.getSize(); ++constructed) {
      new (data_ + constructed) T(rhs.data_[constructed]);
    }
    size_ = constructed;
  } catch (...) {
    destroyRange(data_, constructed);
    deallocateRaw(data_);
    data_ = nullptr;
    size_ = capacity_ = 0;
    throw;
  }
}
template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}
template< class T >
knk::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(allocateRaw(size)),
  size_(0),
  capacity_(size)
{}
template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  size_t constructed = 0;
  try {
    for (; constructed < size; ++constructed) {
      new (data_ + constructed) T(value);
    }
    size_ = constructed;
  } catch (...) {
    destroyRange(data_, constructed);
    deallocateRaw(data_);
    data_ = nullptr;
    size_ = capacity_ = 0;
    throw;
  }
}
template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return size_;
}
template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
}
template< class T >
knk::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template< class T >
knk::Vector< T >::~Vector() {
  destroyRange(data_, size_);
  deallocateRaw(data_);
}

template< class T >
size_t knk::Vector< T >::getCapcity() const noexcept {
  return capacity_;
}

template< class T >
T* knk::Vector< T >::allocateRaw(size_t n)
{
  if (!n) {
    return nullptr;
  }
  return static_cast< T* >(::operator new(sizeof(T) * n));
}

template< class T >
void knk::Vector< T >::deallocateRaw(T* p) noexcept
{
  ::operator delete(p);
}

template< class T >
void knk::Vector< T >::destroyRange(T* p, size_t n) noexcept
{
  for (size_t i = 0; i < n; ++i) {
    (p + i)->~T();
  }
}

template< class T >
void knk::Vector< T >::reserve(size_t newCapacity)
{
  if (newCapacity <= capacity_) {
    return;
  }
  T* newData = allocateRaw(newCapacity);
  size_t constructed = 0;
  try {
    for (; constructed < size_; ++constructed) {
      new (newData + constructed) T(std::move_if_noexcept(data_[constructed]));
    }
  } catch (...) {
    destroyRange(newData, constructed);
    deallocateRaw(newData);
    throw;
  }
  destroyRange(data_, size_);
  deallocateRaw(data_);
  data_ = newData;
  capacity_ = newCapacity;
}

template< class T >
void knk::Vector< T >::insert(size_t id, const T& t)
{
  if (id > size_) {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > tmp;
  tmp.reserve(size_ + 1);
  size_t constructed = 0;
  try {
    for (size_t i = 0; i < id; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
    new (tmp.data_ + constructed) T(t);
    ++constructed;
    for (size_t i = id; i < size_; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
  } catch (...) {
    destroyRange(tmp.data_, constructed);
    deallocateRaw(tmp.data_);
    throw;
  }
  tmp.size_ = constructed;
  swap(tmp);
}

template< class T >
void knk::Vector< T >::insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end)
{
  if (id > size_ || beg > end || end > rhs.size_) {
    throw std::out_of_range("id out of bound");
  }
  const size_t add = end - beg;
  Vector< T > tmp;
  tmp.reserve(size_ + add);
  size_t constructed = 0;
  try {
    for (size_t i = 0; i < id; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
    for (size_t i = beg; i < end; ++i) {
      new (tmp.data_ + constructed) T(rhs.data_[i]);
      ++constructed;
    }
    for (size_t i = id; i < size_; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
  } catch (...) {
    destroyRange(tmp.data_, constructed);
    deallocateRaw(tmp.data_);
    throw;
  }
  tmp.size_ = constructed;
  swap(tmp);
}

template< class T >
void knk::Vector< T >::erase(size_t id)
{
  erase(id, id + 1);
}

template< class T >
void knk::Vector< T >::erase(size_t beg, size_t end)
{
  if (beg > end || end > size_) {
    throw std::out_of_range("id out of bound");
  }
  const size_t removed = end - beg;
  if (!removed) {
    return;
  }
  Vector< T > tmp;
  tmp.reserve(size_ - removed);
  size_t constructed = 0;
  try {
    for (size_t i = 0; i < beg; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
    for (size_t i = end; i < size_; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
  } catch (...) {
    destroyRange(tmp.data_, constructed);
    deallocateRaw(tmp.data_);
    throw;
  }
  tmp.size_ = constructed;
  swap(tmp);
}

template< class T >
template< class FwdIterator >
void knk::Vector< T >::insert(VectorIterator pos, FwdIterator beginIt, FwdIterator endIt)
{
  const size_t id = static_cast< size_t >(pos - begin());
  if (id > size_) {
    throw std::out_of_range("id out of bound");
  }
  const size_t add = static_cast< size_t >(std::distance(beginIt, endIt));
  if (!add) {
    return;
  }
  Vector< T > tmp;
  tmp.reserve(size_ + add);
  size_t constructed = 0;
  try {
    for (size_t i = 0; i < id; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
    for (auto it = beginIt; it != endIt; ++it) {
      new (tmp.data_ + constructed) T(*it);
      ++constructed;
    }
    for (size_t i = id; i < size_; ++i) {
      new (tmp.data_ + constructed) T(data_[i]);
      ++constructed;
    }
  } catch (...) {
    destroyRange(tmp.data_, constructed);
    deallocateRaw(tmp.data_);
    throw;
  }
  tmp.size_ = constructed;
  swap(tmp);
}

template< class T >
bool knk::operator==(const Vector< T >& lhs, const Vector< T >& rhs)
{
  if (lhs.getSize() != rhs.getSize()) {
    return false;
  }
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    if (!(lhs[i] == rhs[i])) {
      return false;
    }
  }
  return true;
}
#endif