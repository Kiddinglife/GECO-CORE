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

#include "geco-config.h"

GECO_BEGIN_NAMESPACE

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
template<class Type1, class Type2>
inline void InternalConstruct(Type1 pointer, const Type2& val) //!_Construct
{
    new ((void*) pointer) T1(val);
}
template<class Type1>
inline void InternalConstruct(Type1* pointer) //!_Construct
{
    new ((void*)pointer) Type1();
}

template<class Type>
inline void InternalDestroy(Type* pointer) //!_Destroy
{
    pointer->~Type();
}
template<class ForwardIterator>
void InternalDestroy(ForwardIterator first, ForwardIterator last)
{
}

GECO_END_NAMESPACE
# endif
