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

# ifndef GECO_CONFIG_H
# define GECO_CONFIG_H

//! Flags.

//! @def GECO_NO_BOOL
//! @brief defined if the compiler doesn't have bool as a builtin type.

//! @def GECO_HAS_WCHAR_T
//! @brief defined if the compier has wchar_t as a builtin type.

//! GECO_NO_DRAND48
//! @brief defined if the compiler doesn't have the drand48 function.
//! @See http://!blog.csdn.net/jimmyblind/article/details/5550042 
//! for details about drand48() function

//! @def GECO_STATIC_TEMPLATE_MEMBER_BUG
//! @brief defined if the compiler can't handle static members of template classes.

//! @def GECO_STATIC_CONST_INIT_BUG:
//! @brief defined if the compiler can't handle a constant-initializer in the declaration 
//! of a static const data member

//! @def GECO_CLASS_PARTIAL_SPECIALIZATION
//! @brief defined if the compiler supports partial specialization of template classes.
//! @code
//!  generic template.
//!  template<class I, class O>
//!  struct testClass{...};
//!  particial-specification 1
//!  template <class Type>
//!  struct testClass <Type*, const Type&>{...};
//!  particial-specification 2
//!  template <class Type>
//!  struct testClass <const Type*, Type*>{...};
//! @endcode

//! @def GECO_PARTIAL_SPECIALIZATION_SYNTAX
//! @brief defined if the compiler supports partial specialization syntax for full 
//! specialization of class templates. 
//! (Even if it doesn't actually support partial specialization itself.)

//! @def GECO_FUNCTION_TMPL_PARTIAL_ORDER
//! \brief defined if the compiler supports partial ordering of function templates.
//! (a.k.a partial specialization of function templates.)
//! @code
//! template <class Type>
//! struct testClass { void swap(vector<Type>){...} };
//! #ifdef GECO_FUNCTION_TMPL_PARTIAL_ORDER
//! template <class Type>
//! inline void swap (vector<Type>& x, vecotr<Type>& y) { x.swap(y); }
//! #endif
//! @endcode

//! @def GECO_MEMBER_TEMPLATES
//! @brief defined if the compiler supports template member functions of classes.

//! @def GECO_MEMBER_TEMPLATE_CLASSES
//! @brief defined if the compiler supports nested classes that are member
//! templates of other classes.

//! @def  GECO_TEMPLATE_FRIENDS
//! @brief  defined if the compiler supports templatized friend declarations.

//! @def GECO_EXPLICIT_FUNCTION_TMPL_ARGS
//! @brief defined if the compiler supports calling a function template by providing its 
//! template arguments explicitly.
//! @code
//! template <class Type, class Sequence>
//! bool operator==(const stack<Type, Sequence>& x);
//!
//! template < class Type, class Sequence = deque<Type>>
//! class stack {
//! //!this is correct
//! friend bool operator== <Type> (const stack<Type>&, const stack<Type>&);
//! //!this is alos correct
//! friend bool opeartor==<Type> (const statck<Type>&, const stack<Type>&);
//! //!this is alos correct
//! friend bool opeartor==<> (const statck&, const stack&);
//! }
//! @endcode

//! @def  GECO_LIMITED_DEFAULT_TEMPLATES
//! @brief defined if the compiler is unable to handle default template parameters
//! that depend on previous template parameters.
//! @code
//! template<class Type, class Sequence = deque<Type>>
//!@endcode

//! @def  GECO_NON_TYPE_TMPL_PARAM_BUG
//! @brief defined if the compiler has trouble with
//! function template argument deduction for non-type template parameters.
//! \code
//! template <class Type, size_t BufSize = 0>
//! struct deque_iterator { typedef deque_iterator<Type, BufSize> iterator;};
//! \endcode

//! @def  SGI_GECO_NO_ARROW_OPERATOR
//! @brief defined if the compiler is unable to support the -> operator for iterators.

