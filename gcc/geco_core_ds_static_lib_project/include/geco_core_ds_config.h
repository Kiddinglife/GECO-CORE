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
 * and its documentation for GECO_STL purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for GECO_STL
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

# ifndef __GECO_STL_CONFIG_H
# define __GECO_STL_CONFIG_H

// Flags:

// __GECO_STL_NO_BOOL
// defined if the compiler doesn't have bool as a builtin type.

// __GECO_STL_HAS_WCHAR_T
// defined if the compier has wchar_t as a builtin type.

// __GECO_STL_NO_DRAND48
// defined if the compiler doesn't have the drand48 function.
// @See http://blog.csdn.net/jimmyblind/article/details/5550042 
// for details about drand48() function

// __GECO_STL_STATIC_TEMPLATE_MEMBER_BUG
// defined if the compiler can't handle static members of template classes.

// __GECO_STL_STATIC_CONST_INIT_BUG: 
// defined if the compiler can't handle a constant-initializer in the declaration 
// of a static const data member

// __GECO_STL_CLASS_PARTIAL_SPECIALIZATION 
// defined if the compiler supports partial specialization of template classes.

// __GECO_STL_PARTIAL_SPECIALIZATION_SYNTAX
// defined if the compiler supports partial specialization syntax for full 
// specialization of class templates. 
// (Even if it doesn't actually support partial specialization itself.)

//  __GECO_STL_FUNCTION_TMPL_PARTIAL_ORDER 
// defined if the compiler supports partial ordering of function templates.
// (a.k.a partial specialization of function templates.)

// __GECO_STL_MEMBER_TEMPLATES
// defined if the compiler supports template member functions of classes.

// __GECO_STL_MEMBER_TEMPLATE_CLASSES
// defined if the compiler supports nested classes that are member
// templates of other classes.

// __GECO_STL_TEMPLATE_FRIENDS
// defined if the compiler supports templatized friend declarations.

// __GECO_STL_EXPLICIT_FUNCTION_TMPL_ARGS 
// defined if the compiler supports calling a function template by providing its 
// template arguments explicitly.

// __GECO_STL_LIMITED_DEFAULT_TEMPLATES
// defined if the compiler is unable to handle default template parameters
// that depend on previous template parameters.
// \code
// template <class _Result, 
// class _Arg1 __GECO_STL_DEPENDENT_DEFAULT_TMPL(_Result),
// class _Arg2 __GECO_STL_DEPENDENT_DEFAULT_TMPL(_Arg1) >
//\code

// __GECO_STL_NON_TYPE_TMPL_PARAM_BUG
// defined if the compiler has trouble with
// function template argument deduction for non-type template parameters.

// __SGI_GECO_STL_NO_ARROW_OPERATOR
// defined if the compiler is unable to support the -> operator for iterators.

// __GECO_STL_DEFAULT_CONSTRUCTOR_BUG
// defined if T() does not work properly when T is a builtin type.

//  __GECO_STL_USE_EXCEPTIONS
// defined if the compiler (in the current compilation mode) supports exceptions.

// __GECO_STL_USE_NAMESPACES
// defined if the compiler has the necessary support for namespaces.

// __GECO_STL_NO_EXCEPTION_HEADER
//  defined if the compiler does not have 
// a standard-conforming header <exception>

//  __GECO_STL_NO_BAD_ALLOC 
// defined if the compiler does not have a <new> header, 
// or if <new> does not contain a bad_alloc class. 
// If a bad_alloc class exists, it is assumed to be in namespace std.

// __GECO_STL_LONG_LONG 
// if the compiler has long long and unsigned long long
// types.  (They're not in the C++ standard, but they are expected to be 
// included in the forthcoming C9X standard.)

// __GECO_STL_THREADS is defined if thread safety is needed.

// __GECO_STL_VOLATILE is defined to be "volatile" if threads are being
// used, and the empty string otherwise.

// __GECO_STL_NO_USING_CLAUSE_IN_CLASS 
// The compiler does not handle "using" clauses inside of class definitions.

//  __GECO_STL_NO_FRIEND_TEMPLATE_CLASS 
// The compiler does not handle friend declaractions 
// where the friend is a template class.

