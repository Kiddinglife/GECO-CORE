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

# ifndef __GECO_CONFIG_H
# define __GECO_CONFIG_H

//! Flags.

//! @def __GECO_NO_BOOL
//! @brief defined if the compiler doesn't have bool as a builtin type.

//! @def __GECO_HAS_WCHAR_T
//! @brief defined if the compier has wchar_t as a builtin type.

//! __GECO_NO_DRAND48
//! @brief defined if the compiler doesn't have the drand48 function.
//! @See http://!blog.csdn.net/jimmyblind/article/details/5550042 
//! for details about drand48() function

//! @def __GECO_STATIC_TEMPLATE_MEMBER_BUG
//! @brief defined if the compiler can't handle static members of template classes.

//! @def __GECO_STATIC_CONST_INIT_BUG: 
//! @brief defined if the compiler can't handle a constant-initializer in the declaration 
//! of a static const data member

//! @def __GECO_CLASS_PARTIAL_SPECIALIZATION 
//! @brief defined if the compiler supports partial specialization of template classes.
//! @code
//!  generic template.
//!  template<class I, class O>
//!  struct testClass{...};
//!  particial-specification 1
//!  template <class T>
//!  struct testClass <T*, const T&>{...};
//!  particial-specification 2
//!  template <class T>
//!  struct testClass <const T*, T*>{...};
//! @endcode

//! @def __GECO_PARTIAL_SPECIALIZATION_SYNTAX
//! @brief defined if the compiler supports partial specialization syntax for full 
//! specialization of class templates. 
//! (Even if it doesn't actually support partial specialization itself.)

//! @def __GECO_FUNCTION_TMPL_PARTIAL_ORDER 
//! \brief defined if the compiler supports partial ordering of function templates.
//! (a.k.a partial specialization of function templates.)
//! @code
//! template <class T>
//! struct testClass { void swap(vector<T>){...} };
//! #ifdef __GECO_FUNCTION_TMPL_PARTIAL_ORDER
//! template <class T>
//! inline void swap (vector<T>& x, vecotr<T>& y) { x.swap(y); }
//! #endif
//! @endcode

//! @def __GECO_MEMBER_TEMPLATES
//! @brief defined if the compiler supports template member functions of classes.

//! @def __GECO_MEMBER_TEMPLATE_CLASSES
//! @brief defined if the compiler supports nested classes that are member
//! templates of other classes.

//! @def  __GECO_TEMPLATE_FRIENDS
//! @brief  defined if the compiler supports templatized friend declarations.

//! @def __GECO_EXPLICIT_FUNCTION_TMPL_ARGS 
//! @brief defined if the compiler supports calling a function template by providing its 
//! template arguments explicitly.
//! @code
//! template <class T, class Sequence>
//! bool operator==(const stack<T, Sequence>& x);
//!
//! template < class T, class Sequence = deque<T>>
//! class stack {
//! //!this is correct
//! friend bool operator== <T> (const stack<T>&, const stack<T>&);
//! //!this is alos correct
//! friend bool opeartor==<T> (const statck<T>&, const stack<T>&);
//! //!this is alos correct
//! friend bool opeartor==<> (const statck&, const stack&);
//! }
//! @endcode

//! @def  __GECO_LIMITED_DEFAULT_TEMPLATES
//! @brief defined if the compiler is unable to handle default template parameters
//! that depend on previous template parameters.
//! @code
//! template<class T, class Sequence = deque<T>>
//!@endcode

//! @def  __GECO_NON_TYPE_TMPL_PARAM_BUG
//! @brief defined if the compiler has trouble with
//! function template argument deduction for non-type template parameters.
//! \code
//! template <class T, size_t BufSize = 0>
//! struct __deque_iterator { typedef __deque_iterator<T, BufSize> iterator;};
//! \endcode

//! @def  __SGI_GECO_NO_ARROW_OPERATOR
//! @brief defined if the compiler is unable to support the -> operator for iterators.

//! @def  __GECO_DEFAULT_CONSTRUCTOR_BUG
//! @brief defined if T() does not work properly when T is a builtin type.

//! @def  __GECO_USE_EXCEPTIONS
//! @brief defined if the compiler (in the current compilation mode) supports exceptions.

//! @def  __GECO_USE_NAMESPACES
//! @brief defined if the compiler has the necessary support for namespaces.

