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
  void pop_back();
  #else
  typedef Type&& rvalue_reference;
  typedef const Type&& const_rvalue_reference;
  fixedCapacityVector() noexcept;
  fixedCapacityVector(const fixedCapacityVector& a) noexcept(std :: is_nothrow_copy_constructible<Type>{});
  fixedCapacityVector(std :: initializer_list<value_type> list);
  template <std :: size_t AnotherCapacity> fixedCapacityVector(fixedCapacityVector<Type, AnotherCapacity>&& a);
  fixedCapacityVector(fixedCapacityVector&& a) noexcept(std :: is_nothrow_move_constructible<Type>{});
  ~fixedCapacityVector() noexcept(std :: is_nothrow_destructible<Type>{});
  constexpr size_type capacity() const noexcept;
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
  void pop_back() noexcept(std :: is_nothrow_destructible<Type>{});
  void push_back(rvalue_reference val);
  #if (__cpluspluc < 201703)
  bool empty() const noexcept;
  template <class ... Args> void emplace_back(Args&& ... args);
  #else
  template <class ... Args> reference emplace_back(Args&& ... args);
  #if (__cplusplus < 202002)
  bool empty() const noexcept;
  #else
  [[nodiscard]] constexpr bool empty() const noexcept;
  #endif
  #endif
  #endif
  reference at(size_type n);
  const_reference at(size_type n) const;
  void push_back(const value_type& val);
  private:
  void fillN();
  std :: size_t Size;
  #if (__cplusplus < 201103)
  char Data[sizeof(Type) * Capacity];
  #else
  void fillN(std :: integral_constant<bool, false>, std :: integral_constant<bool, false>);
  void fillN(std :: integral_constant<bool, false>, std :: integral_constant<bool, true>);
  void fillN(std :: integral_constant<bool, true>, std :: integral_constant<bool, false>) noexcept;
  void fillN(std :: integral_constant<bool, true>, std :: integral_constant<bool, true>) noexcept;
  typename std :: aligned_storage <sizeof(Type), alignof(Type)> :: type Data[Capacity];
  #endif
 };
}

