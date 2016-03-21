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

/*!
 * This file contains all of the general iterator-related utilities.
 * The internal file stl_iterator.h contains predefined iterators,
 * such as front_insert_iterator and istream_iterator.
 */

#ifndef __INCLUDE_GECO_ITERATOR_BASE_H
#define __INCLUDE_GECO_ITERATOR_BASE_H

#include "geco-config.h"
GECO_BEGIN_NAMESPACE

#define GECO_REQUIRES(a,b)

//++++++++++ ITERATOR TAG ++++++++++++
struct input_iterator_tag
{
};
struct output_iterator_tag
{
};
struct forward_iterator_tag: public input_iterator_tag
{
};
struct bidirectional_iterator_tag: public forward_iterator_tag
{
};
struct random_access_iterator_tag: public bidirectional_iterator_tag
{
};
//++++++++++ ITERATOR TAG ++++++++++++



//++++++++++ ITERATOR DELCS ++++++++++++
//! The base classes input_iterator, output_iterator, forward_iterator,
//! bidirectional_iterator, and random_access_iterator are not part of
//! the C++ standard. (They have been replaced by struct iterator.)
//! however, they are useful when the compiler does not support
//! class partial specialization in which case we have to use function overload
//! to get iterator type instance.

//! define to make life easier, used for declare iterators
#define delc_interator(iterator_name,valuetype, itertag, distance)\
struct iterator_name\
{\
    typedef itertag iterator_category;\
    typedef valuetype value_type;\
    typedef distance difference_type;\
    typedef valuetype* pointer;\
    typedef valuetype& reference;\
};

template<class Type, class Distance>
delc_interator(input_iterator, Type, input_iterator_tag,Distance)
template<class Type, class Distance>
delc_interator(output_iterator, Type, output_iterator_tag,Distance)
template<class Type, class Distance>
delc_interator(forward_iterator, Type, forward_iterator_tag,Distance)
template<class Type, class Distance>
delc_interator(bidirectional_iterator, Type, bidirectional_iterator_tag,Distance)
template<class Type, class Distance>
delc_interator(random_access_iterator, Type, random_access_iterator_tag,Distance)

//! stl standard confirming iterator delc
//! you can inheritat from this struct to make your own iterator
template<class Category,
class Type, class Distance = ptrdiff_t,
class Pointer = Type*, class Reference = Type&>
struct iterator
{
    typedef Category iterator_category;
    typedef Type value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};
//++++++++++ ITERATOR DELCS ++++++++++++



//++++++++++ ITERATOR TRAITOR DELCS ++++++++++++
/*!
 * the reason why we use class partial specialization is that:
 * the iterator traitor is designed to trait all types of iterators' assciated types.
 * But for compiler that does not support class partial specialization,
 * raw pointer iterator's assciated types cannot be traited normally.
 * and so, these compilers have to use another way to trait assciated types,
 * which is called 'overloaded functons'
 * @see test-geco-iter-base-h.cc
 * for code example of overloaded function traitor
 */
#ifdef GECO_CLASS_PARTIAL_SPECIALIZATION

template<class Iterator>
struct iterator_traitor
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

template<class Type>
struct iterator_traitor<Type*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef Type value_type;
    typedef ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef Type& reference;
};

template<class Type>
struct iterator_traitor<const Type*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef Type value_type;
    typedef ptrdiff_t difference_type;
    typedef const Type* pointer;
    typedef const Type& reference;
};

//! The overloaded functions iterator_category, distance_type, and
//! value_type are not part of the C++ standard.  (They have been
//! replaced by struct iterator_traitor.)  They are included for
//! backward compatibility with the HP STL.
//! We introduce internal names for these functions.
template<class Iter>
inline typename iterator_traitor<Iter>::iterator_category __iterator_category(
        const Iter&)
{
    typedef typename iterator_traitor<Iter>::iterator_category _Category;
    return _Category();
}

template<class Iter>
inline typename iterator_traitor<Iter>::difference_type*
__distance_type(const Iter&)
{
    return static_cast<typename iterator_traitor<Iter>::difference_type*>(0);
}

template<class Iter>
inline typename iterator_traitor<Iter>::value_type*
__value_type(const Iter&)
{
    return static_cast<typename iterator_traitor<Iter>::value_type*>(0);
}

template<class Iter>
inline typename iterator_traitor<Iter>::iterator_category iterator_category(
        const Iter& i)
{
    return __iterator_category(i);
}

template<class Iter>
inline typename iterator_traitor<Iter>::difference_type*
distance_type(const Iter& i)
{
    return __distance_type(i);
}

template<class Iter>
inline typename iterator_traitor<Iter>::value_type*
value_type(const Iter& i)
{
    return __value_type(i);
}

#define GET_ITER_CATEGORY(i) __iterator_category(i)
#define GET_DISTANCE_TYPE(i)     __distance_type(i)
#define GET_VALUE_TYPE(i)        __value_type(i)
#else
//!! make life easier
#define delc_traitor_function(iterator_tag, name, iterator_type) \
inline iterator_tag name(const iterator_type<Type, Distance>&) \
{\
    return iterator_tag();\
}

