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

/// GECO's allocator is defined in geco-core-ds-memory.h
/// 1.geco - ctor.h defines global functions construct() and destruct() that
/// are used for object construction and destruction.
/// both are geco - standard - conforming functions
/// 2.geco - alloc.h defines allocator named 'alloc'
# ifndef __GECO_INTERNAL_CONSTRUCT_H
# define __GECO_INTERNAL_CONSTRUCT_H

#include <new.h> // for use of placement new 
#include "geco-core-ds-config.h"

__GECO_BEGIN_NAMESPACE

// Only construct and destroy are standard-conforming
// other functions are not part of the C++ standard,
// and are provided for backward compatibility with the HP STL.  We also
// provide internal names _Construct and _Destroy that can be used within
// the library, so that standard-conforming pieces don't have to rely on
// non-standard extensions.

// Internal names
template <class T1, class T2>
inline void Construct
__GECO_END_NAMESPACE

# endif
