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
 */

#ifndef INCLUDE_GECO_DS_INITIALIZED_H_
#define INCLUDE_GECO_DS_INITIALIZED_H_

#include <cstring>

#include "geco-ds-config.h"
#include "geco-ds-ctor.h"
#include "geco-ds-algo-base.h"

GECO_BEGIN_NAMESPACE

/*!
 * @brief
 * there are two things we can do to fill unnitialized memory spaces:
 * 1.fill memory with a same value, term of fill used for the case;
 * 2.fill memory by copying data from other palces;
 * term of copy used for the case.
 */

/*! +++++++++++++++++++++++++++++++++++++++
 *                                uninitialized_copy()
 * +++++++++++++++++++++++++++++++++++++++
 //!                      |---------------> call memmove() for highest effciency
 //!                      |---------------> (char *, ...)   <--- partial specialization char
 //!                      |---------------> (wchar_t, ...) <--- partial specialization wchar_t
 //!                      |
 //!                      | Call
 //!                      | tempalte uninitialized_copy(start, end, ValueType* is_pod_type)
 //!                      |----->function overloaded
 //!                                           |
 //!                                           |  Is POD?
 //!                                          ↓
 //!               ++++++++++++++++++++++
 //!           No |                                                    | yes
 //!               ↓                                                   | handled by algo function copy
 //!      construct(&*cur, *start);               copy(start, end, dest)
 *                                                                      |
 *                                                                      |  has_trivial_assign_opt ? (based on function overload)
 *                                                                     ↓
 *                                             yes +++++++++++++++++ No
 *                                                    |                                          |
 *                                   use memmove                                      |
 *                                            copy_aux3()           copy_aux3(...,)
 *
 *
 *
 //! uninitialized_copy_n and unitialized_fill have something common to above
 //! and so they are not drawn individually.
 */
/*!
 * this method can seperate object construction with its mallocation,
 * if iterator within [dest, distination+(end-start)) point to an
 * unnitialized memory block, copy ctor will be called on every object
 * within [start, end) and put the copy of that object into range
 * container's range constructor often follow the below steps:
 *  - allocate enough memory to hold all elements in the range
 *  - call uninitialized_copy() to construct elment in the memory range.
 */
template<class InputIter, class ForwardIter>
inline ForwardIter
uninitialized_copy(InputIter start,InputIter end, ForwardIter dest)
{
    return uninitialized_copy(start, end, dest,VALUE_TYPE(dest));
    // use value_type() to fetch the value type of start
}

//! full specialization of template uninitialized_copy()
inline char*
uninitialized_copy(const char* start,const char* end, char* dest)
{
    ::memmove(dest, start, end - start);
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

template<class InputIter, class ForwardIter, class ValueType>
inline ForwardIter
uninitialized_copy(InputIter start,InputIter end,
        ForwardIter dest, ValueType* is_pod_type)
{
    typedef typename type_traitor<ValueType>::is_POD_type _Is_POD;
    return uninitialize_copy(start, end, dest,_Is_POD());
}

//! @brief valid if copy ctor is equivalent to assignment when dtor is trivial
template<class InputIter, class ForwardIter>
inline ForwardIter
uninitialized_copy(InputIter start,InputIter end,
        ForwardIter dest, true_type is_pod)
{
    copy(start, end, dest);
}

//! copy data in range [start, end) to the range satrting from dest
//! commit or rollback
template<class InputIter, class ForwardIter>
inline ForwardIter
uninitialized_copy(InputIter start, InputIter end,
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

//! @brief uninitialized_copy_n (not part of the C++ standard)
template<class InputIter, class ForwardIter,class Size>
inline pair<InputIter, ForwardIter>
uninitialized_copy_n(InputIter start, Size copy_size,
        ForwardIter dest, input_iterator_tag)
{
    ForwardIter cur = dest;
    GECO_TRY
    {
        for(; copy_size > 0; --copy_size, ++start, ++cur)
        {
            construct(&*cur, *cur);
        }
        return pair<InputIter, ForwardIter>(start, cur);
    }GECO_UNWIND(destroy(dest, cur));
}

template<class InputIter, class ForwardIter>
pair<InputIter, ForwardIter>
uninitialized_copy_n(InputIter start, InputIter end,
        ForwardIter dest, true_type is_pod)
{

}
GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_INITIALIZED_H_ */