//! @def  s__GECO_NO_EXCEPTION_HEADER
//! @brief defined if the compiler does not have 
//! a standard-conforming header <exception>.

//! @def  __GECO_NO_BAD_ALLOC 
//! @brief defined if the compiler does not have a <new> header, 
//! or if <new> does not contain a bad_alloc class. 
//! If a bad_alloc class exists, it is assumed to be in namespace geco.

//! @def  __GECO_LONG_LONG 
//! @brief if the compiler has long long and unsigned long long
//! types (They're not in the C++ standard, but they are expected to be 
//! included in the forthcoming C9X standard).

//! @def __GECO_THREADS
//! @brief defined if thread safety is needed.

//! @def  __GECO_VOLATILE 
//! @brief defined to be "volatile" if threads are being used, and the empty string otherwise.

//! @def  __GECO_NO_USING_CLAUSE_IN_CLASS 
//! @brief The compiler does not handle "using" clauses inside of class definitions.

//!  @def  __GECO_NO_FRIEND_TEMPLATE_CLASS 
//! @brief The compiler does not handle friend declaractions 
//! where the friend is a template class.

//! @def  __GECO_NO_FUNCTION_PTR_IN_CLASS_TEMPLATE
//! @brief The compiler does not support the use of a function pointer type 
//! as the argument for a template.

//! @def __GECO_MEMBER_TEMPLATE_KEYWORD 
//! @brief standard C++ requires the template keyword in a few new places (14.2.4),
//! this flag is set for compilers that support (and require) this usage.

//! @def  __GECO_USE_SGI_ALLOCATORS 
//! @brief User-settable macros that control compilation. 
//! if defined, then the GECO will use older SGI-style allocators,
//! instead of standard-conforming allocators,
//! even if the compiler supports all of the language features needed
//! for standard-conforming allocators.

//! @def __GECO_NO_NAMESPACES
//! @brief if defined, don't put the library in namespace
//! geco, even if the compiler supports namespaces.

//! @def  __GECO_NO_RELOPS_NAMESPACE 
//! @brief if defined, don't put the relational operator templates (>, <=. >=, !=) 
//! in namespace geco::rel_ops, even if the compiler supports namespaces 
//! and partial ordering of function templates.

//! @def  __GECO_ASSERTIONS
//! @brief if defined, then enable runtime checking through the __GECO_assert macro.

//! @def  __GECO_SGI_THREADS
//! @brief defined if this is being compiled for an SGI IRIX
//! system in multithreaded mode, using native SGI threads instead of  pthreads,
//! this is used only for SGI  specific system.
//! @todo maybe not need,can be deleted.

//! @def  __GECO_WIN32THREADS
//! @brief defined if this is being compiled on a WIN32 compiler in multithreaded mode.

//! @def __GECO_PTHREADS
//! @brief defined if we should use portable pthreads synchronization.

//! @def __GECO_UITHREADS 
//! @brief defined if we should use UI / solaris / UnixWare threads synchronization.  
//! UIthreads are similar to pthreads, but are based 
//! on an earlier version of the Posix threads standard.

//! @def  _PTHREADS
//! @brief if defined, use Posix threads for multithreading support.

//! @def  _UITHREADS
//! @brief if defined, use SCO/Solaris/UI threads for multithreading support

//!  @def  _NOTHREADS 
//! @brief if defined, don't use GECO_GECO multithreading support. 

//!  @def  __GECO_USE_CONCEPT_CHECKS 
//!  enables some extra compile-time error
//!  checking to make sure that user-defined template arguments satisfy
//!  all of the appropriate requirements.  This may result in more
//!  comprehensible error messages.  It incurs no runtime overhead.  This 
//!  feature requires member templates and partial specialization.

//! @def _GECO_NO_CONCEPT_CHECKS
//! @brief if defined, disables the error checking that
//! we get from __GECO_USE_CONCEPT_CHECKS.

//! @def  __GECO_USE_NEW_IOSTREAMS
//! if defined, then the GECO will use new, standard-conforming iostreams
//! (e.g. the <iosfwd> header).  If not defined, the GECO will use old cfront-style 
//! iostreams (e.g. the <iostream.h> header).

//! @def __GECO_NO_BOOL 
//! @brief bool, true, and false, if defined.

//! typename, as a null macro if it's not already a keyword.
//! explicit, as a null macro if it's not already a keyword.