//! @def  GECO_DEFAULT_CONSTRUCTOR_BUG
//! @brief defined if Type() does not work properly when Type is a builtin type.

//! @def  GECO_USE_EXCEPTIONS
//! @brief defined if the compiler (in the current compilation mode) supports exceptions.

//! @def  GECO_USE_NAMESPACES
//! @brief defined if the compiler has the necessary support for namespaces.

//! @def  sGECO_NO_EXCEPTION_HEADER
//! @brief defined if the compiler does not have 
//! a standard-conforming header <exception>.

//! @def  GECO_NO_BAD_ALLOC
//! @brief defined if the compiler does not have a <new> header, 
//! or if <new> does not contain a bad_alloc class. 
//! If a bad_alloc class exists, it is assumed to be in namespace geco.

//! @def  GECO_LONG_LONG
//! @brief if the compiler has long long and unsigned long long
//! types (They're not in the C++ standard, but they are expected to be 
//! included in the forthcoming C9X standard).

//! @def GECO_THREADS
//! @brief defined if thread safety is needed.

//! @def  GECO_VOLATILE
//! @brief defined to be "volatile" if threads are being used, and the empty string otherwise.

//! @def  GECO_NO_USING_CLAUSE_IN_CLASS
//! @brief The compiler does not handle "using" clauses inside of class definitions.

//!  @def  GECO_NO_FRIEND_TEMPLATE_CLASS
//! @brief The compiler does not handle friend declaractions 
//! where the friend is a template class.

//! @def  GECO_NO_FUNCTION_PTR_IN_CLASS_TEMPLATE
//! @brief The compiler does not support the use of a function pointer type 
//! as the argument for a template.

//! @def GECO_MEMBER_TEMPLATE_KEYWORD
//! @brief standard C++ requires the template keyword in a few new places (14.2.4),
//! this flag is set for compilers that support (and require) this usage.

//! @def  GECO_USE_SGI_ALLOCATORS
//! @brief User-settable macros that control compilation. 
//! if defined, then the GECO will use older SGI-style allocators,
//! instead of standard-conforming allocators,
//! even if the compiler supports all of the language features needed
//! for standard-conforming allocators.

//! @def GECO_NO_NAMESPACES
//! @brief if defined, don't put the library in namespace
//! geco, even if the compiler supports namespaces.

//! @def  GECO_NO_RELOPS_NAMESPACE
//! @brief if defined, don't put the relational operator templates (>, <=. >=, !=) 
//! in namespace geco::rel_ops, even if the compiler supports namespaces 
//! and partial ordering of function templates.

//! @def  GECO_ASSERTIONS
//! @brief if defined, then enable runtime checking through the GECO_assert macro.

//! @def  GECO_SGI_THREADS
//! @brief defined if this is being compiled for an SGI IRIX
//! system in multithreaded mode, using native SGI threads instead of  pthreads,
//! this is used only for SGI  specific system.
//! @todo maybe not need,can be deleted.

//! @def  GECO_WIN32THREADS
//! @brief defined if this is being compiled on a WIN32 compiler in multithreaded mode.

//! @def GECO_PTHREADS
//! @brief defined if we should use portable pthreads synchronization.

//! @def GECO_UITHREADS
//! @brief defined if we should use UI / solaris / UnixWare threads synchronization.  
//! UIthreads are similar to pthreads, but are based 
//! on an earlier version of the Posix threads standard.

//! @def  _PTHREADS
//! @brief if defined, use Posix threads for multithreading support.

//! @def  _UITHREADS
//! @brief if defined, use SCO/Solaris/UI threads for multithreading support

//!  @def  _NOTHREADS 
//! @brief if defined, don't use GECO_GECO multithreading support. 

//!  @def  GECO_USE_CONCEPT_CHECKS
//!  enables some extra compile-time error
//!  checking to make sure that user-defined template arguments satisfy
//!  all of the appropriate requirements.  This may result in more
//!  comprehensible error messages.  It incurs no runtime overhead.  This 
//!  feature requires member templates and partial specialization.

