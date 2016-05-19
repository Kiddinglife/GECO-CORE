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
 *  Created on: 22 Mar 2016
 * Author:     jake zhang
 * E - mail:   Jakezhang1989@hotmail.com
 * GitHub:    https://!github.com/Kiddinglife
 */

#ifndef __INCLUDE_GECO_DS_ITER_H
#define __INCLUDE_GECO_DS_ITER_H
#include "geco-ds-iter-base.h"

GECO_BEGIN_NAMESPACE
template<class container_type_>
class back_insert_iterator
{
protected:
    container_type_* container;
public:
    typedef container_type_ container_type;
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    explicit back_insert_iterator(container_type_& __x) :
    container(&__x)
    {
    }
    back_insert_iterator<container_type_>&
    operator=(const typename container_type_::value_type& __value)
    {
        container->push_back(__value);
        return *this;
    }
    back_insert_iterator<container_type_>& operator*()
    {
        return *this;
    }
    back_insert_iterator<container_type_>& operator++()
    {
        return *this;
    }
    back_insert_iterator<container_type_>& operator++(int)
    {
        return *this;
    }
};

#ifndef GECO_CLASS_PARTIAL_SPECIALIZATION
template<class container>
inline output_iterator_tag iterator_category(
        const back_insert_iterator<container>&)
{
    return output_iterator_tag();
}
#endif

template<class container>
inline back_insert_iterator<container> back_inserter(container& __x)
{
    return back_insert_iterator<container>(__x);
}

template<class container_type_>
class front_insert_iterator
{
protected:
    container_type_* container;
public:
    typedef container_type_ container_type;
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    explicit front_insert_iterator(container_type_& __x) :
    container(&__x)
    {
    }
    front_insert_iterator<container_type_>&
    operator=(const typename container_type_::value_type& __value)
    {
        container->push_front(__value);
        return *this;
    }
    front_insert_iterator<container_type_>& operator*()
    {
        return *this;
    }
    front_insert_iterator<container_type_>& operator++()
    {
        return *this;
    }
    front_insert_iterator<container_type_>& operator++(int)
    {
        return *this;
    }
};

#ifndef GECO_CLASS_PARTIAL_SPECIALIZATION
template<class container>
inline output_iterator_tag iterator_category(
        const front_insert_iterator<container>&)
{
    return output_iterator_tag();
}
#endif

template<class container>
inline front_insert_iterator<container> front_inserter(container& __x)
{
    return front_insert_iterator<container>(__x);
}

template<class container_type_>
class insert_iterator
{
protected:
    container_type_* container;
    typename container_type_::iterator iter;
public:
    typedef container_type_ container_type;
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    insert_iterator(container_type_& __x,
            typename container_type_::iterator __i) :
    container(&__x), iter(__i)
    {
    }

    /*只有提供了insert操作的容器才能使用insert_iterator*/
    insert_iterator<container_type_>&
    operator=(const typename container_type_::value_type& __value)
    {
        iter = container->insert(iter, __value);
        ++iter;
        return *this;
    }
    insert_iterator<container_type_>& operator*()
    {
        return *this;
    }
    insert_iterator<container_type_>& operator++()
    {
        return *this;
    }
    insert_iterator<container_type_>& operator++(int)
    {
        return *this;
    }
};

#ifndef GECO_CLASS_PARTIAL_SPECIALIZATION
template<class container_type_>
inline output_iterator_tag iterator_category(
        const insert_iterator<container_type_>&)
{
    return output_iterator_tag();
}
#endif

template<class container_type_, class _Iterator>
inline insert_iterator<container_type_> inserter(container_type_& __x,
        _Iterator __i)
{
    typedef typename container_type_::iterator __iter;
    return insert_iterator<container_type_>(__x, __iter(__i));
}

#ifndef GECO_LIMITED_DEFAULT_TEMPLATES
template<class _BidirectionalIterator, class _Tp, class _Reference = _Tp&,
class _Distance = ptrdiff_t>
#else
template <class _BidirectionalIterator, class _Tp, class _Reference,
class _Distance>
#endif
class reverse_bidirectional_iterator
{
    typedef reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
    _Reference, _Distance> _Self;
protected:
    _BidirectionalIterator current;
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp* pointer;
    typedef _Reference reference;