//! @def __GECO
//! @brief namespace-related macros

//! @def __GECO_BEGIN_NAMESPACE
//! @brief namespace-related macros

//! @def __GECO_TRY
//! @brief exception-related macros

//! @def __GECO_UNWIND
//! @brief exception-related macros

//! @def __GECO_assert
//! @brief either as a test or as a null macro, depending on
//! whether or not __GECO_ASSERTIONS is defined.

# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __GECO_PTHREADS
# endif

# if defined(_UITHREADS) && !defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __GECO_UITHREADS
# endif

//! SGI complier
# if defined(__sgi) && !defined(__GNUC__)
#   include <standards.h>
#   if !defined(_BOOL)
#     define __GECO_NO_BOOL
#   endif
#   if defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32
#     define __GECO_STATIC_CONST_INIT_BUG
#   endif
#   if defined(_WCHAR_T_IS_KEYWORD)
#     define __GECO_HAS_WCHAR_T 
#   endif
#   if !defined(_TYPENAME_IS_KEYWORD)
#     define __GECO_NEED_TYPENAME
#   endif
#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#     define __GECO_CLASS_PARTIAL_SPECIALIZATION
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#     define __GECO_FUNCTION_TMPL_PARTIAL_ORDER
#   endif
#   ifdef _MEMBER_TEMPLATES
#     define __GECO_MEMBER_TEMPLATES
#     define __GECO_TEMPLATE_FRIENDS
#     define __GECO_MEMBER_TEMPLATE_CLASSES
#   endif
#   if defined(_MEMBER_TEMPLATE_KEYWORD)
#     define __GECO_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if defined(_STANDARD_C_PLUS_PLUS)
#     define __GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#     define __GECO_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if COMPILER_VERSION < 720 || (defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32)
#     define __GECO_DEFAULT_CONSTRUCTOR_BUG
#   endif
#   if !defined(_EXPLICIT_IS_KEYWORD)
#     define __GECO_NEED_EXPLICIT
#   endif
#   ifdef __EXCEPTIONS
#     define __GECO_USE_EXCEPTIONS
#   endif
#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
#     define __GECO_HAS_NAMESPACES
#   endif 
#   if (_COMPILER_VERSION < 721) || \
    !defined(__GECO_HAS_NAMESPACES) || defined(__GECO_NO_NAMESPACES)
#     define __GECO_NO_EXCEPTION_HEADER
#   endif
#   if _COMPILER_VERSION < 730 || !defined(_STANDARD_C_PLUS_PLUS) || \
      !defined(_NAMESPACES)
#     define __GECO_NO_BAD_ALLOC
#   endif
#   if !defined(_NOTHREADS) && !defined(__GECO_PTHREADS)
#     define __GECO_SGI_THREADS
#   endif
#   if defined(_LONGLONG) && defined(_SGIAPI) && _SGIAPI
#     define __GECO_LONG_LONG
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __GECO_USE_NEW_IOSTREAMS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __GECO_CAN_THROW_RANGE_ERRORS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __SGI_GECO_USE_AUTO_PTR_CONVERSIONS
#   endif
# endif //! sgi complier

/*
 * Jochen Schlick '1999  - added new #defines (__GECO)_UITHREADS (for
 *                         providing SCO / Solaris / UI thread support)
 *                       - added the necessary defines for the SCO UDK 7
 *                         compiler (and its template friend behavior)
 *                       - all UDK7 specific GECO changes are based on the
 *                         macro __USLC__ being defined
 *
 SCO Unix是在国内比较有名气的操作系统，因为他是当时能运行在Intel的平台之一，并且较早进入中国市场。它的历史可以追溯到MicroSoft开发的Xienx，Xienx是运行在Intel平台上的一种基于Unix V 6的系统，后来Xienx开发部门独立出来成立了SCO公司，并基于AT&T System VR3.2开发了SCO Unix，其最新的版本为增强了图形接口的SCO OpenServer 5.0.4。此时AT&T已经将它们负责Unix的部门USL(Unix系统实验室)，卖给了Novell公司，它们的Unix被更名为UnixWare ，但是Novell正逢经营问题，不得不将UnixWare再次卖给SCO。SCO之所以能占有市场，并不是其产品特别出色，而是因为在小型机特别昂贵的年代，对一些追求稳定的行业来说，使用SCO能在x86上运行，可以节约大量成本。因此早期的银行、金融行业的终端大多是使用SCO的。而最近SCO的名声越来越坏，只因被更加优秀且同样能运行于x86的Linux抢走大量份额，大家知道知道吃不饱的狗是会乱咬人的。不过可惜最后授权没强行推销出去几份，反而得了个$CO之名。而Novell在购买UnixWare之后的一个重要举动是将Unix商标赠送给一个非盈利的Unix组织X/Open，结束了USL与BSD以及其他厂商的纷争。
 */
