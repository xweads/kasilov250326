#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace knk{
template < class T >
struct Vector {
    public:
    Vector()
    ~Vector();

    bool isEmpty() const noexcept;

    private:
    T * data;
    size_t size_, capacity_;
  };
}
template< class T > 
knk::Vector< T >::isEmpty() const noexcept{
    return false;
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