template <class Type, std :: size_t Capacity> inline shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
: Size(n)
{
 if (Size > Capacity)
 {
  throw std :: bad_alloc();
 }
 #if (__cplusplus < 201103)
 fillN();
 #else
 fillN(std :: is_nothrow_default_constructible<Type>{}, std :: is_nothrow_destructible<Type>{});
 #endif
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
 if (Size > Capacity)
 {
  throw std :: bad_alloc();
 }
 std :: uninitialized_copy(a.begin(), a.end(), dataFirst);
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(const shMath :: fixedCapacityVector<Type, Capacity>& a)
#else
template <class Type, std :: size_t Capacity> shMath :: fixedCapacityVector <Type, Capacity> :: fixedCapacityVector(const shMath :: fixedCapacityVector<Type, Capacity>& a) noexcept(std :: is_nothrow_copy_constructible<Type>{})
#endif
:Size(a.Size)
{
 Type* const dataFirst = reinterpret_cast<Type*>(Data);
 std :: uninitialized_copy(a.begin(), a.end(), dataFirst);
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
  #if (__cplusplus < 201703)
  new (dataFirst) Type(std :: move(*first));
  #else
  new (dataFirst) Type(std :: move(*std :: launder(first)));
  #endif
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
  #if (__cplusplus < 201703)
  new (dataFirst) Type(std :: move(*first));
  #else
  new (dataFirst) Type(std :: move(*std :: launder(first)));
  #endif
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
template <class Type, std :: size_t Capacity> inline shMath :: fixedCapacityVector <Type, Capacity> :: ~fixedCapacityVector()
#else
template <class Type, std :: size_t Capacity> inline shMath :: fixedCapacityVector <Type, Capacity> :: ~fixedCapacityVector() noexcept(std :: is_nothrow_destructible<Type>{})
#endif
{
 clear();
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: capacity() const
#else
template <class Type, std :: size_t Capacity> constexpr inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: capacity() const noexcept
#endif
{
 return Capacity;
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: pointer shMath :: fixedCapacityVector <Type, Capacity> :: data() noexcept
{
 #if (__cplusplus < 201703)
 return reinterpret_cast<typename shMath :: fixedCapacityVector <Type, Capacity> :: pointer>(Data);
 #else
 return std :: launder(reinterpret_cast<typename shMath :: fixedCapacityVector <Type, Capacity> :: pointer>(Data));
 #endif
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_pointer shMath :: fixedCapacityVector <Type, Capacity> :: data() const noexcept
{
 #if (__cplusplus < 201703)
 return reinterpret_cast<typename shMath :: fixedCapacityVector<Type, Capacity> :: const_pointer>(Data);
 #else
 return std :: launder(reinterpret_cast<typename shMath :: fixedCapacityVector<Type, Capacity> :: const_pointer>(Data));
 #endif
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
 #if (__cplusplus < 201703)
 return *(reinterpret_cast<Type* const>(Data) + n);
 #else
 return *std :: launder(reinterpret_cast<Type* const>(Data) + n);
 #endif
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: operator [] (typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: operator [] (typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const noexcept
#endif
{
 #if (__cplusplus < 201703)
 return *(reinterpret_cast<const Type* const>(Data) + n);
 #else
 return *std :: launder(reinterpret_cast<const Type* const>(Data) + n);
 #endif
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: front()
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: front() & noexcept
#endif
{
 #if (__cplusplus < 201703)
 return *(reinterpret_cast<Type* const>(Data));
 #else
 return *std :: launder(reinterpret_cast<Type* const>(Data));
 #endif
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() const & noexcept
#endif
{
 #if (__cplusplus < 201703)
 return *(reinterpret_cast<const Type* const>(Data));
 #else
 return *std :: launder(reinterpret_cast<const Type* const>(Data));
 #endif
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() && noexcept
{
 #if (__cplusplus < 201703)
 return std :: move(*(reinterpret_cast<Type* const>(Data)));
 #else
 return std :: move(*std :: launder(reinterpret_cast<Type* const>(Data)));
 #endif
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: front() const && noexcept
{
 #if (__cplusplus < 201703)
 return std :: move(*(reinterpret_cast<const Type* const>(Data)));
 #else
 return std :: move(*std :: launder(reinterpret_cast<const Type* const>(Data)));
 #endif
}
#endif

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: back()
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: back() & noexcept
#endif
{
 #if (__cplusplus < 201703)
 return *(reinterpret_cast<Type* const>(Data) + Size - 1u);
 #else
 return *std :: launder(reinterpret_cast<Type* const>(Data) + Size - 1u);
 #endif
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() const & noexcept
#endif
{
 #if (__cplusplus < 201703)
 return *(reinterpret_cast<const Type* const>(Data) + Size - 1u);
 #else
 return *std :: launder(reinterpret_cast<const Type* const>(Data) + Size - 1u);
 #endif
}

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() && noexcept
{
 #if (__cplusplus < 201703)
 return std :: move(*(reinterpret_cast<Type* const>(Data) + Size - 1u));
 #else
 return std :: move(*std :: launder(reinterpret_cast<Type* const>(Data) + Size - 1u));
 #endif
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_rvalue_reference shMath :: fixedCapacityVector <Type, Capacity> :: back() const && noexcept
{
 #if (__cplusplus < 201703)
 return std :: move(*(reinterpret_cast<const Type* const>(Data) + Size - 1u));
 #else
 return std :: move(*std :: launder(reinterpret_cast<const Type* const>(Data) + Size - 1u));
 #endif
}
#endif

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: at(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n)
{
 if (n < Size)
 {
  #if (__cplusplus < 201703)
  return *(reinterpret_cast<Type* const>(Data) + n);
  #else
  return *std :: launder(reinterpret_cast<Type* const>(Data) + n);
  #endif
 }
 throw std :: out_of_range("Index out of range.");
}

template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: const_reference shMath :: fixedCapacityVector <Type, Capacity> :: at(typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type n) const
{
 if (n < Size)
 {
  #if (__cplusplus < 201703)
  return *(reinterpret_cast<const Type* const>(Data) + n);
  #else
  return *std :: launder(reinterpret_cast<const Type* const>(Data) + n);
  #endif
 }
 throw std :: out_of_range("Index out of range.");
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: pop_back()
#else
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: pop_back() noexcept(std :: is_nothrow_destructible<Type>{})
#endif
{
 #if (__cplusplus < 201703)
 (reinterpret_cast<Type* const>(Data) + Size - 1u)->~Type();
 #else
 std :: launder(reinterpret_cast<Type* const>(Data) + Size - 1u)->~Type();
 #endif
 --Size;
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
#else
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: push_back(typename shMath :: fixedCapacityVector <Type, Capacity> :: rvalue_reference val)
{
 if (capacity() == Size)
 {
  throw std :: bad_alloc();
 }
 Type* const address = reinterpret_cast<Type* const>(Data) + Size;
 new (address) Type (std :: forward<Type>(val));
 ++Size;
}
#endif

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: size() const
#else
template <class Type, std :: size_t Capacity> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: size_type shMath :: fixedCapacityVector <Type, Capacity> :: size() const noexcept
#endif
{
 return Size;
}

#if (__cplusplus < 201103)
template <class Type, std :: size_t Capacity> void shMath :: fixedCapacityVector <Type, Capacity> :: clear()
#else
template <class Type, std :: size_t Capacity> void shMath :: fixedCapacityVector <Type, Capacity> :: clear() noexcept(std :: is_nothrow_destructible<Type>{})
#endif
{
 while (Size != 0u) pop_back();
}

template <class Type, std :: size_t Capacity> void shMath :: fixedCapacityVector <Type, Capacity> :: fillN()
{
 Type* first = reinterpret_cast<Type*>(Data);
 Type* const last = first + Size;
 try
 {
  for(;first != last;++first) new (first) Type();
 }
 catch(...)
 {
  Size = std :: distance(reinterpret_cast<Type* const>(Data), first);
  for(;Size != 0u;--Size)
  {
   try
   {
    #if (__cplusplus < 201703)
    (--first)->~Type();
    #else
    std :: launder(--first)->~Type();
    #endif
   }
   catch(...)
   {
    return; //Nothing better could be done, just pretend everything is ok.
   }
  }
  throw;
 }
}

#if (__cplusplus < 201103)
#else
#if (__cplusplus < 201703)
template <class Type, std :: size_t Capacity> template <class ... Args> inline void shMath :: fixedCapacityVector <Type, Capacity> :: emplace_back(Args&& ... args)
#else
template <class Type, std :: size_t Capacity> template <class ... Args> inline typename shMath :: fixedCapacityVector <Type, Capacity> :: reference shMath :: fixedCapacityVector <Type, Capacity> :: emplace_back(Args&& ... args)
#endif
{
 if (capacity() == Size)
 {
  throw std :: bad_alloc();
 }
 Type* const address = reinterpret_cast<Type* const>(Data) + Size;
 new (address) Type (std :: forward<Args>(args)...);
 ++Size;
 #if (__cplusplus < 201703)
 #else
 return *std :: launder(address);
 #endif
}
#endif

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: fillN(std :: integral_constant<bool, false>, std :: integral_constant<bool, false>)
{
 fillN();
}
#endif

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: fillN(std :: integral_constant<bool, false>, std :: integral_constant<bool, true>)
{
 #if (__cplusplus < 201703)
 Type* first = reinterpret_cast<Type*>(Data);
 Type* const last = first + Size;
 try
 {
  for(;first != last;++first) new (first) Type();
 }
 catch(...)
 {
  Type* const Begin = reinterpret_cast<Type* const>(Data);
  while(first != Begin) (--first)->~Type();
  throw;
 }
 #else
 Type* const first = std :: launder(reinterpret_cast<Type* const>(Data));
 std :: uninitialized_default_construct_n(first, Size);
 #endif
}
#endif

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: fillN(std :: integral_constant<bool, true>, std :: integral_constant<bool, false>) noexcept
{
 #if (__cplusplus < 201703)
 Type* first = reinterpret_cast<Type*>(Data);
 Type* const last = first + Size;
 while(first != last) new (first++) Type();
 #else
 Type* const first = std :: launder(reinterpret_cast<Type* const>(Data));
 std :: uninitialized_default_construct_n(first, Size);
 #endif
}
#endif

#if (__cplusplus < 201103)
#else
template <class Type, std :: size_t Capacity> inline void shMath :: fixedCapacityVector <Type, Capacity> :: fillN(std :: integral_constant<bool, true>, std :: integral_constant<bool, true>) noexcept
{
 fillN(std :: integral_constant<bool, true>{}, std :: integral_constant<bool, false>{});
}
#endif
#endif