// __GECO_STL_NO_FUNCTION_PTR_IN_CLASS_TEMPLATE
// The compiler does not support the use of a function pointer type 
// as the argument for a template.

// __GECO_STL_MEMBER_TEMPLATE_KEYWORD 
// standard C++ requires the template keyword in a few new places (14.2.4).
// This flag is set for compilers that support (and require) this usage.

// __GECO_STL_USE_SGI_ALLOCATORS 
// User-settable macros that control compilation. if defined, then the GECO_STL 
// will use older SGI-style allocators, instead of standard-conforming allocators,
// even if the compiler supports all of the language features needed
// for standard-conforming allocators.

// __GECO_STL_NO_NAMESPACES
// if defined, don't put the library in namespace
// std, even if the compiler supports namespaces.

// __GECO_STL_NO_RELOPS_NAMESPACE 
// if defined, don't put the relational operator templates (>, <=. >=, !=) 
// in namespace std::rel_ops, even if the compiler supports namespaces 
// and partial ordering of function templates.

// __GECO_STL_ASSERTIONS
// if defined, then enable runtime checking through the __geco_stl_assert macro.

// __GECO_STL_SGI_THREADS
// defined if this is being compiled for an SGI IRIX
// system in multithreaded mode, using native SGI threads instead of  pthreads.
// this is used only for SGI compGECO_GECO_STL's specific system

// __GECO_STL_WIN32THREADS
// defined if this is being compiled on a WIN32 compiler in multithreaded mode.

// __GECO_STL_PTHREADS
// defined if we should use portable pthreads synchronization.

//  __GECO_STL_UITHREADS 
// defined if we should use UI / solaris / UnixWare threads
// synchronization.  UIthreads are similar to pthreads, but are based 
// on an earlier version of the Posix threads standard.

// _PTHREADS
// if defined, use Posix threads for multithreading support.

// _UITHREADS
// if defined, use SCO/Solaris/UI threads for multithreading support

//  _NOTHREADS 
// if defined, don't use GECO_GECO_STL multithreading support. 

//   __GECO_STL_USE_CONCEPT_CHECKS 
//  enables some extra compile-time error
//  checking to make sure that user-defined template arguments satisfy
//  all of the appropriate requirements.  This may result in more
//  comprehensible error messages.  It incurs no runtime overhead.  This 
//  feature requires member templates and partial specialization.

// _GECO_STL_NO_CONCEPT_CHECKS
// if defined, disables the error checking that
// we get from __GECO_STL_USE_CONCEPT_CHECKS.

// __GECO_STL_USE_NEW_IOSTREAMS
// if defined, then the GECO_STL will use new, standard-conforming iostreams
// (e.g. the <iosfwd> header).  If not defined, the GECO_STL will use old cfront-style 
// iostreams (e.g. the <iostream.h> header).

// Other macros defined by this file:

// bool, true, and false, if __GECO_STL_NO_BOOL is defined.

// typename, as a null macro if it's not already a keyword.

// explicit, as a null macro if it's not already a keyword.

// namespace-related macros (__STD, __GECO_STL_BEGIN_NAMESPACE, etc.)

// exception-related macros (__GECO_STL_TRY, __GECO_STL_UNWIND, etc.)

// __geco_stl_assert
// either as a test or as a null macro, depending on
// whether or not __GECO_STL_ASSERTIONS is defined.

# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __GECO_STL_PTHREADS
# endif

# if defined(_UITHREADS) && !defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __GECO_STL_UITHREADS
# endif

