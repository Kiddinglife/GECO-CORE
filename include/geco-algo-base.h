/*
 * geco-algo-base.h
 *
 *  Created on: 18 Mar 2016
 *      Author: jakez
 */

#ifndef INCLUDE_GECO_ALGO_BASE_H_
#define INCLUDE_GECO_ALGO_BASE_H_

#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstddef>
#include <new>

#include "geco-pair.h"
#include "geco-type-traits.h"

#ifdef __STL_USE_NEW_IOSTREAMS
#include <iosfwd>
#else /* __STL_USE_NEW_IOSTREAMS */
#include <iostream>
#endif /* __STL_USE_NEW_IOSTREAMS */

//#include <geco-iterator-base.h>
//#include <geco-iterator.h>

GECO_BEGIN_NAMESPACE

// copy
// All of these auxiliary functions serve two purposes.
// (1) Replace calls to copy with memmove whenever possible.
// (Memmove, not memcpy,because the input and output ranges
// are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count.
template<class _InputIter, class _OutputIter, class _Distance>
inline _OutputIter
__copy(
_InputIter __first,
_InputIter __last,
_OutputIter __result,
input_iterator_tag,
_Distance*)
{
    for (; __first != __last; ++__result, ++__first)
        *__result = *__first;
    return __result;
}

template<class _RandomAccessIter, class _OutputIter, class _Distance>
inline _OutputIter
__copy(
_RandomAccessIter __first,
_RandomAccessIter __last,
_OutputIter __result,
random_access_iterator_tag,
_Distance*)
{
    for (_Distance __n = __last - __first; __n > 0; --__n) {
        *__result = *__first;
        ++__first;
        ++__result;
    }
    return __result;
}

template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last,
    _OutputIter __result)
{
    return __copy(
        __first,
        __last,
        __result,
        GET_ITER_CATEGORY(__first),
        GET_DISTANCE_TYPE(__first));
}
GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_ALGO_BASE_H_ */
