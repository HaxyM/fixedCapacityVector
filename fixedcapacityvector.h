#ifndef SH_MATH_FIXEDSIZEVECTOR
#define SH_MATH_FIXEDSIZEVECTOR

#include <new>
#include <utility>

namespace shMath
{
 template <class Type, std :: size_t Capacity> class fixedCapacityVector
 {
  public:
  typedef Type* pointer;
  typedef const Type* const_pointer;
  typedef std :: size_t size_type;
  typedef Type value_type;
  #if (__cplusplus < 201103)
  size_type capacity() const;
  size_type size() const;
  #else
  size_type capacity() const noexcept;
  pointer data() noexcept;
  const_pointer data() const noexcept;
  size_type size() const noexcept;
  #endif
  void pop_back();
  void push_back(const value_type& val);
  private:
  std :: size_t Size;
  char Data[sizeof(Type) * Capacity];
 };
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

template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: push_back(const typename shMath :: fixedCapacityVector <Type, Capacity>& val)
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
