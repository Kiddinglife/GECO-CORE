/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company SGI_STL
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for SGI_STL purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Comp SGI_STL makes no
 * representations about the suitability of this software for SGI_STL
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * Copyright (c) 1997
 * Silicon Graphics
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for SGI_STL purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for SGI_STL
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * Copyright (c) 2016
 * Geco Gaming Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for GECO purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  GECO makes no representations about
 * the suitability of this software for GECO purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

/*
 * geco-algo-base.h
 *
 *  Created on: 18 Mar 2016
 *      Author: jakez
 */

// @Caution when copying non-trivial-assignment-opt-types,
// copy() will call user-customiszed assign operator implementation
// where user may have a ptr member and copy data
#ifndef INCLUDE_GECO_DS_ALGO_BASE_H_
#define INCLUDE_GECO_DS_ALGO_BASE_H_

#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstddef>
#include <new>

#include "geco-ds-pair.h"
#include "geco-ds-iter.h"
#include "geco-ds-iter-base.h"
#include "geco-ds-type-traitor.h"

#ifdef GECO_USE_NEW_IOSTREAMS
#include <iosfwd>
#else /* STL_USE_NEW_IOSTREAMS */
#include <iostream>
#endif /* STL_USE_NEW_IOSTREAMS */

GECO_BEGIN_NAMESPACE

#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x540 /* C++ Builder 4.0 */
#undef min
#undef max
template<class Type>
inline const Type& min(const Type& a, const Type& b)
{
    GECO_REQUIRES(a, b);
    return b < a ? b : a;
}
template<class Type>
inline const Type& max(const Type& a, const Type& b)
{
    GECO_REQUIRES(ValueType, _LessThanComparable);
    return a < b ? b : a;
}
#else
template<class ValueType, class _Compare>
inline const ValueType& min(const ValueType& __a, const ValueType& __b, _Compare __comp)
{
    return __comp(__b, __a) ? __b : __a;
}
template<class ValueType, class _Compare>
inline const ValueType& max(const ValueType& __a, const ValueType& __b, _Compare __comp)
{
    return __comp(__a, __b) ? __b : __a;
}
#endif

// swap and iter swap
// 第三个参数为什么为指针参见<stl_iterator.h>
template <class ForwardIter1, class ForwardIter2, class Type>
inline void
iter_swap_aux1(ForwardIter1 a, ForwardIter2 b, Type*)
{
    // swap the value type
    Type tmp = *a;
    *a = *b;
    *b = tmp;
}

template<class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 a, ForwardIter2 b)
{
    GECO_REQUIRES(ForwardIter1, Mutable_ForwardIterator);
    GECO_REQUIRES(ForwardIter2, Mutable_ForwardIterator);
    GECO_CONVERTIBLE(typename iterator_traitor<ForwardIter1>::value_type,
        typename iterator_traitor<ForwardIter2>::value_type);
    GECO_CONVERTIBLE(typename iterator_traitor<ForwardIter2>::value_type,
        typename iterator_traitor<ForwardIter1>::value_type);
    iter_swap_aux1(a, b, GET_VALUE_TYPE(a));
}

// use opt=() to swap value
template<class Type>
inline void swap(Type& a, Type& b)
{
    GECO_REQUIRES(ValueType, _Assignable);
    Type tmp = a;
    a = b;
    b = tmp;
}

// two purposes
// (1) Replace calls to copy with memmove whenever possible.
// (Memmove, not memcpy,because the input and output ranges
// are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count, faster because save iterator comparsion

template<class InputIter, class OutputIter, class Distance>
inline OutputIter
copy_aux3(InputIter first, InputIter last, OutputIter result,
input_iterator_tag, Distance*)
{
    // first != last导致要进行迭代器的比较, 效率低
    for (; first != last; ++result, ++first)
    {
        *result = *first;
    }
    return result;
}

