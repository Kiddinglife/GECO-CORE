/*
 * test-geco-alog-h.cc
 *
 *  Created on: 24 Mar 2016
 *      Author: jakez
 */

#include "include/geco-ds-config.h"
#include "include/geco-ds-algo-base.h"
#include "include/geco-ds-iter-base.h"
#include "gtest/gtest.h"

#ifdef GECO_USE_NAMESPACES
using namespace geco::ds;
#endif

TEST(CopyTests, test_how_copy_is_used)
{
    typedef iterator<random_access_iterator<int, ptrdiff_t>, int> iter;
    iter start;
    iter end;
    iter dest;
    copy(start, end, dest);
}
