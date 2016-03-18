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

# ifndef __INCLUDE_GECO_CONSTRUCT_H
# define __INCLUDE_GECO_CONSTRUCT_H

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
template<class Type, class Value>
inline void construct(Type pointer, const Value& val) //!_Construct
{
    new ((void*) pointer) Type(val);
}
template<class Type>
inline void construct(Type* pointer) //!_Construct
{
    new ((void*) pointer) Type();
}

//! call destructor and release memory
template<class VallueType>
inline void destroy(VallueType* pointer) //!_Destroy
{
    pointer->~VallueType();
}

//! destroy range objects
template<class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last, false_type)
{
    for (; first != last; ++first)
    {
        destroy(&*first); //!< get pointer to value type object
    }
}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last, true_type)
{
}

template<class ForwardIterator, class Type>
inline void destroy(ForwardIterator first, ForwardIterator last, Type*)
{
    typedef typename type_traitor<Type>::has_trivial_dtor has_trivial_dtor;
    destroy(first,last,has_trivial_dtor());
}

template<class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last)
{
    //! this will call destroy(ForwardIterator first, ForwardIterator last, Type*)
    destroy(first, last, VALUE_TYPE(first));
}
inline void destroy(char*, char*)
{
}
inline void destroy(unsigned char*, unsigned char*)
{
}
inline void destroy(int*, int*)
{
}
inline void destroy(unsigned int*, unsigned int*)
{
}
inline void destroy(long*, long*)
{
}
inline void destroy(unsigned long*, unsigned long*)
{
}
inline void destroy(float*, float*)
{
}
inline void destroy(double*, double*)
{
}
inline void destroy(long double*, long double*)
{
}
#ifdef GECO_HAS_WCHAR_T
inline void _Destroy(wchar_t*, wchar_t*)
{}
#endif /* GECO_HAS_WCHAR_T */

GECO_END_NAMESPACE
# endif