//! @def _GECO_NO_CONCEPT_CHECKS
//! @brief if defined, disables the error checking that
//! we get from GECO_USE_CONCEPT_CHECKS.

//! @def  GECO_USE_NEW_IOSTREAMS
//! if defined, then the GECO will use new, standard-conforming iostreams
//! (e.g. the <iosfwd> header).  If not defined, the GECO will use old cfront-style 
//! iostreams (e.g. the <iostream.h> header).

//! @def GECO_NO_BOOL
//! @brief bool, true, and false, if defined.

//! typename, as a null macro if it's not already a keyword.
//! explicit, as a null macro if it's not already a keyword.

//! @def GECO
//! @brief namespace-related macros

//! @def GECO_BEGIN_NAMESPACE
//! @brief namespace-related macros

//! @def GECO_TRY
//! @brief exception-related macros

//! @def GECO_UNWIND
//! @brief exception-related macros

//! @def GECO_assert
//! @brief either as a test or as a null macro, depending on
//! whether or not GECO_ASSERTIONS is defined.

# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define GECO_PTHREADS
# endif

# if defined(_UITHREADS) && !defined(_PTHREADS) && !defined(_NOTHREADS)
#     define GECO_UITHREADS
# endif

//! SGI complier
# if defined(sgi) && !defined(GNUC)
#   include <standards.h>
#   if !defined(_BOOL)
#     define GECO_NO_BOOL
#   endif
#   if defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32
#     define GECO_STATIC_CONST_INIT_BUG
#   endif
#   if defined(_WCHAR_T_IS_KEYWORD)
#     define GECO_HAS_WCHAR_T
#   endif
#   if !defined(_TYPENAME_IS_KEYWORD)
#     define GECO_NEED_TYPENAME
#   endif
#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#     define GECO_CLASS_PARTIAL_SPECIALIZATION
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#     define GECO_FUNCTION_TMPL_PARTIAL_ORDER
#   endif
#   ifdef _MEMBER_TEMPLATES
#     define GECO_MEMBER_TEMPLATES
#     define GECO_TEMPLATE_FRIENDS
#     define GECO_MEMBER_TEMPLATE_CLASSES
#   endif
#   if defined(_MEMBER_TEMPLATE_KEYWORD)
#     define GECO_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if defined(_STANDARD_C_PLUS_PLUS)
#     define GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#     define GECO_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if COMPILER_VERSION < 720 || (defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32)
#     define GECO_DEFAULT_CONSTRUCTOR_BUG
#   endif
#   if !defined(_EXPLICIT_IS_KEYWORD)
#     define GECO_NEED_EXPLICIT
#   endif
#   ifdef EXCEPTIONS
#     define GECO_USE_EXCEPTIONS
#   endif
#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
#     define GECO_HAS_NAMESPACES
#   endif 
#   if (_COMPILER_VERSION < 721) || \
    !defined(GECO_HAS_NAMESPACES) || defined(GECO_NO_NAMESPACES)
#     define GECO_NO_EXCEPTION_HEADER
#   endif
#   if _COMPILER_VERSION < 730 || !defined(_STANDARD_C_PLUS_PLUS) || \
      !defined(_NAMESPACES)
#     define GECO_NO_BAD_ALLOC
#   endif
#   if !defined(_NOTHREADS) && !defined(GECO_PTHREADS)
#     define GECO_SGI_THREADS
#   endif
#   if defined(_LONGLONG) && defined(_SGIAPI) && _SGIAPI
#     define GECO_LONG_LONG
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define GECO_USE_NEW_IOSTREAMS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define GECO_CAN_THROW_RANGE_ERRORS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define SGI_GECO_USE_AUTO_PTR_CONVERSIONS
#   endif
# endif //! sgi complier