    reverse_bidirectional_iterator()
    {
    }
    explicit reverse_bidirectional_iterator(_BidirectionalIterator __x) :
    current(__x)
    {
    }
    _BidirectionalIterator base() const
    {
        return current;
    }
    _Reference operator*() const
    {
        _BidirectionalIterator __tmp = current;
        return *--__tmp;
    }
#ifndef SGI_GECO_NO_ARROW_OPERATOR
    pointer operator->() const
    {
        return &(operator*());
    }
#endif
    _Self& operator++()
    {
        --current;
        return *this;
    }
    _Self operator++(int)
    {
        _Self __tmp = *this;
        --current;
        return __tmp;
    }
    _Self& operator--()
    {
        ++current;
        return *this;
    }
    _Self operator--(int)
    {
        _Self __tmp = *this;
        ++current;
        return __tmp;
    }
    bool operator==(const _Self& __x)
    {
        return this->base() == __x.base();
    }
    bool operator!=(const _Self& __x)
    {
        return !(*this == __x);
    }
};

#ifndef GECO_CLASS_PARTIAL_SPECIALIZATION
template<class _BidirectionalIterator, class _Tp, class _Reference,
class _Distance>
inline bidirectional_iterator_tag iterator_category(
        const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
        _Reference, _Distance>&)
{
    return bidirectional_iterator_tag();
}
template<class _BidirectionalIterator, class _Tp, class _Reference,
class _Distance>
inline _Tp*
value_type(
        const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
        _Reference, _Distance>&)
{
    return (_Tp*) 0;
}
template<class _BidirectionalIterator, class _Tp, class _Reference,
class _Distance>
inline _Distance*
distance_type(
        const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
        _Reference, _Distance>&)
{
    return (_Distance*) 0;
}
#endif //GECO_CLASS_PARTIAL_SPECIALIZATION

// This is the new version of reverse_iterator, as defined in the
//  draft C++ standard.  It relies on the iterator_traits template,
//  which in turn relies on partial specialization.  The class
//  reverse_bidirectional_iterator is no longer part of the draft
//  standard, but it is retained for backward compatibility.
#ifdef GECO_CLASS_PARTIAL_SPECIALIZATION
template <class _Iterator>
class reverse_iterator
{
protected:
    _Iterator current;

public:
    typedef typename iterator_traitor<_Iterator>::iterator_category
    iterator_category;
    typedef typename iterator_traitor<_Iterator>::value_type
    value_type;
    typedef typename iterator_traitor<_Iterator>::difference_type
    difference_type;
    typedef typename iterator_traitor<_Iterator>::pointer
    pointer;
    typedef typename iterator_traitor<_Iterator>::reference
    reference;
    typedef _Iterator iterator_type;
    typedef reverse_iterator<_Iterator> _Self;

public:
    reverse_iterator()
    {}
    explicit reverse_iterator(iterator_type __x) : current(__x)
    {}
    reverse_iterator(const _Self& __x) : current(__x.current)
    {}

#ifdef GECO_MEMBER_TEMPLATES
    template <class _Iter>
    reverse_iterator(const _Self& __x)
    : current(__x.base())
    {}
#endif /* GECO_MEMBER_TEMPLATES */

    iterator_type base() const
    {   return current;}
    reference operator*() const
    {
        _Iterator __tmp = current;
        return *--__tmp;
    }

#ifndef SGI_GECO_NO_ARROW_OPERATOR
    pointer operator->() const
    {   return &(operator*());}
#endif

    _Self& operator++()
    {
        --current;
        return *this;
    }
    _Self operator++(int)
    {
        _Self __tmp = *this;
        --current;
        return __tmp;
    }
    _Self& operator--()
    {
        ++current;
        return *this;
    }
    _Self operator--(int)
    {
        _Self __tmp = *this;
        ++current;
        return __tmp;
    }

