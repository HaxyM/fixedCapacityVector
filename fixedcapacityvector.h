#ifndef SH_MATH_FIXEDSIZEVECTOR
#define SH_MATH_FIXEDSIZEVECTOR

#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

#if (__cplusplus < 201103)
#else
#include <initializer_list>
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
  explicit fixedCapacityVector(size_type n);
  fixedCapacityVector(size_type n, const value_type& value);
  template <class InputIterator> fixedCapacityVector(InputIterator first, InputIterator last);
  template <std :: size_t AnotherCapacity> fixedCapacityVector(const fixedCapacityVector<Type, AnotherCapacity>& a);
  #if (__cplusplus < 201103)
  fixedCapacityVector();
  fixedCapacityVector(const fixedCapacityVector& a);
  ~fixedCapacityVector();
  size_type capacity() const;
  bool empty() const;
  size_type size() const;
  reference operator [] (size_type n);
  const_reference operator [] (size_type n) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  void clear();
  #else
  #if (__cplusplus < 202002)
  bool empty() const noexcept;
  #else
  [[nodiscard]] constexpr bool empty() const noexcept;
  #endif
  typedef Type&& rvalue_reference;
  typedef const Type&& const_rvalue_reference;
  fixedCapacityVector() noexcept;
  fixedCapacityVector(const fixedCapacityVector& a) noexcept(std :: is_nothrow_copy_constructible<Type>{});
  fixedCapacityVector(std :: initializer_list<value_type> list);
  template <std :: size_t AnotherCapacity> fixedCapacityVector(fixedCapacityVector<Type, AnotherCapacity>&& a);
  fixedCapacityVector(fixedCapacityVector&& a) noexcept(std :: is_nothrow_move_constructible<Type>{});
  ~fixedCapacityVector() noexcept(std :: is_nothrow_destructible<Type>{});
  size_type capacity() const noexcept;
  pointer data() noexcept;
  const_pointer data() const noexcept;
  size_type size() const noexcept;
  reference operator [] (size_type n) noexcept;
  const_reference operator [] (size_type n) const noexcept;
  reference front() & noexcept;
  const_reference front() const & noexcept;
  rvalue_reference front() && noexcept;
  const_rvalue_reference front() const && noexcept;
  reference back() & noexcept;
  const_reference back() const & noexcept;
  rvalue_reference back() && noexcept;
  const_rvalue_reference back() const && noexcept;
  void clear() noexcept(std :: is_nothrow_destructible<Type>{});
  #endif
  reference at(size_type n);
  const_reference at(size_type n) const;
  void pop_back();
  void push_back(const value_type& val);
  private:
  std :: size_t Size;
  #if (__cplusplus < 201103)
  char Data[sizeof(Type) * Capacity];
  #else
  typename std :: aligned_storage <sizeof(Type), alignof(Type)> :: type Data[Capacity];
  #endif
 };
}

template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
: Size(n)
{
 Type* first = reinterpret_cast<Type*>(Data);
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

template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n, const typename shMath :: fixedCapacityVector <Type, Capacity> :: value_type& value)
: Size(n)
{
 Type* const first = reinterpret_cast<Type*>(Data);
 Type* const last = first + n;
 if (n > Capacity)
 {
  throw std :: bad_alloc();
 }
 std :: uninitialized_fill(first, last, value);
}