/*
 * Jochen Schlick '1999  - added new #defines (GECO)_UITHREADS (for
 *                         providing SCO / Solaris / UI thread support)
 *                       - added the necessary defines for the SCO UDK 7
 *                         compiler (and its template friend behavior)
 *                       - all UDK7 specific GECO changes are based on the
 *                         macro USLC being defined
 *
 SCO Unix是在国内比较有名气的操作系统，因为他是当时能运行在Intel的平台之一，
 并且较早进入中国市场. 它的历史可以追溯到MicroSoft开发的Xienx，
 Xienx是运行在Intel平台上的一种基于Unix V 6的系统，
 后来Xienx开发部门独立出来成立了SCO公司，
 并基于AT&Type System VR3.2开发了SCO Unix，
 其最新的版本为增强了图形接口的SCO OpenServer 5.0.4。
 此时AT&Type已经将它们负责Unix的部门USL(Unix系统实验室)，
 卖给了Novell公司，它们的Unix被更名为UnixWare ，
 但是Novell正逢经营问题，不得不将UnixWare再次卖给SCO。
 SCO之所以能占有市场，并不是其产品特别出色，
 而是因为在小型机特别昂贵的年代，对一些追求稳定的行业来说，
 使用SCO能在x86上运行，可以节约大量成本。
 因此早期的银行、金融行业的终端大多是使用SCO的。
 而最近SCO的名声越来越坏，只因被更加优秀且同样能运行于x86的Linux抢走大量份额，
 大家知道知道吃不饱的狗是会乱咬人的。不过可惜最后授权没强行推销出去几份，
 反而得了个$CO之名。
 而Novell在购买UnixWare之后的一个重要举动是将Unix商标赠送给一个非盈利的Unix组织X/Open，
 结束了USL与BSD以及其他厂商的纷争。
 */
//! SCO UDK 7 compiler (UnixWare 7x, OSR 5, UnixWare 2x)
# if defined(USLC)
#     define GECO_HAS_WCHAR_T
#     define GECO_CLASS_PARTIAL_SPECIALIZATION
#     define GECO_PARTIAL_SPECIALIZATION_SYNTAX
#     define GECO_FUNCTION_TMPL_PARTIAL_ORDER
#     define GECO_MEMBER_TEMPLATES
#     define GECO_MEMBER_TEMPLATE_CLASSES
#     define GECO_USE_EXCEPTIONS
#     define GECO_HAS_NAMESPACES
#     define GECO_USE_NAMESPACES
#     define GECO_LONG_LONG
#     if defined(_REENTRANT)
#           define _UITHREADS     /* if      UnixWare < 7.0.1 */
#           define GECO_UITHREADS
//!   use the following defines instead of the UI threads defines when
//!   you want to use POSIX threads
//!#         define _PTHREADS      /* only if UnixWare >=7.0.1 */
//!#         define GECO_PTHREADS
#     endif
# endif

//! GCC
# ifdef __GNUC__
#   if __GNUC__ == 2 && __GNUC_MINOR__ <= 7
#     define GECO_STATIC_TEMPLATE_MEMBER_BUG
#   endif
#   if __GNUC__ < 2 
#     define GECO_NEED_TYPENAME
#     define GECO_NEED_EXPLICIT
#   endif
#   if __GNUC__ == 2 && __GNUC_MINOR__ <= 8
#     define GECO_NO_EXCEPTION_HEADER
#     define GECO_NO_BAD_ALLOC
#   endif
#   if __GNUC__ == 2 && __GNUC_MINOR__ >= 8
#     define GECO_CLASS_PARTIAL_SPECIALIZATION
#     define GECO_FUNCTION_TMPL_PARTIAL_ORDER
#     define GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#     define GECO_MEMBER_TEMPLATES
#     define GECO_CAN_THROW_RANGE_ERRORS
//    g++ 2.8.1 supports member template functions, but not member
//    template nested classes.
#     if __GNUC_MINOR__ >= 9
#       define GECO_MEMBER_TEMPLATE_CLASSES
#       define GECO_TEMPLATE_FRIENDS
#       define __SGI_STL_USE_AUTO_PTR_CONVERSIONS
#       define GECO_HAS_NAMESPACES
//#       define GECO_USE_NEW_IOSTREAMS
#     endif
#   endif
#   define GECO_DEFAULT_CONSTRUCTOR_BUG
#   ifdef __EXCEPTIONS
#     define GECO_USE_EXCEPTIONS
#   endif
#   ifdef _REENTRANT
#     define GECO_PTHREADS
#   endif
#   if (__GNUC__ < 2) || (__GNUC__ == 2 && __GNUC_MINOR__ < 95)
#     define GECO_NO_FUNCTION_PTR_IN_CLASS_TEMPLATE
#   endif
# endif

