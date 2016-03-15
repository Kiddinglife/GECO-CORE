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
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for GECO
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

# ifndef __GECO_INTERNAL_CONSTRUCT_H
# define __GECO_INTERNAL_CONSTRUCT_H

#include <new> //! for use of placement new

#include "config.h"

__GECO_BEGIN_NAMESPACE

//! GECO's allocator is defined in geco-core-ds-memory.h
//! @brief geco - ctor.h defines global functions construct() and destruct() that
//! are used for object construction and destruction,
//! they are geco - standard - conforming functions.
//!
//! Only construct and destroy are standard-conforming
//! other functions are not part of the C++ standard,
//! and are provided for backward compatibility with the HP STL.  We also
//! provide internal names InternalConstruct and InternalDestroy that can be used within
//! the library, so that standard-conforming pieces don't have to rely on
//! non-standard extensions.

//! Internal names
template<class T1, class T2>
inline void InternalConstruct(T1 pointer, const T2& val) //!_Construct
{
    new ((void*) pointer) T1(val);
}
template<class T1>
inline void InternalConstruct(T1* pointer) //!_Construct
{
    new ((void*) pointer) T1();
}

template<class Tp>
inline void InternalDestroy(Tp* pointer) //!_Destroy
{
    pointer->~Tp();
}
template<class ForwardIterator>
void InternalDestroy(ForwardIterator first, ForwardIterator last)
{
}

__GECO_END_NAMESPACE
# endif
