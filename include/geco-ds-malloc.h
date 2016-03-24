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
 *
 * Copyright (c) 1996-1998
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/*
 * geco-malloc.h
 *
 *  Created on: 22 Mar 2016
 *      Author: jakie zhang
 */

#ifndef __INCLUDE_GECO_DS_MALLOC_H
#define __INCLUDE_GECO_DS_MALLOC_H

#include "geco-ds-config.h"
GECO_BEGIN_NAMESPACE

#ifdef __SUNPRO_CC
#   define __PRIVATE public
// Extra access restrictions prevent us from really making some things
// private.
#else
#   define __PRIVATE private
#endif

#ifdef GECO_STATIC_TEMPLATE_MEMBER_BUG
#  define __USE_MALLOC
#endif

// This implements some standard node allocators.  These are
// NOT the same as the allocators in the C++ draft standard or in
// in the original STL.  They do not encapsulate different pointer
// types; indeed we assume that there is only one pointer type.
// The allocation primitives are intended to allocate individual objects,
// not larger arenas as with the original STL allocators.
#ifndef THROW_BAD_ALLOC
#  if defined(GECO_NO_BAD_ALLOC) || !defined(GECO_USE_EXCEPTIONS)
#    include <stdio.h>
#    include <stdlib.h>
#    define THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1)
#  else /* Standard conforming out-of-memory handling */
#    include <new>
#    define THROW_BAD_ALLOC throw std::bad_alloc()
#  endif
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifndef __RESTRICT
#  define __RESTRICT
#endif

#ifdef GECO_USE_STL_THREADS
#include "geco-stl-thread.h"
#define GECO_ALLOC_IF_USES_THREAD true
# ifdef GECO_SGI_THREADS
// We test whether threads are in use before locking.
// Perhaps this should be moved into stl_threads.h, but that
// probably makes it harder to avoid the procedure call when
// it isn't needed.
extern "C"
{
    extern int __us_rsthread_malloc;
}
// The above is copied from malloc.h.  Including <malloc.h>
// would be cleaner but fails with certain levels of standard
// conformance.
# define GECO_ALLOC_LOCK \
if (threads && __us_rsthread_malloc) \
{ _S_node_allocator_lock._M_acquire_lock(); }
# define GECO_ALLOC_UNLOCK
if (threads && __us_rsthread_malloc)
{   _S_node_allocator_lock._M_release_lock();}
# else /* !GECO_SGI_THREADS */
# define GECO_ALLOC_LOCK \
{ if (threads) _S_node_allocator_lock._M_acquire_lock(); }
# define GECO_ALLOC_UNLOCK \
{ if (threads) _S_node_allocator_lock._M_release_lock(); }
# endif
#else
//  Thread-unsafe
# define GECO_ALLOC_LOCK
# define GECO_ALLOC_UNLOCK
# define GECO_ALLOC_IF_USES_THREAD false
#endif

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// Malloc-based allocator.  Typically slower than default alloc below.
// Typically thread-safe and more storage efficient.
#ifdef GECO_STATIC_TEMPLATE_MEMBER_BUG
# ifdef __DECLARE_GLOBALS_HERE
void (* __malloc_alloc_oom_handler)() = 0;
// g++ 2.7.2 does not handle static template data members.
# else
extern void (* __malloc_alloc_oom_handler)();
# endif
#endif

GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_MALLOC_H_ */
