/*
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
 * Created by Jakez on 1 20 March 2016
 * Reviewed by Jackz on 1 May 2016
 */

# ifndef __INCLUDE_GECO_CONSTRUCT_H
# define __INCLUDE_GECO_CONSTRUCT_H

#include <new> //! for use of placement new
#include "geco-ds-config.h"

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

template<class Type>
inline void construct(Type* pointer) //!_Construct
{
    new ((void*)pointer) Type();
}

template<class Type, class Value>
inline void construct(Type* pointer, const Value& val) //!_Construct
{
    new ((void*)pointer) Type(val); // call copy ctor or single parameter ctor
}
template<class Type, class Value1, class Value2>
inline void construct(Type* pointer,
        const Value1& val1,
        const Value2& val2) //!_Construct
{
    new ((void*)pointer) Type(val1, val2);
}
template<class Type, class Value1, class Value2, class Value3>
inline void construct(Type* pointer,
        const Value1& val1,
        const Value2& val2,
        const Value3& val3) //!_Construct
{
    new ((void*)pointer) Type(val1, val2, val3);
}
template<class Type, class Value1, class Value2, class Value3, class Value4>
inline void construct(Type* pointer,
        const Value1& val1,
        const Value2& val2,
        const Value3& val3,
        const Value4& val4) //!_Construct
{
    new ((void*)pointer) Type(val1, val2, val3, val4);
}
template<class Type, class Value1, class Value2, class Value3, class Value4, class Value5>
inline void construct(Type* pointer,
        const Value1& val1,
        const Value2& val2,
        const Value3& val3,
        const Value4& val4,
        const Value5& val5) //!_Construct
{
    new ((void*)pointer) Type(val1, val2, val3, val4, val5);
}

//! call destructor and release memory
template<class VallueType>
inline void destroy(VallueType* pointer)//!_Destroy
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
{}

template<class ForwardIterator, class Type>
inline void destroy(ForwardIterator first, ForwardIterator last, Type*)
{
    typedef typename type_traitor<Type>::has_trivial_dtor has_trivial_dtor;
    destroy(first, last, has_trivial_dtor());
}

template<class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last)
{
    //! this will call destroy(ForwardIterator first, ForwardIterator last, Type*)
    destroy(first, last, GET_VALUE_TYPE(first));
}

#define delc_destroy_trivial_raw_ptr(Type) inline void destroy(Type, Type){}
delc_destroy_trivial_raw_ptr(char*)
delc_destroy_trivial_raw_ptr(unsigned char*)
delc_destroy_trivial_raw_ptr(int*)
delc_destroy_trivial_raw_ptr(unsigned int*)
delc_destroy_trivial_raw_ptr(short*)
delc_destroy_trivial_raw_ptr(unsigned short*)
delc_destroy_trivial_raw_ptr(float*)
delc_destroy_trivial_raw_ptr(double*)
delc_destroy_trivial_raw_ptr(long double*)
#ifdef GECO_HAS_LONG_LONG
delc_destroy_trivial_raw_ptr(long long*)
delc_destroy_trivial_raw_ptr(unsigned long long*)
#endif
#ifdef GECO_HAS_WCHAR_T
delc_destroy_trivial_raw_ptr(wchar_t*)
#endif /* GECO_HAS_WCHAR_T */

GECO_END_NAMESPACE
# endif