// SGI complier
# if defined(__sgi) && !defined(__GNUC__)
#   include <standards.h>
#   if !defined(_BOOL)
#     define __GECO_STL_NO_BOOL
#   endif
#   if defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32
#     define __GECO_STL_STATIC_CONST_INIT_BUG
#   endif
#   if defined(_WCHAR_T_IS_KEYWORD)
#     define __GECO_STL_HAS_WCHAR_T 
#   endif
#   if !defined(_TYPENAME_IS_KEYWORD)
#     define __GECO_STL_NEED_TYPENAME
#   endif
#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#     define __GECO_STL_CLASS_PARTIAL_SPECIALIZATION
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#     define __GECO_STL_FUNCTION_TMPL_PARTIAL_ORDER
#   endif
#   ifdef _MEMBER_TEMPLATES
#     define __GECO_STL_MEMBER_TEMPLATES
#     define __GECO_STL_TEMPLATE_FRIENDS
#     define __GECO_STL_MEMBER_TEMPLATE_CLASSES
#   endif
#   if defined(_MEMBER_TEMPLATE_KEYWORD)
#     define __GECO_STL_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if defined(_STANDARD_C_PLUS_PLUS)
#     define __GECO_STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#     define __GECO_STL_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if COMPILER_VERSION < 720 || (defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32)
#     define __GECO_STL_DEFAULT_CONSTRUCTOR_BUG
#   endif
#   if !defined(_EXPLICIT_IS_KEYWORD)
#     define __GECO_STL_NEED_EXPLICIT
#   endif
#   ifdef __EXCEPTIONS
#     define __GECO_STL_USE_EXCEPTIONS
#   endif
#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
#     define __GECO_STL_HAS_NAMESPACES
#   endif 
#   if (_COMPILER_VERSION < 721) || \
    !defined(__GECO_STL_HAS_NAMESPACES) || defined(__GECO_STL_NO_NAMESPACES)
#     define __GECO_STL_NO_EXCEPTION_HEADER
#   endif
#   if _COMPILER_VERSION < 730 || !defined(_STANDARD_C_PLUS_PLUS) || \
      !defined(_NAMESPACES)
#     define __GECO_STL_NO_BAD_ALLOC
#   endif
#   if !defined(_NOTHREADS) && !defined(__GECO_STL_PTHREADS)
#     define __GECO_STL_SGI_THREADS
#   endif
#   if defined(_LONGLONG) && defined(_SGIAPI) && _SGIAPI
#     define __GECO_STL_LONG_LONG
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __GECO_STL_USE_NEW_IOSTREAMS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __GECO_STL_CAN_THROW_RANGE_ERRORS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __SGI_GECO_STL_USE_AUTO_PTR_CONVERSIONS
#   endif
# endif // sgi complier

/*
 * Jochen Schlick '1999  - added new #defines (__GECO_STL)_UITHREADS (for
 *                         providing SCO / Solaris / UI thread support)
 *                       - added the necessary defines for the SCO UDK 7
 *                         compiler (and its template friend behavior)
 *                       - all UDK7 specific GECO_STL changes are based on the
 *                         macro __USLC__ being defined
 *
 SCO Unix是在国内比较有名气的操作系统，因为他是当时能运行在Intel的平台之一，并且较早进入中国市场。它的历史可以追溯到MicroSoft开发的Xienx，Xienx是运行在Intel平台上的一种基于Unix V 6的系统，后来Xienx开发部门独立出来成立了SCO公司，并基于AT&T System VR3.2开发了SCO Unix，其最新的版本为增强了图形接口的SCO OpenServer 5.0.4。此时AT&T已经将它们负责Unix的部门USL(Unix系统实验室)，卖给了Novell公司，它们的Unix被更名为UnixWare ，但是Novell正逢经营问题，不得不将UnixWare再次卖给SCO。SCO之所以能占有市场，并不是其产品特别出色，而是因为在小型机特别昂贵的年代，对一些追求稳定的行业来说，使用SCO能在x86上运行，可以节约大量成本。因此早期的银行、金融行业的终端大多是使用SCO的。而最近SCO的名声越来越坏，只因被更加优秀且同样能运行于x86的Linux抢走大量份额，大家知道知道吃不饱的狗是会乱咬人的。不过可惜最后授权没强行推销出去几份，反而得了个$CO之名。而Novell在购买UnixWare之后的一个重要举动是将Unix商标赠送给一个非盈利的Unix组织X/Open，结束了USL与BSD以及其他厂商的纷争。
 */
