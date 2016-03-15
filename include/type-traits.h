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

# ifndef __GECO__TYPE_TRAITS_H
# define __GECO__TYPE_TRAITS_H

# include "config.h"

/*!
 * @brief This header file provides a framework for allowing complile time dispath based
 * on type attribute. This is useful when writing template code.
 *
 * when making a copy of an array of an unknown type, it helps to konw if the type has a
 * trivial copy ctor or not, to help decide if a memcpy can be used.
 *
 * The template TypeTraits(see below) provides a series of typedefs each of which is either
 * mTrueType or mFalseType.
 * The argument to TypeTraits can be any type. The typedefs within this template will attain
 * their correct values by one of these means:
 *    1. the gerneral instantiation contain conservative values which work for all types.
 *    2. Specializations may be delared to make distinctions between types.
 *    3. Some compilers (such as the Silicon Graphics N32 and N64 compilers)
 *        will automatically provide the appropriate specializations for all types.
 *
 * @code
 * struct TrueType {};
 * struct FalseType {};
 *
 * //copy an array of elments which have non-trivial copy ctors.
 * template<class T> void copy(T* source, T* destination, int n, FalseType falseType);
 *
 * //copy an array of elments which have trivial copy ctors. this function will use memcpy().
 * template<class T> void copy(T* source, T* destination, int n, TrueType trueType);
 *
 * //copy an array of elements by using the most efficient copy mechanism.
 * template<class T> inline void copy(T* source, T* destination, int n)
 * {
 *      // refer to 2. Specializations may be delared to make distinctions between types.
 *      // typename TypeTraits<T>::has_trivial_copy_ctor is known based on type of T
 *      // If T is int, TypeTraits<int>::has_trivial_copy_ctor = FalseType
 *      // if T is a class or struct, TypeTraits<int>::has_trivial_copy_ctor = TrueType
 *      copy(source, destination, n, typename TypeTraits<T>::has_trivial_copy_ctor());
 * }
 * @endcode
 */

struct TrueType
{
};
struct FalseType
{
};

template<class Tp>
struct TypeTraits
{
    /*!
     * Do not remove this member. It informs a compiler who is automatically specializing
     * TypeTraits that this template is special.
     *  It just makes sure that things work if an implementation is using a template
     *  called TypeTraits for something unrelated.
     */
    typedef TrueType this_dummy_member_must_be_first;

    /*!
     * The following restrictions should be observed for the sake of compiliers which
     * automatically produce type specific specifications of this class
     *    1. you MAY recorder the members below if you wish
     *    2. you MAY remove any of the members below if you wish
     *    3. you MUST NOT rename members without making the corresponding name change
     *    in the compiler
     *    4. members you add will be treated like regular members UNLESS you add the proper
     *    support in the compiler
     */
    typedef FalseType has_trivial_default_ctor; //!< ctor means constructor.
    typedef FalseType has_trivial_copy_ctor;
    typedef FalseType has_trivial_assign_opt; //!< opt means operator.
    typedef FalseType has_trivial_dtor; //!< dtor means destructor.
    typedef FalseType is_pod_type; //!< @see http://blog.csdn.net/aqtata/article/details/35618709 for details.
};


# endif