//! SCO UDK 7 compiler (UnixWare 7x, OSR 5, UnixWare 2x)
# if defined(__USLC__)
#     define __GECO_HAS_WCHAR_T 
#     define __GECO_CLASS_PARTIAL_SPECIALIZATION
#     define __GECO_PARTIAL_SPECIALIZATION_SYNTAX
#     define __GECO_FUNCTION_TMPL_PARTIAL_ORDER
#     define __GECO_MEMBER_TEMPLATES
#     define __GECO_MEMBER_TEMPLATE_CLASSES
#     define __GECO_USE_EXCEPTIONS
#     define __GECO_HAS_NAMESPACES
#     define __GECO_USE_NAMESPACES
#     define __GECO_LONG_LONG
#     if defined(_REENTRANT)
#           define _UITHREADS     /* if      UnixWare < 7.0.1 */
#           define __GECO_UITHREADS
//!   use the following defines instead of the UI threads defines when
//!   you want to use POSIX threads
//!#         define _PTHREADS      /* only if UnixWare >=7.0.1 */
//!#         define __GECO_PTHREADS
#     endif
# endif

//! GCC
# ifdef __GNUC__
#   define __GECO_MEMBER_TEMPLATES
#   define __GECO_MEMBER_TEMPLATE_CLASSES
#   define __GECO_TEMPLATE_FRIENDS
#   define __GECO_CLASS_PARTIAL_SPECIALIZATION
#   define __GECO_USE_EXCEPTIONS
#   define __GECO_HAS_NAMESPACES
# endif

# if defined(__ICL) //! Intel compiler, which uses the EDG front end.
#   define __GECO_LONG_LONG 
#   define __GECO_MEMBER_TEMPLATES
#   define __GECO_MEMBER_TEMPLATE_CLASSES
#   define __GECO_TEMPLATE_FRIENDS
#   define __GECO_FUNCTION_TMPL_PARTIAL_ORDER
#   define __GECO_CLASS_PARTIAL_SPECIALIZATION
#   define __GECO_NO_DRAND48
#   define __GECO_HAS_NAMESPACES
#   define __GECO_USE_EXCEPTIONS
#   define __GECO_MEMBER_TEMPLATE_KEYWORD
#   ifdef _CPPUNWIND
#     define __GECO_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define __GECO_WIN32THREADS
#   endif
# endif

//! Mingw32, egcs compiler using the Microsoft C runtime
# if defined(__MINGW32__)
#   define __GECO_NO_DRAND48
#   ifdef _MT
#     define __GECO_WIN32THREADS
#   endif
# endif

//! Cygwin32, egcs compiler on MS Windows
# if defined(__CYGWIN__)
#   define __GECO_NO_DRAND48
# endif

//! Microsoft compiler. 
# if defined(_MSC_VER) && !defined(__ICL) && !defined(__MWERKS__)

//! Because of a Microsoft front end bug, we must not provide a
//! namespace qualifier when declaring a friend function.
#   define __GECO_QUALIFIER

#   define __GECO_NO_DRAND48
#   define __GECO_STATIC_CONST_INIT_BUG
#   define __GECO_NEED_TYPENAME
#   define __GECO_NO_USING_CLAUSE_IN_CLASS
#   define __GECO_NO_FRIEND_TEMPLATE_CLASS 
#   define __GECO_NON_TYPE_TMPL_PARAM_BUG
#   define __SGI_GECO_NO_ARROW_OPERATOR
#   define __GECO_DEFAULT_CONSTRUCTOR_BUG

#   ifdef _CPPUNWIND
#		define __GECO_USE_EXCEPTIONS
#   endif

#   ifdef _MT
#		define __GECO_WIN32THREADS
#   endif

