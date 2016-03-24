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
using namespace geco::ds;

struct test
{
};
GECO_TEMPLATE_NULL
delc_true_type(test);

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