// SCO UDK 7 compiler (UnixWare 7x, OSR 5, UnixWare 2x)
# if defined(__USLC__)
#     define __GECO_STL_HAS_WCHAR_T 
#     define __GECO_STL_CLASS_PARTIAL_SPECIALIZATION
#     define __GECO_STL_PARTIAL_SPECIALIZATION_SYNTAX
#     define __GECO_STL_FUNCTION_TMPL_PARTIAL_ORDER
#     define __GECO_STL_MEMBER_TEMPLATES
#     define __GECO_STL_MEMBER_TEMPLATE_CLASSES
#     define __GECO_STL_USE_EXCEPTIONS
#     define __GECO_STL_HAS_NAMESPACES
#     define __GECO_STL_USE_NAMESPACES
#     define __GECO_STL_LONG_LONG
#     if defined(_REENTRANT)
#           define _UITHREADS     /* if      UnixWare < 7.0.1 */
#           define __GECO_STL_UITHREADS
//   use the following defines instead of the UI threads defines when
//   you want to use POSIX threads
//#         define _PTHREADS      /* only if UnixWare >=7.0.1 */
//#         define __GECO_STL_PTHREADS
#     endif
# endif

// GCC
# ifdef __GNUC__
#   define __GECO_STL_MEMBER_TEMPLATES
#   define __GECO_STL_MEMBER_TEMPLATE_CLASSES
#   define __GECO_STL_TEMPLATE_FRIENDS
#   define __GECO_STL_CLASS_PARTIAL_SPECIALIZATION
#   define __GECO_STL_USE_EXCEPTIONS
#   define __GECO_STL_HAS_NAMESPACES
# endif

# if defined(__ICL) // Intel compiler, which uses the EDG front end.
#   define __GECO_STL_LONG_LONG 
#   define __GECO_STL_MEMBER_TEMPLATES
#   define __GECO_STL_MEMBER_TEMPLATE_CLASSES
#   define __GECO_STL_TEMPLATE_FRIENDS
#   define __GECO_STL_FUNCTION_TMPL_PARTIAL_ORDER
#   define __GECO_STL_CLASS_PARTIAL_SPECIALIZATION
#   define __GECO_STL_NO_DRAND48
#   define __GECO_STL_HAS_NAMESPACES
#   define __GECO_STL_USE_EXCEPTIONS
#   define __GECO_STL_MEMBER_TEMPLATE_KEYWORD
#   ifdef _CPPUNWIND
#     define __GECO_STL_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define __GECO_STL_WIN32THREADS
#   endif
# endif

// Mingw32, egcs compiler using the Microsoft C runtime
# if defined(__MINGW32__)
#   define __GECO_STL_NO_DRAND48
#   ifdef _MT
#     define __GECO_STL_WIN32THREADS
#   endif
# endif

// Cygwin32, egcs compiler on MS Windows
# if defined(__CYGWIN__)
#   define __GECO_STL_NO_DRAND48
# endif

// Microsoft compiler. 
# if defined(_MSC_VER) && !defined(__ICL) && !defined(__MWERKS__)

// Because of a Microsoft front end bug, we must not provide a
// namespace qualifier when declaring a friend function.
#   define __STD_QUALIFIER

#   define __GECO_STL_NO_DRAND48
#   define __GECO_STL_STATIC_CONST_INIT_BUG
#   define __GECO_STL_NEED_TYPENAME
#   define __GECO_STL_NO_USING_CLAUSE_IN_CLASS
#   define __GECO_STL_NO_FRIEND_TEMPLATE_CLASS 
#   define __GECO_STL_NON_TYPE_TMPL_PARAM_BUG
#   define __SGI_GECO_STL_NO_ARROW_OPERATOR
#   define __GECO_STL_DEFAULT_CONSTRUCTOR_BUG

#   ifdef _CPPUNWIND
#		define __GECO_STL_USE_EXCEPTIONS
#   endif

#   ifdef _MT
#		define __GECO_STL_WIN32THREADS
#   endif

// 1000 is version 4.0, 
// 1100 is 5.0, 
// 1200 is 6.0.
#   if _MSC_VER < 1100 
#     define __GECO_STL_NEED_EXPLICIT
#     define __GECO_STL_NO_BOOL
#     define __GECO_STL_NO_BAD_ALLOC
#   endif

#   if _MSC_VER > 1000
// c standard library header 
//@see http://blog.csdn.net/acmicpc123/article/details/50205729 for details
#     include <yvals.h>
#     define __GECO_STL_DONT_USE_BOOL_TYPEDEF
#   endif