template<class RandomAccessIter, class OutputIter, class Distance>
inline OutputIter
copy_aux3(RandomAccessIter first, RandomAccessIter last, OutputIter result,
random_access_iterator_tag, Distance*)
{
    // 不进行迭代器间的比较, 直接指定循环次数, 高效
    for (Distance n = last - first; n > 0; --n)
    {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

// @Remember just record a query that cofused me a bit
// why the two copy_aux3() above does not use memmove() to copy trivial types for highest efficiency?
// I once thought they should use  memmove() because we can get the value_type raw pointer formate
// by dereferencing iterator like (&*iter). Actually I was wrong because memove() only works on
// for continusous memory copy, For example:
// vector can use memmove() to copy trivial types for highest efficiency by deferencing elements
// or we can still use one-by-one-copy because memove() copy one byte after another, which may not be
// be fastr than assignment-copy eg. long long value type. so the only case where memmove() is faster
// than assign-opt-copy is vector contains raw byte blocks or chars
// like vector<char[256]> char_blocks; OR vector<char> chars;
// But for list with trivial value type, we have to use iterator to go through each element and copy value
// by assignment '=', just like the above two copy_aux3() functions do.
template <class Type>
inline Type*
copy_aux3(const Type* start, const Type* end, Type* dest)
{
    memmove(dest, start, sizeof(Type)*(end - start));
    return dest + (end - start);
}

// tmpl function partial order is used for the RAW POINTER VALUE
#if defined(GECO_FUNCTION_TMPL_PARTIAL_ORDER)
// even through it is non_trivial_assign_opt, it does matter,
// because we reply on user-defined-assig-opt implementation when assigning it in aux3
template <class InputIter, class OutputIter>
inline OutputIter
copy_aux2(InputIter start, InputIter end, OutputIter dest,
false_type non_trivial_assign_opt)
{
    return copy_aux3(start, end, dest,
        GET_ITER_CATEGORY(start),
        GET_DISTANCE_TYPE(start));
}

template <class InputIter, class OutputIter>
inline OutputIter
copy_aux2(InputIter start, InputIter end, OutputIter dest,
true_type trivial_assign_opt)
{
    return copy_aux3(start, end, dest,
        GET_ITER_CATEGORY(start),
        GET_DISTANCE_TYPE(start));
}

// partial order for raw pointer
#ifndef __USLC__
template <class Type>
inline Type* copy_aux2(Type* start, Type* end, Type* dest,
    true_type trivial_assign_opt)
{
    return copy_aux3(start, end, dest);
}
#endif

template <class Type>
inline Type* copy_aux2(const Type* start, const Type* end, Type* dest,
    true_type trivial_assign_opt)
{
    return copy_aux3(start, end, dest);
}

template <class InputIter, class OutputIter, class Type>
inline OutputIter
copy_aux1(InputIter start, InputIter end, OutputIter dest, Type* valtype)
{
    typedef typename type_traitor<Type>::has_trivial_assign_opt opt;
    return copy_aux2(start, end, dest, opt());
}
template <class InputIter, class OutputIter>
inline OutputIter
copy(InputIter start, InputIter end, OutputIter dest)
{
    GECO_REQUIRES(InputIter, OutputIter);
    GECO_REQUIRES(OutputIter, OutputIter);
    return copy_aux1(start, end, dest, GET_VALUE_TYPE(start));
}
#elif defined(GECO_CLASS_PARTIAL_SPECIALIZATION)
template <class InputIter, class OutputIter, class has_trivial_assign_opt_type>
struct copy_dispatcher
{
    static OutputIter copy(InputIter start, InputIter end, OutputIter dest)
    {
        return copy_aux3(start, end,dest, GET_ITER_CATEGORY(start), GET_DISTANCE_TYPE(start));
    }
};

template <class ValueType>
struct copy_dispatcher<ValueType*, ValueType*, true_type>
{
    static ValueType* copy(const ValueType* start, const ValueType* end, ValueType* dest)
    {
        return copy_aux3(start, end, dest);
    }
};

template <class ValueType>
struct copy_dispatcher<const ValueType*, ValueType*, true_type>
{
    static ValueType* copy(const ValueType* start, const ValueType* end, ValueType* dest)
    {
        return copy_aux3(start, end, dest);
    }
};

template <class InputIter, class OutputIter>
inline OutputIter
copy(InputIter start, InputIter end,OutputIter dest)
{
    GECO_REQUIRES(InputIter, _InputIterator);
    GECO_REQUIRES(OutputIter, _OutputIterator);
    typedef typename iterator_traitor<InputIter>::value_type value_type_;
    typedef typename type_traitor<value_type_>::has_trivial_assign_opt assign_opt_;
    typedef typename copy_dispatcher<InputIter, OutputIter, assign_opt_> copy_dispatcher_;
    return copy_dispatcher_::copy(start, end, dest);
}
#else
// fallback for compilers with neither func partial ordering nor partial specialization.
// in order to define faster version of copy() for the basic builtin types using full specialization
// full specialization is supported by all compilers
template<class InputIter, class OutputIter>
inline OutputIter
copy(InputIter start, InputIter end,OutputIter dest)
{
    return copy_aux3(start, end,dest,
        GET_ITER_CATEGORY(start),
        GET_DISTANCE_TYPE(start));
}

#define delc_memmove_copy(ValueType)                                \
  inline ValueType* copy(const ValueType* start, const ValueType* end, ValueType* dest) { \
    memmove(dest, start, sizeof(ValueType) * (end - start));          \
    return dest + (end - start);                                  \
  }

delc_memmove_copy(char)
delc_memmove_copy(signed char)
delc_memmove_copy(unsigned char)
delc_memmove_copy(short)
delc_memmove_copy(unsigned short)
delc_memmove_copy(int)
delc_memmove_copy(unsigned int)
delc_memmove_copy(long)
delc_memmove_copy(unsigned long)
#ifdef GECO_HAS_WCHAR_T
delc_memmove_copy(wchar_t)
#endif
#ifdef GECO_HAS_LONG_LONG
delc_memmove_copy(long long)
delc_memmove_copy(unsigned long long)
#endif
delc_memmove_copy(float)
delc_memmove_copy(double)
delc_memmove_copy(long double)
#endif

//--------------------------------------------------
// copy_backward 从后往前拷贝 similar to copy will not expalin it again
template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
inline BidirectionalIter2
copy_backward_aux3(BidirectionalIter1 start, BidirectionalIter1 end,
BidirectionalIter2 dest, bidirectional_iterator_tag, Distance*)
{
    while (start != end)
    {
        *--dest = *--end;
    }
    return dest;
}

template <class RandomAccessIter, class BidirectionalIter, class Distance>
inline BidirectionalIter
copy_backward_aux3(RandomAccessIter start, RandomAccessIter end,
BidirectionalIter dest, random_access_iterator_tag, Distance*)
{
    for (Distance n = end - start; n > 0; --n)
    {
        *--dest = *--end;
    }
    return dest;
}
template <class Type>
inline Type*
copy_backward_aux3(const Type* start, const Type* end, Type* dest)
{
    const ptrdiff_t _Num = end - start;
    memmove(dest - _Num, start, sizeof(Type) * _Num);
    return dest - _Num;
}

#ifdef GECO_FUNCTION_TMPL_PARTIAL_ORDER
template<class BidirectionalIter1, class BidirectionalIter2>
inline BidirectionalIter1
copy_backward_aux2(BidirectionalIter1 start, BidirectionalIter1 end,
BidirectionalIter2 dest, false_type not_trivial_type)
{
    return copy_backward_aux3(start, end, dest,
        GET_ITER_CATEGORY(start), GET_DISTANCE_TYPE(start));
}
template<class BidirectionalIter1, class BidirectionalIter2>
inline BidirectionalIter1
copy_backward_aux2(BidirectionalIter1 start, BidirectionalIter1 end,
BidirectionalIter2 dest, true_type trivial_type)
{
    return copy_backward_aux3(start, end, dest,
        GET_ITER_CATEGORY(start), GET_DISTANCE_TYPE(start));
}
template<class Type>
Type* copy_backward_aux2(const Type* start, const Type* end,
    Type* dest, true_type trivial_type)
{
    return copy_backward_aux3(start, end, dest);
}

#ifndef __USLC__
template<class Type>
Type* copy_backward_aux2(Type* start, Type* end,
    Type* dest, true_type trivial_type)
{
    return copy_backward_aux3(start, end, dest);
}
#endif

template<class BidirectionalIter1, class BidirectionalIter2, class Type>
inline BidirectionalIter1
copy_backward_aux1(BidirectionalIter1 start, BidirectionalIter1 end,
BidirectionalIter2 dest, Type* value_type_)
{
    typedef typename type_traitor<Type>::has_trivial_assign_opt assopt;
    return copy_backward_aux2(start, end, dest, assopt());
}
template<class BidirectionalIter1, class BidirectionalIter2>
inline BidirectionalIter1
copy_backward(BidirectionalIter1 start, BidirectionalIter1 end,
BidirectionalIter2 dest)
{
    return copy_backward_aux1(start, end, dest, GET_VALUE_TYPE(start));
}
#elif defined(GECO_CLASS_PARTIAL_SPECIALIZATION)
// This dispatch class is a workaround for compilers that do not
// have partial ordering of function templates.  All we're doing is
// creating a specialization so that we can turn a call to copy_backward
// into a memmove whenever possible.
template<class BidirectionalIter1, class BidirectionalIter2, class trivial_value_type>
struct copy_backward_dispatcher
{
    typedef typename iterator_traitor<BidirectionalIter1>::iterator_category Cat;
    typedef typename iterator_traitor<BidirectionalIter1>::difference_type Distance;

    static BidirectionalIter2 copy(BidirectionalIter1 first,
        BidirectionalIter1 last, BidirectionalIter2 result)
    {
        return copy_backward_aux3(first, last, result, Cat(),(Distance*) 0);
    }
};
template<class Type>
struct copy_backward_dispatcher<Type*, Type*, true_type>
{
    static Type* copy(const Type* start, const Type* end, Type* dest)
    {
        const ptrdiff_t _Num = end - start;
        memmove(dest - _Num, start, sizeof(Type) * _Num);
        return dest - _Num;
    }
};

template<class ValueType>
struct copy_backward_dispatcher<const ValueType*, ValueType*, true_type>
{
    static ValueType* copy(const ValueType* start, const ValueType* end, ValueType* dest)
    {
        typedef typename copy_backward_dispatcher<ValueType*, ValueType*, true_type> cbd;
        return cbd::copy(start, end, dest);
    }
};
template<class BI1, class BI2>
inline BI2 copy_backward(BI1 start, BI1 end, BI2 dest)
{
    GECO_REQUIRES(BI1, _BidirectionalIterator);
    GECO_REQUIRES(BI2, _Mutable_BidirectionalIterator);
    GECO_CONVERTIBLE(typename iterator_traitor<BI1>::value_type,typename iterator_traitor<BI2>::value_type);
    typedef typename type_traitor<typename iterator_traitor<BI2>::value_type>::has_trivial_assignment_operator _Trivial;
    return copy_backward_dispatcher<BI1, BI2, _Trivial>::copy(start, end,dest);
}
#else
// compiler firstly try to find a matched function from common functions copy_backward,
// if not found, it will then use template-version-one
template <class BI1, class BI2>
inline BI2
copy_backward(BI1 start, BI1 end, BI2 dest)
{
    return copy_backward_aux3(start, end, dest,
        GET_ITER_CATEGORY(start), GET_DISTANCE_TYPE(start));
}
#define delc_memmove_copy_backward(ValueType)                                \
  inline ValueType* copy_backward(const ValueType* start, const ValueType* end, ValueType* dest) { \
    const ptrdiff_t _Num = end - start;\
    memmove(dest - _Num, start, sizeof(ValueType) * _Num);\
    return dest - _Num;                              \
  }

delc_memmove_copy_backward(char)
delc_memmove_copy_backward(signed char)
delc_memmove_copy_backward(unsigned char)
delc_memmove_copy_backward(short)
delc_memmove_copy_backward(unsigned short)
delc_memmove_copy_backward(int)
delc_memmove_copy_backward(unsigned int)
delc_memmove_copy_backward(long)
delc_memmove_copy_backward(unsigned long)
#ifdef GECO_HAS_WCHAR_T
delc_memmove_copy_backward(wchar_t)
#endif
#ifdef GECO_HAS_LONG_LONG
delc_memmove_copy_backward(long long)
delc_memmove_copy_backward(unsigned long long)
#endif
delc_memmove_copy_backward(float)
delc_memmove_copy_backward(double)
delc_memmove_copy_backward(long double)
#endif

//--------------------------------------------------
// copy_n (not part of the C++ standard)
template<class InputIter, class Size, class OutputIter>
pair<InputIter, OutputIter>
copy_n_aux2(InputIter start, Size count,
OutputIter dest, input_iterator_tag)
{
    for (; count > 0; --count)
    {
        *dest = *start;
        ++start;
        ++dest;
    }
    return pair<InputIter, OutputIter>(start, dest);
}
template<class _RAIter, class Size, class OutputIter>
inline pair<_RAIter, OutputIter>
copy_n_aux2(_RAIter start, Size count,
OutputIter dest, random_access_iterator_tag)
{
    _RAIter end = start + count;
    return pair<_RAIter, OutputIter>(end, copy(start, end, dest));
}
template<class InputIter, class Size, class OutputIter>
inline pair<InputIter, OutputIter>
copy_n_aux1(InputIter start, Size count, OutputIter dest)
{
    return copy_n_aux2(start, count, dest, GET_ITER_CATEGORY(start));
}
template<class InputIter, class Size, class OutputIter>
inline pair<InputIter, OutputIter>
copy_n(InputIter start, Size count, OutputIter dest)
{
    GECO_REQUIRES(InputIter, _InputIterator);
    GECO_REQUIRES(OutputIter, _OutputIterator);
    return copy_n_aux1(start, count, dest);
}
//--------------------------------------------------
// fill and fill_n
template<class ForwardIter, class ValueType>
void fill(ForwardIter start, ForwardIter end, const ValueType& value)
{
    GECO_REQUIRES(ForwardIter, _Mutable_ForwardIterator);
    for (; start != end; ++start)
        *start = value; // 调用的是operator =(), 这个要特别注意
}
// Specialization: for one-byte type and continues memory fill  we can use 
// memset. this is not template template specia;ization, 
// @caution this is actually fill<unsigned char*, unsigned char*>(unsigned char* start, unsigned char* end)
// you must sepecify specialized types in <>. this is like just a common function but will be taken into 
// account first by compiler, if not satified, it will call template version. why need this? two reasons:
// 1. less typing works 2. leass work for compiler deductions
inline void fill(unsigned char* start, unsigned char* end,
const unsigned char& c)
{
    unsigned char tmp = c;
    memset(start, tmp, end - start);
}

inline void fill(signed char* start, signed char* end,
    const signed char& c)
{
    signed char tmp = c;
    memset(start, static_cast<unsigned char>(tmp), end - start);
}

inline void fill(char* start, char* end, const char& c)
{
    char tmp = c;
    memset(start, static_cast<unsigned char>(tmp), end - start);
}

template<class OutputIter, class Size, class ValueType>
OutputIter fill_n(OutputIter start, Size n, const ValueType& value)
{
    GECO_REQUIRES(OutputIter, _OutputIterator);
    for (; n > 0; --n, ++start)
        *start = value;
    return start;
}

inline unsigned char* fill_n(unsigned char* start, ptrdiff_t n,
    const unsigned char& c)
{
    fill(start, start + n, c);
    return start + n;
}

inline signed char* fill_n(char* start, ptrdiff_t n, const signed char& c)
{
    fill(start, start + n, c);
    return (signed char*)start + n;
}

inline char* fill_n(char* start, ptrdiff_t n, const char& c)
{
    fill(start, start + n, c);
    return start + n;
}
//--------------------------------------------------
// equal and mismatch
// 找到两个序列第一个失配的地方, 结果以pair返回
template<class InputIter1, class InputIter2>
pair<InputIter1, InputIter2>
mismatch(InputIter1 start1, InputIter1 end1, InputIter2 start2)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    GECO_REQUIRES(typename iterator_traitor<InputIter1>::value_type,
        _EqualityComparable);
    GECO_REQUIRES(typename iterator_traitor<InputIter2>::value_type,
        _EqualityComparable);
    while (start1 != end1 && *start1 == *start2)
    {
        ++start1;
        ++start2;
    }
    return pair<InputIter1, InputIter2>(start1, start2);
}
// 提供用户自定义的二元判别式, 其余同上
template<class InputIter1, class InputIter2, class _BinaryPredicate>
pair<InputIter1, InputIter2>
mismatch(InputIter1 start1, InputIter1 end1, InputIter2 start2,
_BinaryPredicate __binary_pred)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    while (start1 != end1 && __binary_pred(*start1, *start2))
    {
        ++start1;
        ++start2;
    }
    return pair<InputIter1, InputIter2>(start1, start2);
}

