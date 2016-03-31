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

// @Caution when copying non-tricial-assignment-opt-types, like custom class defined by users
// it will depent on the user-defined-assign-opt's implementations. if you have pointer members
// in class, if you implement copying data in overwrittn assign-opt method,
// this copy() will also do same thing

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
    GECO_REQUIRES(_Tp, _LessThanComparable);
    return a < b ? b : a;
}
#else
template<class _Tp, class _Compare>
inline const _Tp& min(const _Tp& __a, const _Tp& __b, _Compare __comp)
{
    return __comp(__b, __a) ? __b : __a;
}
template<class _Tp, class _Compare>
inline const _Tp& max(const _Tp& __a, const _Tp& __b, _Compare __comp)
{
    return __comp(__a, __b) ? __b : __a;
}
#endif

// swap and iter swap
template <class ForwardIter1, class ForwardIter2, class Type>
inline void
iter_swap_aux1(ForwardIter1 a, ForwardIter2 b, Type*)
{
    Type tmp = *a;
    *a = *b;
    *b = tmp;
}

template<class _ForwardIter1, class _ForwardIter2>
inline void iter_swap(_ForwardIter1 a, _ForwardIter2 b)
{
    GECO_REQUIRES(ForwardIter1, Mutable_ForwardIterator);
    GECO_REQUIRES(ForwardIter2, Mutable_ForwardIterator);
    GECO_CONVERTIBLE(typename iterator_traitor<_ForwardIter1>::value_type,
            typename iterator_traitor<_ForwardIter2>::value_type);
    GECO_CONVERTIBLE(typename iterator_traitor<_ForwardIter2>::value_type,
            typename iterator_traitor<_ForwardIter1>::value_type);
    iter_swap_aux1(a, b, GET_VALUE_TYPE(a));
}

template<class Type>
inline void swap(Type& a, Type& b)
{
    GECO_REQUIRES(_Tp, _Assignable);
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
    for (; first != last; ++result, ++first)
    {
        *result = *first;
    }
    return result;
}

// hashtable supports random iter but cannot be copied using memmove()
template<class RandomAccessIter, class OutputIter, class Distance>
inline OutputIter
copy_aux3(RandomAccessIter first, RandomAccessIter last, OutputIter result,
        random_access_iterator_tag, Distance*)
{
    for (Distance n = last - first; n > 0; --n)
    {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

// @remember myself,
// for trivial type copy, for example, builtin basic types int* char* and so on.
// use memmove for highest efficiency.
// @remember myself, I was wondering why the two copy_aux3() above does not use
// memove() as we can do &*iter to get the value_type raw pointer formate.
// now reason is that memove or memcpy() functions only work on continuesous memory
//so this method only works for continusous memory copy,
// for example, vector. but for list, even though its value type is basic types like int, we
// have to go through the elment one by one and copy it simply by = just as the above
// copy_aux3(0 functions do.
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

template <class _Tp>
struct copy_dispatcher<_Tp*, _Tp*, true_type>
{
    static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result)
    {
        return copy_aux3(__first, __last, __result);
    }
};

template <class _Tp>
struct copy_dispatcher<const _Tp*, _Tp*, true_type>
{
    static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result)
    {
        return copy_aux3(__first, __last, __result);
    }
};

template <class _InputIter, class _OutputIter>
inline _OutputIter
copy(_InputIter __first, _InputIter __last,_OutputIter __result)
{
    GECO_REQUIRES(_InputIter, _InputIterator);
    GECO_REQUIRES(_OutputIter, _OutputIterator);
    typedef typename iterator_traitor<_InputIter>::value_type value_type_;
    typedef typename type_traitor<value_type_>::has_trivial_assign_opt assign_opt_;
    typedef typename copy_dispatcher<_InputIter, _OutputIter, assign_opt_> copy_dispatcher_;
    return copy_dispatcher_::copy(__first, __last, __result);
}
#else
// fallback for compilers with neither partial ordering nor partial specialization.
// in order to define faster version of copy() for the basic builtin types
template<class _InputIter, class _OutputIter>
inline _OutputIter
copy(_InputIter start, _InputIter end,_OutputIter dest)
{
    return copy_aux3(start, end,dest,
            GET_ITER_CATEGORY(start),
            GET_DISTANCE_TYPE(start));
}

#define delc_memmove_copy(_Tp)                                \
  inline _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) { \
    memmove(__result, __first, sizeof(_Tp) * (__last - __first));          \
    return __result + (__last - __first);                                  \
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
// copy_backward 从后往前拷贝

//--------------------------------------------------
// copy_n (not part of the C++ standard)

//--------------------------------------------------
// fill and fill_n

//--------------------------------------------------
// equal and mismatch

//--------------------------------------------------
// lexicographical_compare and lexicographical_compare_3way.
// (the latter is not part of the C++ standard.)

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_ALGO_BASE_H_ */