#   if _MSC_VER >= 1200
#     define __GECO_STL_PARTIAL_SPECIALIZATION_SYNTAX
#     define __GECO_STL_HAS_NAMESPACES
#     define __GECO_STL_CAN_THROW_RANGE_ERRORS
#     define NOMINMAX
#     undef min
#     undef max
// disable warning 'initializers put in unrecognized initialization area'
#     pragma warning ( disable : 4075 )
// disable warning 'empty controlled statement found'
#     pragma warning ( disable : 4390 )
// disable warning 'debug symbol greater than 255 chars'
#     pragma warning ( disable : 4786 )
#   endif

#   if _MSC_VER < 1100
#     define __GECO_STL_NO_EXCEPTION_HEADER
#     define __GECO_STL_NO_BAD_ALLOC
#   endif

# endif // Microsoft compiler. 

# if defined(__BORLANDC__)
#     define __GECO_STL_NO_BAD_ALLOC
#     define __GECO_STL_NO_DRAND48
#     define __GECO_STL_DEFAULT_CONSTRUCTOR_BUG
#   if __BORLANDC__ >= 0x540 /* C++ Builder 4.0 */
#     define __GECO_STL_CLASS_PARTIAL_SPECIALIZATION
#     define __GECO_STL_FUNCTION_TMPL_PARTIAL_ORDER
#     define __GECO_STL_EXPLICIT_FUNCTION_TMPL_ARGS
#     define __GECO_STL_MEMBER_TEMPLATES
#     define __GECO_STL_TEMPLATE_FRIENDS
#   else
#     define __GECO_STL_NEED_TYPENAME
#     define __GECO_STL_LIMITED_DEFAULT_TEMPLATES
#     define __SGI_GECO_STL_NO_ARROW_OPERATOR
#     define __GECO_STL_NON_TYPE_TMPL_PARAM_BUG
#   endif
#   ifdef _CPPUNWIND
#     define __GECO_STL_USE_EXCEPTIONS
#   endif
#   ifdef __MT__
#     define __GECO_STL_WIN32THREADS
#   endif
# endif

# if defined(__GECO_STL_NO_BOOL) && !defined(__GECO_STL_DONT_USE_BOOL_TYPEDEF)
typedef int bool;
#   define true 1
#   define false 0
# endif

# ifdef __GECO_STL_NEED_TYPENAME
#   define typename
# endif

//for example:
//template <class _Result,
//class _Arg1 __GECO_STL_DEPENDENT_DEFAULT_TMPL(_Result),
//class _Arg2 __GECO_STL_DEPENDENT_DEFAULT_TMPL(_Arg1) >
# ifdef __GECO_STL_LIMITED_DEFAULT_TEMPLATES
#   define __GECO_STL_DEPENDENT_DEFAULT_TMPL(_Tp)
# else
#   define __GECO_STL_DEPENDENT_DEFAULT_TMPL(_Tp) = _Tp
# endif

# ifdef __GECO_STL_MEMBER_TEMPLATE_KEYWORD
#   define __GECO_STL_TEMPLATE template
# else
#   define __GECO_STL_TEMPLATE
# endif

# ifdef __GECO_STL_NEED_EXPLICIT
#   define explicit
# endif

# ifdef __GECO_STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __GECO_STL_NULL_TMPL_ARGS <>
# else
#   define __GECO_STL_NULL_TMPL_ARGS
# endif

# if defined(__GECO_STL_CLASS_PARTIAL_SPECIALIZATION) \
|| defined (__GECO_STL_PARTIAL_SPECIALIZATION_SYNTAX)
#   define __GECO_STL_TEMPLATE_NULL template<>
# else
#   define __GECO_STL_TEMPLATE_NULL
# endif

// Use standard-conforming allocators if we have the necessary language
// features.  __GECO_STL_USE_SGI_ALLOCATORS is a hook so that users can 
// disable new-style allocators, and continue to use the same kind of
// allocators as before, without having to edit library headers.
# if defined(__GECO_STL_CLASS_PARTIAL_SPECIALIZATION) && \
     defined(__GECO_STL_MEMBER_TEMPLATES) && \
     defined(__GECO_STL_MEMBER_TEMPLATE_CLASSES) && \
    !defined(__GECO_STL_NO_BOOL) && \
    !defined(__GECO_STL_NON_TYPE_TMPL_PARAM_BUG) && \
    !defined(__GECO_STL_LIMITED_DEFAULT_TEMPLATES) && \
    !defined(__GECO_STL_USE_SGI_ALLOCATORS) 
