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
 * geco-initialize.h
 *
 *  Created on: 18 Mar 2016
 *      Author: jakez zhang
 *+++++++++++++++++++++++++++++++++++++++
 * @brief
 * there are two things we can do to fill unnitialized memory spaces:
 * 1.fill memory with a given value
 * 2.copy data from other palces;
 *+++++++++++++++++++++++++++++++++++++++
 *                                uninitialized_copy()
 *+++++++++++++++++++++++++++++++++++++++
 *                      |---------------> call memmove() for highest effciency
 *                      |---------------> (char *, ...)   <--- partial specialization char
 *                      |---------------> (wchar_t, ...) <--- partial specialization wchar_t
 *                      |
 *                      | Call
 *                      | tempalte uninitialized_copy(start, end, ValueType* is_pod_type)
 *                      |----->function overloaded
 *                                           |
 *                                           |  Is POD?
 *                                          ↓
 *               ++++++++++++++++++++++
 *           No |                                                    | yes
 *               ↓                                                   | handled by algo function copy
 *      construct(&*cur, *start);               copy(start, end, dest)
 *                                                                      |
 *                                                                      |  has_trivial_assign_opt ? (function overload)
 *                                                                     ↓
 *                                             yes +++++++++++++++++ No
 *                                                   ↓                                         |
 *                                   use memmove                                  ↓
 *                                            copy_aux3()                   copy_aux3(...,)
 *
 *
 *
 * uninitialized_copy_n and unitialized_fill have something common to above
 * and so they are not drawn individually.
 */

#ifndef __INCLUDE_GECO_DS_INITIALIZED_H
#define __INCLUDE_GECO_DS_INITIALIZED_H

#include <string.h>
#include "geco-ds-algo-base.h"

GECO_BEGIN_NAMESPACE


//+++++++++++++++++++++++++++++++++++++++++++++
//* This method can seperate object construction with its mallocation,
//* if iterator within [dest, distination+(end-start)) point to an
//* unnitialized memory block, copy ctor will be called on every object
//* within [start, end) and put the copy of that object into range
//* container's range constructor often follow the below steps:
//*  - allocate enough memory to hold all elements in the range
//*  - call uninitialized_copy() to construct elment in the memory range.
//+++++++++++++++++++++++++++++++++++++++++++++



//++++++++++++++ uninitialized_copy +++++++++++++++++++++
//! @brief valid if copy ctor is equivalent to assignment when dtor is trivial
//! copy data in range [start, end) to the range satrting from dest
//! commit or rollback
template<class InputIter, class ForwardIter>
inline ForwardIter
uninitialized_copy_aux2(InputIter start, InputIter end,
ForwardIter dest, true_type is_pod)
{
    return copy(start, end, dest);
}

template<class InputIter, class ForwardIter>
inline ForwardIter
uninitialized_copy_aux2(InputIter start, InputIter end,
ForwardIter dest, false_type is_not_pod)
{
    ForwardIter cur = dest;
    GECO_TRY
    {
        for (; start != end; ++start, ++cur)
        {
            construct(&*cur, *start);
        }
        return cur;
    }GECO_UNWIND(destroy(dest, cur)); //!< if exception, destroy all copied data
}

template<class InputIter, class ForwardIter, class ValueType>
inline ForwardIter
uninitialized_copy_aux1(InputIter start, InputIter end,
ForwardIter dest, ValueType* is_pod_type)
{
    typedef typename type_traitor<ValueType>::is_pod_type _Is_POD;
    return uninitialized_copy_aux2(start, end, dest, _Is_POD());
}

template<class InputIter, class ForwardIter>
inline ForwardIter
uninitialized_copy(InputIter start, InputIter end, ForwardIter dest)
{
    // use value_type() to fetch the value type of start
    return uninitialized_copy_aux1(start, end, dest, GET_VALUE_TYPE(dest));
}

//! full specializations of uninitialized_copy(...)
inline char*
uninitialized_copy(const char* start, const char* end, char* dest)
{
    memmove(dest, start, end - start);
    return dest + (end - start);
}

#ifdef GECO_HAS_WCHAR_T
inline wchar_t*
uninitialized_copy(const wchar_t* start, const wchar_t* end, wchar_t* dest)
{
    memmove(dest, start, sizeof(wchar_t) * (end - start));
    return dest + (end - start);
}
#endif /* GECO_HAS_WCHAR_T */



//++++++++++++++++++ uninitialized_copy_n +++++++++++++++
//! @brief uninitialized_copy_n (not part of the C++ standard)
template<class InputIter, class ForwardIter, class Size>
inline pair<InputIter, ForwardIter>
uninitialized_copy_n_aux1(InputIter start, Size copy_size,
ForwardIter dest, input_iterator_tag)
{
    ForwardIter cur = dest;
    GECO_TRY
    {
        // not call  uninitialized_copy() is as uninitialized_copy() does another for loop 
        // to construct value
        for (; copy_size > 0; --copy_size, ++start, ++cur)
        {
            construct(&*cur, *cur);
        }
        return pair<InputIter, ForwardIter>(start, cur);
    }GECO_UNWIND(destroy(dest, cur));
}

template<class RandomAccessIter, class ForwardIter, class Size>
inline pair<RandomAccessIter, ForwardIter>
uninitialized_copy_n_aux1(RandomAccessIter start, Size copy_size,
ForwardIter dest, random_access_iterator_tag)
{
    RandomAccessIter end = start + copy_size;
    return pair<RandomAccessIter, ForwardIter>(end, uninitialized_copy(start, end, dest));
}

template <class InputIter, class ForwardIter, class Size>
inline pair<InputIter, ForwardIter>
__uninitialized_copy_n(InputIter first, Size count, ForwardIter result)
{
    // for internal use not standard-conforming
    return uninitialized_copy_n_aux1(first, count, result, GET_ITER_CATEGORY(first));
}

template <class InputIter, class ForwardIter, class Size>
inline pair<InputIter, ForwardIter>
uninitialized_copy_n(InputIter first, Size count, ForwardIter result)
{
    return uninitialized_copy_n_aux1(first, count, result, GET_ITER_CATEGORY(first));
}

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_INITIALIZED_H_ */