//! MS VC++ 10.0 _MSC_VER = 1600  
//! MS VC++ 9.0 _MSC_VER = 1500  
//! MS VC++ 8.0 _MSC_VER = 1400  
//! MS VC++ 7.1 _MSC_VER = 1310  
//! MS VC++ 7.0 _MSC_VER = 1300  
//! MS VC++ 6.0 _MSC_VER = 1200  
//! MS VC++ 5.0 _MSC_VER = 1100  
#   if _MSC_VER < 1100 
#     define __GECO_NEED_EXPLICIT
#     define __GECO_NO_BOOL
#     define __GECO_NO_BAD_ALLOC
#   endif

#   if _MSC_VER > 1000
//! c standard library header 
//!@see http://!blog.csdn.net/acmicpc123/article/details/50205729 for details
#     include <yvals.h>
#     define __GECO_DONT_USE_BOOL_TYPEDEF
#   endif

#   if _MSC_VER >= 1200
#     define __GECO_PARTIAL_SPECIALIZATION_SYNTAX
#     define __GECO_HAS_NAMESPACES
#     define __GECO_CAN_THROW_RANGE_ERRORS
#     define NOMINMAX
#     undef min
#     undef max
//! disable warning 'initializers put in unrecognized initialization area'
#     pragma warning ( disable : 4075 )
//! disable warning 'empty controlled statement found'
#     pragma warning ( disable : 4390 )
//! disable warning 'debug symbol greater than 255 chars'
#     pragma warning ( disable : 4786 )
#   endif

#   if _MSC_VER < 1100
#     define __GECO_NO_EXCEPTION_HEADER
#     define __GECO_NO_BAD_ALLOC
#   endif

# endif //! Microsoft compiler. 

# if defined(__BORLANDC__)
#     define __GECO_NO_BAD_ALLOC
#     define __GECO_NO_DRAND48
#     define __GECO_DEFAULT_CONSTRUCTOR_BUG
#   if __BORLANDC__ >= 0x540 /* C++ Builder 4.0 */
#     define __GECO_CLASS_PARTIAL_SPECIALIZATION
#     define __GECO_FUNCTION_TMPL_PARTIAL_ORDER
#     define __GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#     define __GECO_MEMBER_TEMPLATES
#     define __GECO_TEMPLATE_FRIENDS
#   else
#     define __GECO_NEED_TYPENAME
#     define __GECO_LIMITED_DEFAULT_TEMPLATES
#     define __SGI_GECO_NO_ARROW_OPERATOR
#     define __GECO_NON_TYPE_TMPL_PARAM_BUG
#   endif
#   ifdef _CPPUNWIND
#     define __GECO_USE_EXCEPTIONS
#   endif
#   ifdef __MT__
#     define __GECO_WIN32THREADS
#   endif
# endif

# if defined(__GECO_NO_BOOL) && !defined(__GECO_DONT_USE_BOOL_TYPEDEF)
typedef int bool;
#   define true 1
#   define false 0
# endif

# ifdef __GECO_NEED_TYPENAME
#   define typename
# endif

//!for example:
//!template <class _Result,
//!class _Arg1 __GECO_DEPENDENT_DEFAULT_TMPL(_Result),
//!class _Arg2 __GECO_DEPENDENT_DEFAULT_TMPL(_Arg1) >
# ifdef __GECO_LIMITED_DEFAULT_TEMPLATES
#   define __GECO_DEPENDENT_DEFAULT_TMPL(_Tp)
# else
#   define __GECO_DEPENDENT_DEFAULT_TMPL(_Tp) = _Tp
# endif

# ifdef __GECO_MEMBER_TEMPLATE_KEYWORD
#   define __GECO_TEMPLATE template
# else
#   define __GECO_TEMPLATE
# endif

# ifdef __GECO_NEED_EXPLICIT
#   define explicit
# endif

# ifdef __GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __GECO_NULL_TMPL_ARGS <>
# else
#   define __GECO_NULL_TMPL_ARGS
# endif

# if defined(__GECO_CLASS_PARTIAL_SPECIALIZATION) \
|| defined (__GECO_PARTIAL_SPECIALIZATION_SYNTAX)
#   define __GECO_TEMPLATE_NULL template<>
# else
#   define __GECO_TEMPLATE_NULL
# endif