template <class Type, class Distance>
delc_traitor_function(input_iterator_tag,iterator_category,input_iterator)
template <class Type, class Distance>
delc_traitor_function(output_iterator_tag,iterator_category,output_iterator)
template <class Type, class Distance>
delc_traitor_function(forward_iterator_tag,iterator_category,forward_iterator)
template <class Type, class Distance>
delc_traitor_function(bidirectional_iterator_tag,iterator_category,bidirectional_iterator)
template <class Type, class Distance>
delc_traitor_function(random_access_iterator_tag,iterator_category,random_access_iterator)

//! the
template <class Type>
inline random_access_iterator_tag iterator_category(const Type*)
{
    return random_access_iterator_tag();
}

template <class Type, class Distance>
inline Type* value_type(const input_iterator<Type, Distance>&)
{
    return (Type*)(0);
}

template <class Type, class Distance>
inline Type* value_type(const forward_iterator<Type, Distance>&)
{
    return (Type*)(0);
}

template <class Type, class Distance>
inline Type* value_type(const bidirectional_iterator<Type, Distance>&)
{
    return (Type*)(0);
}

template <class Type, class Distance>
inline Type* value_type(const random_access_iterator<Type, Distance>&)
{
    return (Type*)(0);
}

template <class Type>
inline Type* value_type(const Type*)
{   return (Type*)(0);}

template <class Type, class Distance>
inline Distance* distance_type(const input_iterator<Type, Distance>&)
{
    return (Distance*)(0);
}

template <class Type, class Distance>
inline Distance* distance_type(const forward_iterator<Type, Distance>&)
{
    return (Distance*)(0);
}

template <class Type, class Distance>
inline Distance*
distance_type(const bidirectional_iterator<Type, Distance>&)
{
    return (Distance*)(0);
}

template <class Type, class Distance>
inline Distance*
distance_type(const random_access_iterator<Type, Distance>&)
{
    return (Distance*)(0);
}

template <class Type>
inline ptrdiff_t* distance_type(const Type*)
{   return (ptrdiff_t*)(0);}

//! Without partial specialization we can't use iterator_traitor, so
//! we must keep the old iterator query functions around.

#define GET_ITER_CATEGORY(i) iterator_category(i)
#define GET_DISTANCE_TYPE(i)     distance_type(i)
#define GET_VALUE_TYPE(i)        value_type(i)

#endif  /* GECO_CLASS_PARTIAL_SPECIALIZATION */

template<class InputIter, class Distance>
inline void __distance(InputIter first, InputIter last, Distance& n,
        input_iterator_tag)
{
    while (first !=last)
    {
        ++first;
        ++n;
    }
}

template<class _RandomAccessIterator, class Distance>
inline void __distance(_RandomAccessIterator __first,
        _RandomAccessIterator __last, Distance& n, random_access_iterator_tag)
{
    GECO_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
    n += __last - __first;
}

template<class InputIter, class Distance>
inline void distance(InputIter __first, InputIter __last, Distance& n)
{
    GECO_REQUIRES(InputIter, InputIter);
    __distance(__first, __last, n, GET_ITER_CATEGORY(__first));
}

#ifdef GECO_CLASS_PARTIAL_SPECIALIZATION
template<class InputIter>
inline typename iterator_traitor<InputIter>::difference_type __distance(
        InputIter __first, InputIter __last, input_iterator_tag)
{
    typename iterator_traitor<InputIter>::difference_type n = 0;
    while (__first != __last)
    {
        ++__first;
        ++n;
    }
    return n;
}

template<class _RandomAccessIterator>
inline typename iterator_traitor<_RandomAccessIterator>::difference_type __distance(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        random_access_iterator_tag)
{
    GECO_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
    return __last - __first;
}

//!! this is where the inheritance works.
//!! any class above  the youngest child random_access_iterator_tag will overloaded
//!! to __distance(..., input_iterator_tag)
template<class InputIter>
inline typename iterator_traitor<InputIter>::difference_type distance(
        InputIter __first, InputIter __last)
{
    typedef typename iterator_traitor<InputIter>::iterator_category _Category;
    GECO_REQUIRES(InputIter, InputIter);
    return __distance(__first, __last, _Category());
}
#endif  /* GECO_CLASS_PARTIAL_SPECIALIZATION */

template<class InputIter, class Distance>
inline void __advance(InputIter& i, Distance n, input_iterator_tag)
{
    while (n--)
    ++i;
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1183
#endif

template<class BidirectionalIter, class Distance>
inline void __advance(BidirectionalIter& i, Distance n,
        bidirectional_iterator_tag)
{
    GECO_REQUIRES(BidirectionalIter, BidirectionalIter);
    if (n >= 0)
    while (n--)
    ++i;
    else
    while (n++)
    --i;
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1183
#endif

template<class _RandomAccessIterator, class Distance>
inline void __advance(_RandomAccessIterator& i, Distance n,
        random_access_iterator_tag)
{
    GECO_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
    i += n;
}

template<class InputIter, class Distance>
inline void advance(InputIter& i, Distance n)
{
    GECO_REQUIRES(InputIter, InputIter);
    __advance(i, n, GET_ITER_CATEGORY(i));
}

GECO_END_NAMESPACE
;
#endif
