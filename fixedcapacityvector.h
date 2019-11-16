#ifndef SH_MATH_FIXEDSIZEVECTOR
#define SH_MATH_FIXEDSIZEVECTOR

#include <new>
#include <stdexcept>
#include <utility>

#if (__cplusplus < 201103)
#else
#include <type_traits>
#endif

namespace shMath
{
 template <class Type, std :: size_t Capacity> class fixedCapacityVector
 {
  public:
  typedef Type* pointer;
  typedef Type& reference;
  typedef const Type* const_pointer;
  typedef const Type& const_reference;
  typedef std :: size_t size_type;
  typedef Type value_type;
  explicit vector(size_type n);
  #if (__cplusplus < 201103)
  size_type capacity() const;
  size_type size() const;
  #else
  size_type capacity() const noexcept;
  pointer data() noexcept;
  const_pointer data() const noexcept;
  size_type size() const noexcept;
  #endif
  reference at(size_type n);
  const_reference at(size_type n) const;
  void pop_back();
  void push_back(const value_type& val);
  private:
  std :: size_t Size;
  char Data[sizeof(Type) * Capacity];
 };
}

template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
: Size(n)
{
 Type* first = static_cast<Type*>(Data);
 Type* const last = first + n;
 if (n > Capacity)
 {
  throw std :: bad_alloc();
 }
 for(;first != last;++first)
 {
  new (first) Type();
 }
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: capacity() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: capacity() const noexcept
#endif
{
 return sizeof(Type) * Capacity;
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: pointer shMath :: fixedCapacityVector <Type, Capacity> :: data() noexcept
{
 return static_cast<typename shMath :: fizedCapacityVector <Type, Capacity> :: pointer>(Data);
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_pointer shMath :: fixedCapacityVector <Type, Capacity> :: data() const noexcept
{
 return static_cast<typename shMath :: fixedCapacityVector<Type, Capacity> :: const_pointer>(Data);
}
#endif

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: at(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
{
 if (n < Size)
 {
  return *(static_cast<Type* const>(Data) + n)
 }
 throw std :: out_of_range();
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: at(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const
{
 if (n < Size)
 {
  return *(static_cast<const Type* const>(Data) + n)
 }
 throw std :: out_of_range();
}

template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: pop_back()
{
 --Size;
 (static_cast<Type* const>(Data) + Size)->~Type();
}

template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: push_back(const typename shMath :: fixedCapacityVector <Type, Capacity> :: value_type& val)
{
 if (capacity() == Size)
 {
  throw std :: bad_alloc();
 }
 Type* const address = static_cast<Type* const>(Data) + Size;
 new (address) Type (val);
 ++Size;
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: size() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: size() const noexcept
#endif
{
 return Size;
}
#endif

