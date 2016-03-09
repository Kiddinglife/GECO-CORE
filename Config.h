/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * Copyright (c) 1997
 * Silicon Graphics
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * Copyright (c) 2015
 * Geco Gaming
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

# ifndef __STL_CONFIG_H
# define __STL_CONFIG_H

// Flags:

// __STL_NO_BOOL
// defined if the compiler doesn't have bool as a builtin type.

// __STL_HAS_WCHAR_T
// defined if the compier has wchar_t as a builtin type.


// __STL_NO_DRAND48
// defined if the compiler doesn't have the drand48 function.
// @See http://blog.csdn.net/jimmyblind/article/details/5550042 
// for details about drand48() function

// __STL_STATIC_TEMPLATE_MEMBER_BUG
// defined if the compiler can't handle static members of template classes.

// __STL_STATIC_CONST_INIT_BUG: 
// defined if the compiler can't handle a constant-initializer in the declaration 
// of a static const data member


// __STL_CLASS_PARTIAL_SPECIALIZATION 
// defined if the compiler supports partial specialization of template classes.

// __STL_PARTIAL_SPECIALIZATION_SYNTAX
// defined if the compiler supports partial specialization syntax for full 
// specialization of class templates. 
// (Even if it doesn't actually support partial specialization itself.)

//  __STL_FUNCTION_TMPL_PARTIAL_ORDER 
// defined if the compiler supports partial ordering of function templates.
// (a.k.a partial specialization of function templates.)

// __STL_MEMBER_TEMPLATES
// defined if the compiler supports template member functions of classes.

// __STL_MEMBER_TEMPLATE_CLASSES
// defined if the compiler supports nested classes that are member
// templates of other classes.

// __STL_TEMPLATE_FRIENDS
// defined if the compiler supports templatized friend declarations.

// __STL_EXPLICIT_FUNCTION_TMPL_ARGS 
// defined if the compiler supports calling a function template by providing its 
// template arguments explicitly.


// __STL_LIMITED_DEFAULT_TEMPLATES
// defined if the compiler is unable to handle default template parameters
// that depend on previous template parameters.

// __STL_NON_TYPE_TMPL_PARAM_BUG: defined if the compiler has trouble with
//   function template argument deduction for non-type template parameters.

// __STL_NON_TYPE_TMPL_PARAM_BUG
// defined if the compiler has trouble with
//  function template argument deduction for non-type template parameters.

// __SGI_STL_NO_ARROW_OPERATOR
// defined if the compiler is unable to support the -> operator for iterators.

// __STL_DEFAULT_CONSTRUCTOR_BUG
// defined if T() does not work properly when T is a builtin type.

//  __STL_USE_EXCEPTIONS
// defined if the compiler (in the current compilation mode) supports exceptions.

// __STL_USE_NAMESPACES
// defined if the compiler has the necessary support for namespaces.

// __STL_NO_EXCEPTION_HEADER
//  defined if the compiler does not have 
// a standard-conforming header <exception>

//  __STL_NO_BAD_ALLOC 
// defined if the compiler does not have a <new> header, 
// or if <new> does not contain a bad_alloc class. 
// If a bad_alloc class exists, it is assumed to be in namespace std.

// __STL_SGI_THREADS
// defined if this is being compiled for an SGI IRIX
// system in multithreaded mode, using native SGI threads instead of  pthreads.
// this is used only for SGI company's specific system


// __STL_WIN32THREADS
// defined if this is being compiled on a WIN32 compiler in multithreaded mode.

// __STL_PTHREADS
// defined if we should use portable pthreads synchronization.

//  __STL_UITHREADS 
// defined if we should use UI / solaris / UnixWare threads
// synchronization.  UIthreads are similar to pthreads, but are based 
// on an earlier version of the Posix threads standard.

// __STL_LONG_LONG 
// if the compiler has long long and unsigned long long
// types.  (They're not in the C++ standard, but they are expected to be 
// included in the forthcoming C9X standard.)

// __STL_THREADS is defined if thread safety is needed.

// __STL_VOLATILE is defined to be "volatile" if threads are being
// used, and the empty string otherwise.

// __STL_NO_USING_CLAUSE_IN_CLASS 
// The compiler does not handle "using" clauses inside of class definitions.

//  __STL_NO_FRIEND_TEMPLATE_CLASS 
// The compiler does not handle friend declaractions 
// where the friend is a template class.

// __STL_NO_FUNCTION_PTR_IN_CLASS_TEMPLATE
// The compiler does not support the use of a function pointer type 
// as the argument for a template.

// __STL_MEMBER_TEMPLATE_KEYWORD 
// standard C++ requires the template keyword in a few new places (14.2.4).
// This flag is set for compilers that support (and require) this usage.

// __STL_USE_SGI_ALLOCATORS 
// User-settable macros that control compilation. if defined, then the STL 
// will use older SGI-style allocators, instead of standard-conforming allocators,
// even if the compiler supports all of the language features needed
// for standard-conforming allocators.

// __STL_NO_NAMESPACES
// if defined, don't put the library in namespace
// std, even if the compiler supports namespaces.

// __STL_NO_RELOPS_NAMESPACE 
// if defined, don't put the relational operator templates (>, <=. >=, !=) 
// in namespace std::rel_ops, even if the compiler supports namespaces 
// and partial ordering of function templates.

// __STL_ASSERTIONS
// if defined, then enable runtime checking through the __stl_assert macro.



// _PTHREADS
// if defined, use Posix threads for multithreading support.

// _UITHREADS
// if defined, use SCO/Solaris/UI threads for multithreading support

//  _NOTHREADS 
// if defined, don't use any multithreading support. 

# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __STL_PTHREADS
# endif

# if defined(_UITHREADS) && !defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __STL_UITHREADS
# endif



//   __STL_USE_CONCEPT_CHECKS enables some extra compile-time error
//   checking to make sure that user-defined template arguments satisfy
//   all of the appropriate requirements.  This may result in more
//   comprehensible error messages.  It incurs no runtime overhead.  This 
//   feature requires member templates and partial specialization.

// _STL_NO_CONCEPT_CHECKS
// if defined, disables the error checking that
// we get from __STL_USE_CONCEPT_CHECKS.

// __STL_USE_NEW_IOSTREAMS
// if defined, then the STL will use new, standard-conforming iostreams
// (e.g. the <iosfwd> header).  If not defined, the STL will use old cfront-style 
// iostreams (e.g. the <iostream.h> header).

// Other macros defined by this file:

// bool, true, and false, if __STL_NO_BOOL is defined.

// typename, as a null macro if it's not already a keyword.

// explicit, as a null macro if it's not already a keyword.

// namespace-related macros (__STD, __STL_BEGIN_NAMESPACE, etc.)

// exception-related macros (__STL_TRY, __STL_UNWIND, etc.)

// __stl_assert
// either as a test or as a null macro, depending on
// whether or not __STL_ASSERTIONS is defined.

# endif
