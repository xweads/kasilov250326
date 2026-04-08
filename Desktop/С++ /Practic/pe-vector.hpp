#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace knk{
template < class T >
struct Vector {
    public:
    Vector()
    ~Vector();
    Vecotr(const Vector <T> &rhs);
    Vector (Vector< T >&& rhs) noexcept;
    Vector(size_t size, const T & value );

    
   

    Vector < T > & operator=(const Vector <T> & rhs) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
 
    //Реализовать + тестирование
    size_t getCapacity() const noexcept;
    void pushBack(const T &);
    void popBack();
    void pushFront(const T &);

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    private:
    T * data;
    size_t size_, capacity_;
    explicit Vector(size_t size);
  };
}
template < class T >
Vector< T >::Vector(Vector < T >&& rhs):
data_(rhs.data_),
size_(rhs.size_),
capacity_(rhs.capacity_)
{
    rhs.data_ = nullptr;
}
template < class T >
knk::Vector < T >::Vector< T >::operator=(Vector < T >&& rhs) noexcept
{
    Vector< T > cpy(std::move(rhs));
    swap(cpy);
    return *this;
}
template < class T > 
void knk::Vector::pushBack(const T& t)
{
    Vector< T > v(getSize() + 1);
    for (size_t i =0 ; i < getSize() ; ++i){
        v[i] = (*this)[i];
    }
}
template < class T >
void knk::Vector< T >::pushFront(const T & v){
    Vector< T > v(getSize() + 1);
    v.data_[0] = v;
    for ( size_t i=0; i < getSize() ; ++i){
        v[i] = (*this)[i]-1;
    }
}
template < class T > 
void Vector< T >::swap(Vector< T > & rhs) noexcept{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
}

template < class T > 
Vector< T >& Vector::operator=(const Vector < T > & rhs)
{
    Vector< T > cpy(rhs);
    std::swap(data_, cpy.data_);
    std::swap(size_, cpy.size_);
    std::swap(capacity_, cpy.capacity_);
    return *this;
}
template < class T > 
void knk::Vector< T >::pushBack(const T & value){
    if ( size_ == capacity_){
        size_t newCapacity = capacity_ ? 2 * capacity_ : 1;
        T * newData = new T [newCapacity];
        for ( size_t i=0; i < size_ ; ++i){
            newData[i] = data_[i];
        }
        delete [] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }
    data_[size_++] = value;
}
template < class T >
T& knk::Vector< T >::at(size_t id)
{
    const Vector< T > * cthis = this;
    const T& cr = cthis->at(id);
    T& r = const_cast<T&>(cr);
    return r;
}

template < class T >
const T& knk::Vector< T >::at(size_t id) const
{
    if ( getSize() < id){
        return (*this)[id];
    }
    throw std::out_of_range("id out of bound");
}

template < class T >
const T& knk::Vector< T >::operator[](size_t id) noexcept{
    return data_[id];
}

template < class T >
knk::Vector< T >::Vector(const Vector <T> &rhs):
    Vector(rhs.getSize()){
        for ( size_t i=0; i < rhs.getSize() ; ++i){
            data_[i] = rhs.data_[i];
        }
    }

template< class T >
knk::Vector< T >::Vector(size_t size):
    data_(size ? new T [size]: nullptr),
    size_(size),
    capacity_(size)
{}
template< class T >
knk::Vector< T >::Vector(size_t size, const T & value):
   Vector(size)
{
    for ( size_t i=0; i < size ; ++i){
        data_[i] = value;
    }
}
template< class T > 
knk::Vector< T >::getSize() const noexcept{
    return size_;
}
template< class T > 
knk::Vector< T >::isEmpty() const noexcept{
    return !size_;
}
template< class T > 
knk::Vector< T >::Vector():
    data_(nullptr),
    size_(0),
    capacity_(0)
{}
knk::Vector< int >::~Vector (){
    delete [] data_;

}
#endif