#   define __GECO_STL_USE_STD_ALLOCATORS
# endif

# ifndef __GECO_STL_DEFAULT_ALLOCATOR
#   ifdef __GECO_STL_USE_STD_ALLOCATORS
#     define __GECO_STL_DEFAULT_ALLOCATOR(T) allocator< T >
#   else
#     define __GECO_STL_DEFAULT_ALLOCATOR(T) alloc
#   endif
# endif

// __GECO_STL_NO_NAMESPACES is a hook so that users can disable namespaces
// without having to edit library headers. 
// __GECO_STL_NO_RELOPS_NAMESPACE is a hook so that users can disable the
// std::rel_ops namespace, keeping the relational operator template in namespace std, 
// without having to edit library headers.
# if defined(__GECO_STL_HAS_NAMESPACES) && !defined(__GECO_STL_NO_NAMESPACES)
#   define __GECO_STL_USE_NAMESPACES
#   define __STD std
#   define __GECO_STL_BEGIN_NAMESPACE namespace std {
#   define __GECO_STL_END_NAMESPACE }
#   if defined(__GECO_STL_FUNCTION_TMPL_PARTIAL_ORDER) && \
       !defined(__GECO_STL_NO_RELOPS_NAMESPACE)
#     define __GECO_STL_USE_NAMESPACE_FOR_RELOPS
#     define __GECO_STL_BEGIN_RELOPS_NAMESPACE namespace std { namespace rel_ops {
#     define __GECO_STL_END_RELOPS_NAMESPACE } }
#     define __STD_RELOPS std::rel_ops
#   else /* Use std::rel_ops namespace */
#     define __GECO_STL_USE_NAMESPACE_FOR_RELOPS
#     define __GECO_STL_BEGIN_RELOPS_NAMESPACE namespace std {
#     define __GECO_STL_END_RELOPS_NAMESPACE }
#     define __STD_RELOPS std
#   endif /* Use std::rel_ops namespace */
# else
#   define __STD 
#   define __GECO_STL_BEGIN_NAMESPACE 
#   define __GECO_STL_END_NAMESPACE 
#   undef  __GECO_STL_USE_NAMESPACE_FOR_RELOPS
#   define __GECO_STL_BEGIN_RELOPS_NAMESPACE 
#   define __GECO_STL_END_RELOPS_NAMESPACE 
#   define __STD_RELOPS 
#   undef  __GECO_STL_USE_NAMESPACES
# endif

// Some versions of the EDG front end sometimes require an explicit
// namespace spec where they shouldn't.  This macro facilitates that.
// If the bug becomes irrelevant, then all uses of __STD_QUALIFIER
// should be removed.  The 7.3 beta SGI compiler has this bug, but the
// MR version is not expected to have it.
# if defined(__GECO_STL_USE_NAMESPACES) && !defined(__STD_QUALIFIER)
#   define __STD_QUALIFIER std::
# else
#   define __STD_QUALIFIER
# endif

# ifdef __GECO_STL_USE_EXCEPTIONS
#   define __GECO_STL_TRY try
#   define __GECO_STL_CATCH_ALL catch(...)
#   define __GECO_STL_THROW(x) throw x
#   define __GECO_STL_RETHROW throw
#   define __GECO_STL_NOTHROW throw()
#   define __GECO_STL_UNWIND(action) catch(...) { action; throw; }
# else
#   define __GECO_STL_TRY 
#   define __GECO_STL_CATCH_ALL if (false)
#   define __GECO_STL_THROW(x) 
#   define __GECO_STL_RETHROW 
#   define __GECO_STL_NOTHROW 
#   define __GECO_STL_UNWIND(action) 
# endif

#ifdef __GECO_STL_ASSERTIONS
# include <stdio.h>
# define __geco_stl_assert(expr) \
if (!(expr)){ fprintf(stderr, "%s:%d GECO_STL assertion failure: %s\n",__FILE__,__LINE__,# expr);abort(); }
#else
# define __geco_stl_assert(expr)
#endif

# endif /* __GECO_STL_CONFIG_H */