template <class Type, std :: size_t Capacity> template <class InputIterator> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(InputIterator first, InputIterator last)
: Size(reinterpret_cast<std :: size_t>(std :: distance(first, last)))
{
 Type* const dataFirst = reinterpret_cast<Type*>(Data);
 if (Size > Capacity)
 {
  throw std :: bad_alloc();
 }
 std :: uninitialized_copy(first, last, dataFirst);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector()
#else
template <class Type, std :: size_t Capacity> inline shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector() noexcept
#endif
: Size(0u)
{
}

template <class Type, std :: size_t Capacity> template <std :: size_t AnotherCapacity> shMath :: fixedCapacityVector<Type, Capacity> :: fixedCapacityVector(const fixedCapacityVector<Type, AnotherCapacity>& a)
: Size(a.Size)
{
 Type* const dataFirst = reinterpret_cast<Type*>(Data);
 Type* const first = reinterpret_cast<Type*>(a.Data);
 Type* const last = first + Size;
 if (Size > Capacity)
 {
  throw std :: bad_alloc();
 }
 std :: uninitialized_copy(first, last, dataFirst);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(const shMath :: fixedCapacityVector<Type, Capacity>& a)
#else
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(const shMath :: fixedCapacityVector<Type, Capacity>& a) noexcept(std :: is_nothrow_copy_constructible<Type>{})
#endif
:Size(a.Size)
{
 Type* const dataFirst = reinterpret_cast<Type*>(Data);
 Type* const first = reinterpret_cast<Type*>(a.Data);
 Type* const last = first + Size;
 std :: uninitialized_copy(first, last, dataFirst);
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> template <std :: size_t AnotherCapacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(shMath :: fixedCapacityVector<Type, AnotherCapacity>&& a)
: Size(a.Size)
{
 Type* dataFirst = reinterpret_cast<Type*>(Data);
 Type* const dataLast = dataFirst + Size;
 Type* first = reinterpret_cast<Type*>(a.Data);
 if (Size > Capacity)
 {
  throw std :: bad_alloc();
 }
 for(;dataFirst != dataLast;++dataFirst,++first)
 {
  new (dataFirst) Type(std :: move(*first));
 }
}
#endif

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(shMath :: fixedCapacityVector<Type, Capacity>&& a) noexcept(std :: is_nothrow_move_constructible<Type>{})
: Size(a.Size)
{
 Type* dataFirst = reinterpret_cast<Type*>(Data);
 Type* const dataLast = dataFirst + Size;
 Type* first = reinterpret_cast<Type*>(a.Data);
 for(;dataFirst != dataLast;++dataFirst,++first)
 {
  new (dataFirst) Type(std :: move(*first));
 }
}
#endif

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(std :: initializer_list<typename shMath :: fixedCapacityVector <Type, Capacity> :: value_type> list)
: Size(list.size())
{
 Type* const dataFirst = reinterpret_cast<Type*>(Data);
 typename std :: initializer_list <typename shMath :: fixedCapacityVector <Type, Capacity> :: value_type> :: const_iterator first = list.begin();
 const typename std :: initializer_list <typename shMath :: fixedCapacityVector <Type, Capacity> :: value_type> :: const_iterator last = list.end();
 if (list.size() > Capacity)
 {
  throw std :: bad_alloc();
 }
 std :: uninitialized_copy(first, last, dataFirst);
}
#endif

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: ~fixedCapacityVector()
#else
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: ~fixedCapacityVector() noexcept(std :: is_nothrow_destructible<Type>{})
#endif
{
 Type* dataFirst = reinterpret_cast<Type*>(Data);
 Type* const dataLast = dataFirst + Size;
 for(;dataFirst != dataLast;++dataFirst)
 {
  dataFirst->~Type();
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
 return reinterpret_cast<typename shMath :: fixedCapacityVector <Type, Capacity> :: pointer>(Data);
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_pointer shMath :: fixedCapacityVector <Type, Capacity> :: data() const noexcept
{
 return reinterpret_cast<typename shMath :: fixedCapacityVector<Type, Capacity> :: const_pointer>(Data);
}
#endif

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline bool shMath :: fixedCapacityVector <Type, Capacity> :: empty() const
#else
#if (__cplusplus < 202002)
template <class Type, std :: size_t Capacity> inline bool shMath :: fixedCapacityVector <Type, Capacity> :: empty() const noexcept
#else
template <class Type, std :: size_t Capacity> [[nodiscard]] inline constexpr bool shMath :: fixedCapacityVector <Type, Capacity> :: empty() const noexcept
#endif
#endif
{
 return (Size == 0u);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: operator [] (typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: operator [] (typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) noexcept
#endif
{
 return *(reinterpret_cast<Type* const>(Data) + n);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: operator [] (typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: operator [] (typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const noexcept
#endif
{
 return *(reinterpret_cast<const Type* const>(Data) + n);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: front()
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: front() & noexcept
#endif
{
 return *(reinterpret_cast<Type* const>(Data));
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() const & noexcept
#endif
{
 return *(reinterpret_cast<const Type* const>(Data));
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() && noexcept
{
 return std :: move(*(reinterpret_cast<Type* const>(Data)));
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() const && noexcept
{
 return std :: move(*(reinterpret_cast<const Type* const>(Data)));
}
#endif

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: back()
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: back() & noexcept
#endif
{
 return *(reinterpret_cast<Type* const>(Data) + Size - 1u);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() const & noexcept
#endif
{
 return *(reinterpret_cast<const Type* const>(Data) + Size - 1u);
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() && noexcept
{
 return std :: move(*(reinterpret_cast<Type* const>(Data) + Size - 1u));
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() const && noexcept
{
 return std :: move(*(reinterpret_cast<const Type* const>(Data) + Size - 1u));
}
#endif

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: at(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
{
 if (n < Size)
 {
  return *(reinterpret_cast<Type* const>(Data) + n);
 }
 throw std :: out_of_range("Index out of range.");
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: at(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const
{
 if (n < Size)
 {
  return *(reinterpret_cast<const Type* const>(Data) + n);
 }
 throw std :: out_of_range("Index out of range.");
}

template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: pop_back()
{
 --Size;
 (reinterpret_cast<Type* const>(Data) + Size)->~Type();
}

template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: push_back(const typename shMath :: fixedCapacityVector <Type, Capacity> :: value_type& val)
{
 if (capacity() == Size)
 {
  throw std :: bad_alloc();
 }
 Type* const address = reinterpret_cast<Type* const>(Data) + Size;
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

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> void shMath :: fixedCapacityVector <Type, Capacity> :: clear()
#else
template <class Type, std :: size_t Capacity> void shMath :: fixedCapacityVector <Type, Capacity> :: clear() noexcept(std :: is_nothrow_destructible<Type>{})
#endif
{
 Type* last = reinterpret_cast<Type*>(Data) + Size - 1u;
 for(;Size != 0u;--Size,--last)
 {
  last->~Type();
 }
}

