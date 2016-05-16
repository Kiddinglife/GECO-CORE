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

GECO_END_NAMESPACE

#endif