    _Self operator+(difference_type __n) const
    {
        return _Self(current - __n);
    }
    _Self& operator+=(difference_type __n)
    {
        current -= __n;
        return *this;
    }
    _Self operator-(difference_type __n) const
    {
        return _Self(current + __n);
    }
    _Self& operator-=(difference_type __n)
    {
        current += __n;
        return *this;
    }
    reference operator[](difference_type __n) const
    {
        return *(*this + __n);
        //fixme do unit test see if this is correct
        //_Iterator __tmp = current + __n;
        //return *--__tmp;
    }
    bool operator==(const _Self& __x)
    {
        return this->base() == __x.base();
    }
    bool operator!=(const _Self& __x)
    {
        return !(*this == __x);
    }
    bool operator<(const _Self& __y)
    {
        return base() < __y.base();
    }
    bool operator>(const _Self& __x)
    {
        return __x < *this;
    }
    bool operator<=(const _Self& __y)
    {
        return !(*this > __y);
    }
    bool operator>=(const _Self& __y)
    {
        return !(*this < __y);
    }
    difference_type operator-(const _Self& __y)
    {
        return __y.base() - base();
    }
    _Self operator+(difference_type __n)
    {
        return _Self(base() - __n);
    }
};
#else
#ifndef GECO_LIMITED_DEFAULT_TEMPLATES
template<class _RandomAccessIterator, class _Tp, class _Reference = _Tp&,
class _Distance = ptrdiff_t>
#else
template <class _RandomAccessIterator, class _Tp, class _Reference,
class _Distance>
#endif
class reverse_iterator
{
    typedef reverse_iterator<_RandomAccessIterator, _Tp, _Reference, _Distance> _Self;
protected:
    _RandomAccessIterator current;
public:
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp* pointer;
    typedef _Reference reference;
    typedef _RandomAccessIterator iterator_type;
public:
    reverse_iterator()
    {}
    explicit reverse_iterator(iterator_type __x) : current(__x)
    {}
    reverse_iterator(const _Self& __x) : current(__x.current)
    {}

#ifdef GECO_MEMBER_TEMPLATES
    template <class _Iter>
    reverse_iterator(const _Self& __x)
    : current(__x.base())
    {}
#endif /* GECO_MEMBER_TEMPLATES */

    iterator_type base() const
    {   return current;}
    reference operator*() const
    {
        iterator_type __tmp = current;
        return *--__tmp;
    }

#ifndef SGI_GECO_NO_ARROW_OPERATOR
    pointer operator->() const
    {   return &(operator*());}
#endif

    _Self& operator++()
    {
        --current;
        return *this;
    }
    _Self operator++(int)
    {
        _Self __tmp = *this;
        --current;
        return __tmp;
    }
    _Self& operator--()
    {
        ++current;
        return *this;
    }
    _Self operator--(int)
    {
        _Self __tmp = *this;
        ++current;
        return __tmp;
    }

    _Self operator+(difference_type __n) const
    {
        return _Self(current - __n);
    }
    _Self& operator+=(difference_type __n)
    {
        current -= __n;
        return *this;
    }
    _Self operator-(difference_type __n) const
    {
        return _Self(current + __n);
    }
    _Self& operator-=(difference_type __n)
    {
        current += __n;
        return *this;
    }
    reference operator[](difference_type __n) const
    {
        return *(*this + __n);
        //fixme do unit test see if this is correct
        //_Iterator __tmp = current + __n;
        //return *--__tmp;
    }
    bool operator==(const _Self& __x)
    {
        return this->base() == __x.base();
    }
    bool operator!=(const _Self& __x)
    {
        return !(*this == __x);
    }
    bool operator<(const _Self& __y)
    {
        return base() < __y.base();
    }
    bool operator>(const _Self& __x)
    {
        return __x < *this;
    }
    bool operator<=(const _Self& __y)
    {
        return !(*this > __y);
    }
    bool operator>=(const _Self& __y)
    {
        return !(*this < __y);
    }
    difference_type operator-(const _Self& __y)
    {
        return __y.base() - base();
    }
    _Self operator+(difference_type __n)
    {
        return _Self(base() - __n);
    }
};

template<class _RandomAccessIterator, class _Tp, class _Reference,
class _Distance>
inline random_access_iterator_tag iterator_category(
        const reverse_iterator<_RandomAccessIterator, _Tp, _Reference, _Distance>&)
{
    return random_access_iterator_tag();
}

template<class _RandomAccessIterator, class _Tp, class _Reference,
class _Distance>
inline _Tp* value_type(
        const reverse_iterator<_RandomAccessIterator, _Tp, _Reference, _Distance>&)
{
    return (_Tp*) 0;
}

template<class _RandomAccessIterator, class _Tp, class _Reference,
class _Distance>
inline _Distance*
distance_type(
        const reverse_iterator<_RandomAccessIterator, _Tp, _Reference, _Distance>&)
{
    return (_Distance*) 0;
}
#endif

// istream_iterator and ostream_iterator look very different if we're
// using new, templatized iostreams than if we're using the old cfront
// version.
GECO_END_NAMESPACE

#endif