//! Use standard-conforming allocators if we have the necessary language
//! features.  __GECO_USE_SGI_ALLOCATORS is a hook so that users can 
//! disable new-style allocators, and continue to use the same kind of
//! allocators as before, without having to edit library headers.
# if defined(__GECO_CLASS_PARTIAL_SPECIALIZATION) && \
     defined(__GECO_MEMBER_TEMPLATES) && \
     defined(__GECO_MEMBER_TEMPLATE_CLASSES) && \
    !defined(__GECO_NO_BOOL) && \
    !defined(__GECO_NON_TYPE_TMPL_PARAM_BUG) && \
    !defined(__GECO_LIMITED_DEFAULT_TEMPLATES) && \
    !defined(__GECO_USE_SGI_ALLOCATORS) 
#   define __GECO_USE_GECO_ALLOCATORS
# endif

# ifndef __GECO_DEFAULT_ALLOCATOR
#   ifdef __GECO_USE_GECO_ALLOCATORS
#     define __GECO_DEFAULT_ALLOCATOR(T) allocator< T >
#   else
#     define __GECO_DEFAULT_ALLOCATOR(T) alloc
#   endif
# endif

//! __GECO_NO_NAMESPACES is a hook so that users can disable namespaces
//! without having to edit library headers. 
//! __GECO_NO_RELOPS_NAMESPACE is a hook so that users can disable the
//! geco::rel_ops namespace, keeping the relational operator template in namespace geco, 
//! without having to edit library headers.
# if defined(__GECO_HAS_NAMESPACES) && !defined(__GECO_NO_NAMESPACES)
#   define __GECO_USE_NAMESPACES
#   define __GECO geco
#   define __GECO_BEGIN_NAMESPACE namespace geco {
#   define __GECO_END_NAMESPACE }
#   if defined(__GECO_FUNCTION_TMPL_PARTIAL_ORDER) && \
       !defined(__GECO_NO_RELOPS_NAMESPACE)
#     define __GECO_USE_NAMESPACE_FOR_RELOPS
#     define __GECO_BEGIN_RELOPS_NAMESPACE namespace geco { namespace rel_ops {
#     define __GECO_END_RELOPS_NAMESPACE } }
#     define __GECO_RELOPS geco::rel_ops
#   else /* Use geco::rel_ops namespace */
#     define __GECO_USE_NAMESPACE_FOR_RELOPS
#     define __GECO_BEGIN_RELOPS_NAMESPACE namespace geco {
#     define __GECO_END_RELOPS_NAMESPACE }
#     define __GECO_RELOPS geco
#   endif /* Use geco::rel_ops namespace */
# else
#   define __GECO 
#   define __GECO_BEGIN_NAMESPACE 
#   define __GECO_END_NAMESPACE 
#   undef  __GECO_USE_NAMESPACE_FOR_RELOPS
#   define __GECO_BEGIN_RELOPS_NAMESPACE 
#   define __GECO_END_RELOPS_NAMESPACE 
#   define __GECO_RELOPS 
#   undef  __GECO_USE_NAMESPACES
# endif

//! Some versions of the EDG front end sometimes require an explicit
//! namespace spec where they shouldn't.  This macro facilitates that.
//! If the bug becomes irrelevant, then all uses of __GECO_QUALIFIER
//! should be removed.  The 7.3 beta SGI compiler has this bug, but the
//! MR version is not expected to have it.
# if defined(__GECO_USE_NAMESPACES) && !defined(__GECO_QUALIFIER)
#   define __GECO_QUALIFIER geco::
# else
#   define __GECO_QUALIFIER
# endif

# ifdef __GECO_USE_EXCEPTIONS
#   define __GECO_TRY try
#   define __GECO_CATCH_ALL catch(...)
#   define __GECO_THROW(x) throw x
#   define __GECO_RETHROW throw
#   define __GECO_NOTHROW throw()
#   define __GECO_UNWIND(action) catch(...) { action; throw; }
# else
#   define __GECO_TRY 
#   define __GECO_CATCH_ALL if (false)
#   define __GECO_THROW(x) 
#   define __GECO_RETHROW 
#   define __GECO_NOTHROW 
#   define __GECO_UNWIND(action) 
# endif

#ifdef __GECO_ASSERTIONS
# include <stdio.h>
# define __GECO_assert(expr) \
if (!(expr)){ fprintf(stderr, "%s:%d GECO assertion failure: %s\n",__FILE__,__LINE__,# expr);abort(); }
#else
# define __GECO_assert(expr)
#endif

# endif /* __GECO_CONFIG_H */