// 如果序列在[first, last)内相等, 则返回true, 如果第二个序列有多余的元素,
// 则不进行比较, 直接忽略. 如果第二个序列元素不足, 会导致未定义行为
template<class InputIter1, class InputIter2>
inline bool
equal(InputIter1 start1, InputIter1 end1, InputIter2 start2)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    GECO_REQUIRES(typename iterator_traitor<InputIter1>::value_type,
        _EqualityComparable);
    GECO_REQUIRES(typename iterator_traitor<InputIter2>::value_type,
        _EqualityComparable);
    for (; start1 != end1; ++start1, ++start2)
        if (*start1 != *start2) // 只要有一个不相等就判定为false
            return false;
    return true;
}
// 提供用户自定义的二元判别式, 其余同上
template<class InputIter1, class InputIter2, class _BinaryPredicate>
inline bool
equal(InputIter1 start1, InputIter1 end1,
InputIter2 start2, _BinaryPredicate __binary_pred)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    for (; start1 != end1; ++start1, ++start2)
        if (!__binary_pred(*start1, *start2)) // 只要有一个不相等就判定为false
            return false;
    return true;
}

// 字典序比较, 非常类似字符串的比较
// 具体比较方式参见STL文档, 另外strcmp()也可以参考
// lexicographical_compare and lexicographical_compare_3way.
// (the latter is not part of the C++ standard.)
template<class InputIter1, class InputIter2>
bool lexicographical_compare(
    InputIter1 start1,
    InputIter1 end1,
    InputIter2 start2,
    InputIter2 end2)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    GECO_REQUIRES(typename iterator_traitor<InputIter1>::value_type,
        _LessThanComparable);
    GECO_REQUIRES(typename iterator_traitor<InputIter2>::value_type,
        _LessThanComparable);
    for (; start1 != end1 && start2 != end2; ++start1, ++start2)
    {
        if (*start1 < *start2)
            return true;
        if (*start2 < *start1)
            return false;
    }
    // 区间所有元素相等 all elments have the same value
    return start1 == end1 && start2 != end2;
}
// 提供用户自定义的二元判别式, 其余同上
template<class InputIter1, class InputIter2, class _Compare>
bool lexicographical_compare(
    InputIter1 start1,
    InputIter1 end1,
    InputIter2 start2,
    InputIter2 end2,
    _Compare __comp)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    for (; start1 != end1 && start2 != end2; ++start1, ++start2)
    {
        if (__comp(*start1, *start2))
            return true;
        if (__comp(*start2, *start1))
            return false;
    }
    return start1 == end1 && start2 != end2;
}
//char类型使用ｍｅｍｃｍｐ比较
inline bool lexicographical_compare(
    const unsigned char* start1,
    const unsigned char* end1,
    const unsigned char* start2,
    const unsigned char* end2)
{
    const size_t __len1 = end1 - start1;
    const size_t __len2 = end2 - start2;
    const int dest = memcmp(start1, start2, min(__len1, __len2));
    return dest != 0 ? dest < 0 : __len1 < __len2;
}
inline bool lexicographical_compare(
    const char* start1,
    const char* end1,
    const char* start2,
    const char* end2)
{
    /**
     limits.h 先定义了 SCHAR_ 和 UCHAR
     而 CHAR_* 是变化的，取什么值要看别的参数。
     CHAR_MAX和SCHAR_MAX 数值可能一样也可能不一样。
     基本定义：
     #define SCHAR_MIN   (-128)
     #define SCHAR_MAX     127
     #define UCHAR_MAX     0xff
     如果没有定义 _CHAR_UNSIGNED ：
     CHAR_MIN  等于  SCHAR_MIN  ，CHAR_MAX 等于   SCHAR_MAX
     如果定义了 _CHAR_UNSIGNED：
     CHAR_MIN    等于  0 ， CHAR_MAX   等于  UCHAR_MAX
     有符号 int 分  short int, int, long int 三种 分别定义:
     SHRT_, INT_,LONG_
     无符号 int 分 unsigned .... 三种 分别定义:
     USHRT_, UINT_,  ULONG_
     此外，int 还有 _I64  (64位整型）
     */
#if CHAR_MAX == SCHAR_MAX
    return lexicographical_compare((const signed char*)start1,
        (const signed char*)end1, (const signed char*)start2,
        (const signed char*)end2);
#else /* CHAR_MAX == SCHAR_MAX */
    return lexicographical_compare((const unsigned char*) start1,
        (const unsigned char*) end1,
        (const unsigned char*) start2,
        (const unsigned char*) end2);
#endif /* CHAR_MAX == SCHAR_MAX */
}

