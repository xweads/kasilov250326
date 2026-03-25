#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace knk{
template < class T >
struct Vector {
    public:
    Vector()
    ~Vector();
    Vecotr(const Vector <T> &rhs)= delete;
    Vector(size_t size, const T & value );

    Vector < T > & operator=(const Vector <T> & rhs) = delete;
    
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    void pushBack(const T &);
    void popBack();

    private:
    T * data;
    size_t size_, capacity_;
  };
}
template< class T >
knk::Vector< T >::Vector(size_t size, const T & value):
    data_(size ? new T [size]: nullptr),
    size_(0),
    capacity_(size)
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