# if defined(__SUNPRO_CC) 
#   define GECO_NO_BOOL
#   define GECO_NEED_TYPENAME
#   define GECO_NEED_EXPLICIT
#   define GECO_USE_EXCEPTIONS
#   ifdef _REENTRANT
#     define GECO_PTHREADS
#   endif
#   define __SGI_STL_NO_ARROW_OPERATOR
#   define GECO_PARTIAL_SPECIALIZATION_SYNTAX
#   define GECO_NO_EXCEPTION_HEADER
#   define GECO_NO_BAD_ALLOC
# endif

# if defined(__COMO__)
#   define GECO_MEMBER_TEMPLATES
#   define GECO_MEMBER_TEMPLATE_CLASSES
#   define GECO_TEMPLATE_FRIENDS
#   define GECO_CLASS_PARTIAL_SPECIALIZATION
#   define GECO_USE_EXCEPTIONS
#   define GECO_HAS_NAMESPACES
# endif

# if defined(ICL) //! Intel compiler, which uses the EDG front end.
#   define GECO_LONG_LONG
#   define GECO_MEMBER_TEMPLATES
#   define GECO_MEMBER_TEMPLATE_CLASSES
#   define GECO_TEMPLATE_FRIENDS
#   define GECO_FUNCTION_TMPL_PARTIAL_ORDER
#   define GECO_CLASS_PARTIAL_SPECIALIZATION
#   define GECO_NO_DRAND48
#   define GECO_HAS_NAMESPACES
#   define GECO_USE_EXCEPTIONS
#   define GECO_MEMBER_TEMPLATE_KEYWORD
#   ifdef _CPPUNWIND
#     define GECO_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define GECO_WIN32THREADS
#   endif
# endif

//! Mingw32, egcs compiler using the Microsoft C runtime
# if defined(MINGW32)
#   define GECO_NO_DRAND48
#   ifdef _MT
#     define GECO_WIN32THREADS
#   endif
# endif

//! Cygwin32, egcs compiler on MS Windows
# if defined(CYGWIN)
#   define GECO_NO_DRAND48
# endif

//! Microsoft compiler. 
# if defined(_MSC_VER) && !defined(ICL) && !defined(MWERKS)

#   define GECO_NO_DRAND48
#   define GECO_STATIC_CONST_INIT_BUG
#   define GECO_NEED_TYPENAME
#   define GECO_NO_USING_CLAUSE_IN_CLASS
#   define GECO_NO_FRIEND_TEMPLATE_CLASS
#   define GECO_NON_TYPE_TMPL_PARAM_BUG
#   define SGI_GECO_NO_ARROW_OPERATOR
#   define GECO_DEFAULT_CONSTRUCTOR_BUG

#   ifdef _CPPUNWIND
#		define GECO_USE_EXCEPTIONS
#   endif

#   ifdef _MT
#		define GECO_WIN32THREADS
#   endif

//! MS VC++ 10.0 _MSC_VER = 1600  
//! MS VC++ 9.0 _MSC_VER = 1500  
//! MS VC++ 8.0 _MSC_VER = 1400  
//! MS VC++ 7.1 _MSC_VER = 1310  
//! MS VC++ 7.0 _MSC_VER = 1300  
//! MS VC++ 6.0 _MSC_VER = 1200  
//! MS VC++ 5.0 _MSC_VER = 1100  
#   if _MSC_VER < 1100 
#     define GECO_NEED_EXPLICIT
#     define GECO_NO_BOOL
#     define GECO_NO_BAD_ALLOC
#   endif

