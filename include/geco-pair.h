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
 * geco-pair.h
 *
 *  Created on: 18 Mar 2016
 *      Author: jakez
 */

// make_pair(0 uses return value optimization

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

template<class Type1, class Type2>
inline bool operator==(const pair<Type1, Type2>& __x,
        const pair<Type1, Type2>& __y)
{
    return __x.first == __y.first && __x.second == __y.second;
}
template<class Type1, class Type2>
inline bool operator<(const pair<Type1, Type2>& __x,
        const pair<Type1, Type2>& __y)
{
    return __x.first < __y.first
            || (!(__y.first < __x.first) && __x.second < __y.second);
}

# ifdef GECO_FUNCTION_TMPL_PARTIAL_ORDER
template<class Type1, class Type2>
inline bool operator!=(const pair<Type1, Type2>& __x,
        const pair<Type1, Type2>& __y)
{
    return !(__x == __y);
}

template<class Type1, class Type2>
inline bool operator>(const pair<Type1, Type2>& __x,
        const pair<Type1, Type2>& __y)
{
    return __y < __x;
}

template<class Type1, class Type2>
inline bool operator<=(const pair<Type1, Type2>& __x,
        const pair<Type1, Type2>& __y)
{
    return !(__y < __x);
}

template<class Type1, class Type2>
inline bool operator>=(const pair<Type1, Type2>& __x,
        const pair<Type1, Type2>& __y)
{
    return !(__x < __y);
}

# endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

//! return value optimization
//! @see http://www.programlife.net/cpp-return-value-optimization.html
// call ctor ->copy ctor->dtor
//const Rational operator*(const Rational& lhs,
//                       const Rational& rhs)
//{
//  return Rational(lhs.numerator() * rhs.numerator(),
//                  lhs.denominator() * rhs.denominator());
//}

// only call ctor so most effcient
//const Rational operator*(const Rational& lhs,
//                         const Rational& rhs)
//{
//    cout << "----------- Enter operator* -----------" << endl;
//    Rational tmp(lhs.numerator() * rhs.numerator(),
//        lhs.denominator() * rhs.denominator());
//    cout << "----------- Leave operator* -----------" << endl;
//    return tmp;
//}
template<class Type1, class Type2>
inline pair<Type1, Type2> make_pair(const Type1& __x, const Type2& __y)
{
    return pair<Type1, Type2>(__x, __y);
}

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_PAIR_H_ */
