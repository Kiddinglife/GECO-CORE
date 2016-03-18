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

/*
 * geco-pair.h
 *
 *  Created on: 18 Mar 2016
 *      Author: jakez
 */

#ifndef INCLUDE_GECO_PAIR_H_
#define INCLUDE_GECO_PAIR_H_

#include "geco-config.h"
GECO_BEGIN_NAMESPACE

template<class Type1, class Type2>
struct pair
{
    typedef Type1 first_type;
    typedef Type2 second_type;

    Type1 first_;
    Type2 second_;

    pair() :
            first_(Type1()), second_(Type2())
    {
    }

    pair(const Type1& first, const Type2& second) :
            first_(first), second_(second)
    {
    }

# ifdef GECO_MEMBER_TEMPLATES
    template<class U1, class U2>
    pair(const pair<U1, U2>& p) :
            first_(p.first_), second_(p.second_)
    {
    }
# endif
};

template<class _T1, class _T2>
inline bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return __x.first == __y.first && __x.second == __y.second;
}
template<class _T1, class _T2>
inline bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{
    return __x.first < __y.first
            || (!(__y.first < __x.first) && __x.second < __y.second);
}

# ifdef GECO_FUNCTION_TMPL_PARTIAL_ORDER
template<class T1, class T2>
inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}
# endif

template<class _T1, class _T2>
inline pair<_T1, _T2> make_pair(const _T1& __x, const _T2& __y)
{
    return pair<_T1, _T2>(__x, __y);
}

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_PAIR_H_ */
