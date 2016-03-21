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

# ifndef __INCLUDE_GECO__TYPE_TRAITS_H
# define __INCLUDE_GECO__TYPE_TRAITS_H

# include "geco-config.h"

/*!
 * @brief This header file provides a framework for allowing complile time dispath
 * based on type attribute. This is useful when writing template code.
 *
 * when making a copy of an array of an unknown type, it helps to konw if the type
 * has a trivial copy ctor or not, to help decide if a memcpy can be used.
 *
 * The template TypeTraits(see below) provides a series of typedefs each of which is
 * eitherm TrueType or mFalseType.
 * The argument to TypeTraits can be any type. The typedefs within this template
 * will attain their correct values by one of these means:
 *    1. TypeTraits' gerneral instantiation contain conservative values which work for all types.
 *        @example
 *        If given:
 *        TypeTraits<class Type>{tyodef typename Type::value_type value_type;}
 *        A gerneral instantiation look like this:
 *        TypeTraits<std::vector<int>::iterator>::value_type;
 *        You will get type of int.
 *        @example
 *    2. TypeTraits' template partial or full specializations may be delared to make distinctions between types.
 *        @example
 *        If given:
 *          - TypeTraits<class Type>{typedef typename Type::value_type value_type;}
 *        A partialspecification template looks like this:
 *          - TypeTraits<Type*>{typedef typename Type value_type;}
 *        when instantiated like this;
 *          - TypeTraits<int*>::value_type;
 *          - You will also get type of int.
 *
 *        A full specification template looks like this:
 *          - template<> TypeTraits<int>{typedef typename int value_type;}
 *        when instantiated like this;
 *          - TypeTraits<int>::value_type;
 *          - You will also get type of int.
 *        @example
 *    3. Some compilers (such as the Silicon Graphics N32 and N64 compilers)
 *        will automatically provide the appropriate specializations for all types.
 *
 * @code
 * struct TrueType {};
 * struct FalseType {};
 *
 * //copy an array of elments which have non-trivial copy ctors.
 * template<class Type> void copy(Type* source, Type* destination, int n, FalseType falseType);
 *
 * //copy an array of elments which have trivial copy ctors. this function will use memcpy().
 * template<class Type> void copy(Type* source, Type* destination, int n, TrueType trueType);
 *
 * //copy an array of elements by using the most efficient copy mechanism.
 * template<class Type> inline void copy(Type* source, Type* destination, int n)
 * {
 *      // typename TypeTraits<Type>::has_trivial_copy_ctor is known based on type of Type
 *      // If Type is int, TypeTraits<int>::has_trivial_copy_ctor = FalseType
 *      // if Type is a class or struct, TypeTraits<int>::has_trivial_copy_ctor = TrueType
 *      copy(source, destination, n, typename TypeTraits<Type>::has_trivial_copy_ctor());
 * }
 * @endcode
 */

GECO_BEGIN_NAMESPACE

# ifndef GECO_DEFAULT_CONSTRUCTOR_BUG
enum true_type
{
};
enum false_type
{
};
# else
struct true_type
{
};
struct false_type
{
};
# endif

template<class Type>
struct type_traitor
{
    /*!
     * Do not remove this member. It informs a compiler who is automatically specializing
     * TypeTraits that this template is special.
     *  It just makes sure that things work if an implementation is using a template
     *  called TypeTraits for something unrelated.
     */
    typedef true_type this_dummy_member_must_be_first;

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
    typedef false_type has_trivial_default_ctor; //!< ctor means constructor.
    typedef false_type has_trivial_copy_ctor;
    typedef false_type has_trivial_assign_opt; //!< opt means operator.
    typedef false_type has_trivial_dtor; //!< dtor means destructor.
    typedef false_type is_pod_type; //!< @see http://blog.csdn.net/aqtata/article/details/35618709 for details.
};

/*!
 * @brief Provide some specilizations for @struct TypeTraits.
 * This is harmless for comlilers that have built0in type traits support,
 * and essential for those that do not have it.
 */
# ifndef GECO_NO_BOOL
GECO_TEMPLATE_NULL struct type_traitor<bool>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
# endif

# ifdef GECO_HAS_WCHAR_T
GECO_TEMPLATE_NULL struct type_traitor<wchar_t>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
# endif

GECO_TEMPLATE_NULL struct type_traitor<char>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<signed char>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<unsigned char>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};

GECO_TEMPLATE_NULL struct type_traitor<short>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<unsigned short>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};

GECO_TEMPLATE_NULL struct type_traitor<int>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<unsigned int>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};

GECO_TEMPLATE_NULL struct type_traitor<long>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<unsigned long>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};

# ifndef GECO_LONG_LONG
GECO_TEMPLATE_NULL struct type_traitor<long long>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<unsigned long long>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
# endif

GECO_TEMPLATE_NULL struct type_traitor<float>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<double>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<long double>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};

//! pointer is also basic type, and so the trait result is always @struct TrueType
# ifdef GECO_CLASS_PARTIAL_SPECIALIZATION
template<class Type>
struct type_traitor<Type*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
# else
GECO_TEMPLATE_NULL struct type_traitor<char*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<signed char*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<unsigned char*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<const char*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<const signed char*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
GECO_TEMPLATE_NULL struct type_traitor<const unsigned char*>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};
# endif //! GECO_CLASS_PARTIAL_SPECIALIZATION

//! The following could be written in terms of numeric_limits.  
//! We're doing it separately to reduce the number of dependencies.
template<class Type>
struct IsInteger
{
    typedef false_type Integer;
};

# ifndef GECO_NO_BOOL
GECO_TEMPLATE_NULL struct IsInteger<bool>
{
    typedef true_type Integer;
};
# endif

# ifdef GECO_HAS_WCHAR_T
GECO_TEMPLATE_NULL struct IsInteger<wchar_t>
{
    typedef true_type Integer;
};
# endif

GECO_TEMPLATE_NULL struct IsInteger<char>
{
    typedef true_type Integer;
};
GECO_TEMPLATE_NULL struct IsInteger<unsigned char>
{
    typedef true_type Integer;
};
GECO_TEMPLATE_NULL struct IsInteger<signed char>
{
    typedef true_type Integer;
};

GECO_TEMPLATE_NULL struct IsInteger<unsigned short>
{
    typedef true_type Integer;
};
GECO_TEMPLATE_NULL struct IsInteger<short>
{
    typedef true_type Integer;
};

GECO_TEMPLATE_NULL struct IsInteger<unsigned int>
{
    typedef true_type Integer;
};
GECO_TEMPLATE_NULL struct IsInteger<int>
{
    typedef true_type Integer;
};

GECO_TEMPLATE_NULL struct IsInteger<unsigned long>
{
    typedef true_type Integer;
};
GECO_TEMPLATE_NULL struct IsInteger<long>
{
    typedef true_type Integer;
};

# ifndef GECO_LONG_LONG
GECO_TEMPLATE_NULL struct IsInteger<unsigned long long>
{
    typedef true_type Integer;
};
GECO_TEMPLATE_NULL struct IsInteger<long long>
{
    typedef true_type Integer;
};
# endif

GECO_END_NAMESPACE
# endif //! __GECO__TYPE_TRAITS_H

