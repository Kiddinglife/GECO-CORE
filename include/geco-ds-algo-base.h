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

#ifndef INCLUDE_GECO_DS_ALGO_BASE_H_
#define INCLUDE_GECO_DS_ALGO_BASE_H_


#include "geco-ds-pair.h"
#include "geco-ds-iter.h"
#include "geco-ds-iter-base.h"
#include "geco-ds-type-traitor.h"

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <new>

#ifdef GECO_USE_NEW_IOSTREAMS
#include <iosfwd>
#else /* STL_USE_NEW_IOSTREAMS */
#include <iostream>
#endif /* STL_USE_NEW_IOSTREAMS */

GECO_BEGIN_NAMESPACE

//++++++++++++++++++++++++++++ min and max
#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x540 /* C++ Builder 4.0 */
#undef min
#undef max
template<class Type>
inline const Type& min(const Type& a, const Type& b)
{
    GECO_REQUIRES(a,b);
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
//+++++++++++++++++++++++++++++ min and max

//+++++++++++++++++++++++++++++ copy
// two purposes
// (1) Replace calls to copy with memmove whenever possible.
// (Memmove, not memcpy,because the input and output ranges
// are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count, faster because save iterator comparsion

template<class InputIter, class OutputIter, class Distance>
inline OutputIter
copy_aux3(InputIter first,InputIter last,OutputIter result,
        input_iterator_tag,Distance*)
{
    for (; first != last; ++result, ++first)
    {
        *result = *first;
    }
    return result;
}

template<class RandomAccessIter, class OutputIter, class Distance>
inline OutputIter
copy_aux3(RandomAccessIter first,RandomAccessIter last,OutputIter result,
        random_access_iterator_tag,Distance*)
{
    for (Distance n = last - first; n > 0; --n)
    {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

//! @brief for trivial type copy, use memmove for highest efficiency.
template <class Type>
inline Type*
copy_aux3(const Type* start, const Type* end, Type* dest)
{
    ::memmove(dest, start, sizeof(Type)*(end-start));
    return dest+(end - start);
}

#if defined(GECO_FUNCTION_TMPL_PARTIAL_ORDER)
template <class InputIter, class OutputIter>
inline OutputIter
copy_aux2(InputIter start, InputIter end,OutputIter dest,
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
#endif

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_ALGO_BASE_H_ */
