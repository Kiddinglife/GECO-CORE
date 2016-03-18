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

/*!
 * @brief
 * there are two things we can do to fill unnitialized memory spaces:
 * 1.fill memory with a same value, term of fill used for the case;
 * 2.fill memory by copying data from other palces;
 * term of copy used for the case.
 */

//! +++++++++++++++++++++++++++++++++++++++
//!                               uninitialized_copy()
//! +++++++++++++++++++++++++++++++++++++++
//!                      |---------------> call memmove() for highest effciency
//!                      |---------------> (char *, ...)   <--- partial specialization char
//!                      |---------------> (wchar_t, ...) <--- partial specialization wchar_t
//!                      |
//!                      | Call
//!                      | tempalte uninitialized_copy(first, last, ValueType* is_pod_type)
//!                      |----->function overloaded
//!                                           |
//!                                           |---------------- Is POD?
//!                                           |
//!              -------------------------------------
//!           No |                                                   | Yes
//!               ↓                                                   |
//! __uninitialized_copy(..., false_type not_pod)   |
//! for ( ; first != last; ++first, ++cur)                |
//!      construct(&*cur, *first);                           ↓
//!                                   __uninitialized_copy(..., true_type is_pod)
//!                                   copy(first, last, result)
//! +++++++++++++++++++++++++++++++++++++++
//! uninitialized_copy_n and unitialized_fill have something common to above
//! and so they are not drawn individually.
//! +++++++++++++++++++++++++++++++++++++++
#ifndef INCLUDE_GECO_INITIALIZED_H_
#define INCLUDE_GECO_INITIALIZED_H_

#include <cstring>
#include "geco-config.h"
#include "geco-ctor-dtor.h"
GECO_BEGIN_NAMESPACE

//! @brief valid if copy ctor is equivalent to assignment when dtor is trivial
template<class InputIter, class ForwardIter>
inline ForwardIter uninitialized_copy(InputIter copy_start_pos,
    InputIter copy_end_pos, ForwardIter destination, true_type is_pod)
{
    GECO::copy(copy_start_pos, copy_end_pos, destination);
}

//! copy data in range [first, last) to the range satrting from result
template<class InputIter, class ForwardIter>
inline ForwardIter uninitialized_copy(InputIter first, InputIter last,
    ForwardIter result, false_type is_not_pod)
{
    ForwardIter cur = result;
    GECO_TRY
    {
        for (; first != last; ++first, ++cur)
        {
            construct(&*cur, *first);
        }
        return cur;
    }GECO_UNWIND(destroy(result, cur)); //!< if exception, destroy all copied data
}

template<class InputIter, class ForwardIter, class ValueType>
inline ForwardIter uninitialized_copy(InputIter copy_start_pos,
    InputIter copy_end_pos, ForwardIter destination, ValueType* is_pod_type)
{
    typedef typename type_traitor<ValueType>::is_POD_type _Is_POD;
    return uninitialize_copy(copy_start_pos, copy_end_pos, destination,
        _Is_POD());
}

template<class InputIter, class ForwardIter>
inline ForwardIter uninitialized_copy(InputIter copy_start_pos,
    InputIter copy_end_pos, ForwardIter destination)
{
    return uninitialized_copy(copy_start_pos, copy_end_pos, destination,
        VALUE_TYPE(destination));
}

inline char* uninitialized_copy(const char* copy_start_pos,
    const char* copy_end_pos, char* destination)
{
    memmove(destination, copy_start_pos, copy_end_pos - copy_start_pos);
    return destination + (copy_end_pos - copy_start_pos);
}

#ifdef GECO_HAS_WCHAR_T
inline wchar_t*
uninitialized_copy(const wchar_t* copy_start_pos, const wchar_t* copy_end_pos,
wchar_t* destination)
{
    memmove(destination, copy_start_pos, sizeof(wchar_t) * (copy_end_pos - copy_start_pos));
    return destination + (copy_end_pos - copy_start_pos);
}
#endif /* GECO_HAS_WCHAR_T */

//! @brief uninitialized_copy_n (not part of the C++ standard)
template<class InputIter, class ForwardIter>
inline pair<InputIter, ForwardIter> uninitialized_copy_n(
    InputIter copy_start_pos, InputIter copy_end_pos,
    ForwardIter destination, true_type is_pod)
{
    GECO::copy(copy_start_pos, copy_end_pos, destination);
}

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_INITIALIZED_H_ */