// 一句话概括, 这个是strcmp()的泛化版本
template<class InputIter1, class InputIter2>
int __lexicographical_compare_3way(InputIter1 start1, InputIter1 end1,
    InputIter2 start2, InputIter2 end2)
{
    while (start1 != end1 && start2 != end2)
    {
        if (*start1 < *start2)
            return -1;
        if (*start2 < *start1)
            return 1;
        ++start1;
        ++start2;
    }
    if (start2 == end2)
    {
        return !(start1 == end1);
    }
    else
    {
        return -1;
    }
}
inline int __lexicographical_compare_3way(const unsigned char* start1,
    const unsigned char* end1, const unsigned char* start2,
    const unsigned char* end2)
{
    const ptrdiff_t __len1 = end1 - start1;
    const ptrdiff_t __len2 = end2 - start2;
    const int dest = memcmp(start1, start2, min(__len1, __len2));
    return dest != 0 ?
    dest : (__len1 == __len2 ? 0 : (__len1 < __len2 ? -1 : 1));
}

inline int __lexicographical_compare_3way(const char* start1,
    const char* end1, const char* start2, const char* end2)
{
#if CHAR_MAX == SCHAR_MAX
    return __lexicographical_compare_3way((const signed char*)start1,
        (const signed char*)end1, (const signed char*)start2,
        (const signed char*)end2);
#else
    return __lexicographical_compare_3way((const unsigned char*) start1,
        (const unsigned char*) end1,
        (const unsigned char*) start2,
        (const unsigned char*) end2);
#endif
}

template<class InputIter1, class InputIter2>
int lexicographical_compare_3way(InputIter1 start1, InputIter1 end1,
    InputIter2 start2, InputIter2 end2)
{
    GECO_REQUIRES(InputIter1, _InputIterator);
    GECO_REQUIRES(InputIter2, _InputIterator);
    GECO_REQUIRES(typename iterator_traitor<InputIter1>::value_type,
        _LessThanComparable);
    GECO_REQUIRES(typename iterator_traitor<InputIter2>::value_type,
        _LessThanComparable);
    return __lexicographical_compare_3way(start1, end1, start2, end2);
}

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_ALGO_BASE_H_ */
