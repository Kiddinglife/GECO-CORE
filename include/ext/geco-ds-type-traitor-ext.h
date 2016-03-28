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
 * geco-ds-type-traitor-ext.h
 *
 *  Created on: 23 Mar 2016
 *      Author: jakez
 */

/*!
 * Put your own type traitor in this file
 * see example below
 */
#ifndef INCLUDE_GECO_DS_TYPE_TRAITOR_EXT_H_
#define INCLUDE_GECO_DS_TYPE_TRAITOR_EXT_H_

#include "geco-ds-config.h"

using namespace geco::ds;

struct test
{
};
GECO_TEMPLATE_NULL delc_true_type(test);

struct test2
{
};
GECO_TEMPLATE_NULL
delc_false_type(test2);

// or you can do this if you want to type more words
struct test1
{
};
GECO_TEMPLATE_NULL
struct type_traitor<test1>
{
    typedef true_type has_trivial_default_ctor;
    typedef true_type has_trivial_copy_ctor;
    typedef true_type has_trivial_assign_opt;
    typedef true_type has_trivial_dtor;
    typedef true_type is_pod_type;
};



#endif /* INCLUDE_GECO_DS_TYPE_TRAITOR_EXT_H_ */