#   if _MSC_VER > 1000
//! c standard library header 
//!@see http://!blog.csdn.net/acmicpc123/article/details/50205729 for details
#     include <yvals.h>
#     define GECO_DONT_USE_BOOL_TYPEDEF
#   endif

#   if _MSC_VER >= 1200
#     define GECO_PARTIAL_SPECIALIZATION_SYNTAX
#     define GECO_HAS_NAMESPACES
#     define GECO_CAN_THROW_RANGE_ERRORS
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
#     define GECO_NO_EXCEPTION_HEADER
#     define GECO_NO_BAD_ALLOC
#   endif

//! Because of a Microsoft front end bug, we must not provide a
//! namespace qualifier when declaring a friend function.
#   define GECO_QUALIFIER

# endif //! Microsoft compiler. 

# if defined(BORLANDC)
#     define GECO_NO_BAD_ALLOC
#     define GECO_NO_DRAND48
#     define GECO_DEFAULT_CONSTRUCTOR_BUG
#   if BORLANDC >= 0x540 /* C++ Builder 4.0 */
#     define GECO_CLASS_PARTIAL_SPECIALIZATION
#     define GECO_FUNCTION_TMPL_PARTIAL_ORDER
#     define GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#     define GECO_MEMBER_TEMPLATES
#     define GECO_TEMPLATE_FRIENDS
#   else
#     define GECO_NEED_TYPENAME
#     define GECO_LIMITED_DEFAULT_TEMPLATES
#     define SGI_GECO_NO_ARROW_OPERATOR
#     define GECO_NON_TYPE_TMPL_PARAM_BUG
#   endif
#   ifdef _CPPUNWIND
#     define GECO_USE_EXCEPTIONS
#   endif
#   ifdef MT
#     define GECO_WIN32THREADS
#   endif
# endif

# if defined(GECO_NO_BOOL) && !defined(GECO_DONT_USE_BOOL_TYPEDEF)
typedef int bool;
#   define true 1
#   define false 0
# endif

# ifdef GECO_NEED_TYPENAME
#   define typename
# endif

//!for example:
//!template <class _Result,
//!class _Arg1 GECO_DEPENDENT_DEFAULT_TMPL(_Result),
//!class _Arg2 GECO_DEPENDENT_DEFAULT_TMPL(_Arg1) >
# ifdef GECO_LIMITED_DEFAULT_TEMPLATES
#   define GECO_DEPENDENT_DEFAULT_TMPL(_Tp)
# else
#   define GECO_DEPENDENT_DEFAULT_TMPL(_Tp) = _Tp
# endif

# ifdef GECO_MEMBER_TEMPLATE_KEYWORD
#   define GECO_TEMPLATE template
# else
#   define GECO_TEMPLATE
# endif

# ifdef GECO_NEED_EXPLICIT
#   define explicit
# endif

# ifdef GECO_EXPLICIT_FUNCTION_TMPL_ARGS
#   define GECO_NULL_TMPL_ARGS <>
# else
#   define GECO_NULL_TMPL_ARGS
# endif

# if defined(GECO_CLASS_PARTIAL_SPECIALIZATION) \
|| defined (GECO_PARTIAL_SPECIALIZATION_SYNTAX)
#   define GECO_TEMPLATE_NULL template<>
# else
#   define GECO_TEMPLATE_NULL
# endif

//! Use standard-conforming allocators if we have the necessary language
//! features.  GECO_USE_SGI_ALLOCATORS is a hook so that users can
//! disable new-style allocators, and continue to use the same kind of
//! allocators as before, without having to edit library headers.
# if defined(GECO_CLASS_PARTIAL_SPECIALIZATION) && \
     defined(GECO_MEMBER_TEMPLATES) && \
     defined(GECO_MEMBER_TEMPLATE_CLASSES) && \
    !defined(GECO_NO_BOOL) && \
    !defined(GECO_NON_TYPE_TMPL_PARAM_BUG) && \
    !defined(GECO_LIMITED_DEFAULT_TEMPLATES) && \
    !defined(GECO_USE_SGI_ALLOCATORS)
#   define GECO_USE_GECO_ALLOCATORS
# endif

# ifndef GECO_DEFAULT_ALLOCATOR
#   ifdef GECO_USE_GECO_ALLOCATORS
#     define GECO_DEFAULT_ALLOCATOR(Type) allocator< Type >
#   else
#     define GECO_DEFAULT_ALLOCATOR(Type) alloc
#   endif
# endif

//! GECO_NO_NAMESPACES is a hook so that users can disable namespaces
//! without having to edit library headers. 
//! GECO_NO_RELOPS_NAMESPACE is a hook so that users can disable the
//! geco::rel_ops namespace, keeping the relational operator template in namespace geco, 
//! without having to edit library headers.
# if defined(GECO_HAS_NAMESPACES) && !defined(GECO_NO_NAMESPACES)
#   define GECO_USE_NAMESPACES
#   define GECO geco
#   define GECO_BEGIN_NAMESPACE namespace geco {
#   define GECO_END_NAMESPACE }
#   if defined(GECO_FUNCTION_TMPL_PARTIAL_ORDER) && \
       !defined(GECO_NO_RELOPS_NAMESPACE)
#     define GECO_USE_NAMESPACE_FOR_RELOPS
#     define GECO_BEGIN_RELOPS_NAMESPACE namespace geco { namespace rel_ops {
#     define GECO_END_RELOPS_NAMESPACE } }
#     define GECO_RELOPS geco::rel_ops
#   else /* Use geco::rel_ops namespace */
#     define GECO_USE_NAMESPACE_FOR_RELOPS
#     define GECO_BEGIN_RELOPS_NAMESPACE namespace geco {
#     define GECO_END_RELOPS_NAMESPACE }
#     define GECO_RELOPS geco
#   endif /* Use geco::rel_ops namespace */
# else
#   define GECO
#   define GECO_BEGIN_NAMESPACE
#   define GECO_END_NAMESPACE
#   undef  GECO_USE_NAMESPACE_FOR_RELOPS
#   define GECO_BEGIN_RELOPS_NAMESPACE
#   define GECO_END_RELOPS_NAMESPACE
#   define GECO_RELOPS
#   undef  GECO_USE_NAMESPACES
# endif

//! Some versions of the EDG front end sometimes require an explicit
//! namespace spec where they shouldn't.  This macro facilitates that.
//! If the bug becomes irrelevant, then all uses of GECO_QUALIFIER
//! should be removed.  The 7.3 beta SGI compiler has this bug, but the
//! MR version is not expected to have it.
# if defined(GECO_USE_NAMESPACES) && !defined(GECO_QUALIFIER)
#   define GECO_QUALIFIER geco::
# else
#   define GECO_QUALIFIER
# endif

# ifdef GECO_USE_EXCEPTIONS
#   define GECO_TRY try
#   define GECO_CATCH_ALL catch(...)
#   define GECO_THROW(x) throw x
#   define GECO_RETHROW throw
#   define GECO_NOTHROW throw()
#   define GECO_UNWIND(action) catch(...) { action; throw; }
# else
#   define GECO_TRY
#   define GECO_CATCH_ALL if (false)
#   define GECO_THROW(x)
#   define GECO_RETHROW
#   define GECO_NOTHROW
#   define GECO_UNWIND(action)
# endif

#ifdef GECO_ASSERTIONS
# include <stdio.h>
# define GECO_assert(expr) \
if (!(expr)){ fprintf(stderr, "%s:%d GECO assertion failure: %s\n",FILE,LINE,# expr);abort(); }
#else
# define GECO_assert(expr)
#endif

# endif /* GECO_CONFIG_H */
