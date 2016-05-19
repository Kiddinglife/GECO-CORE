/*
 * test-geco-alog-h.cc
 *
 *  Created on: 24 Mar 2016
 *      Author: jakez
 */

#include "gtest/gtest.h"
#include "include/geco-ds-config.h"
#include "include/geco-ds-algo-base.h"
#include "include/geco-ds-iter-base.h"
#include "include/geco-ds-malloc.h"

#ifdef GECO_USE_NAMESPACES
using namespace geco::ds;
#endif

TEST(CopyTests, test_how_copy_is_used)
{
    typedef random_access_iterator<int, ptrdiff_t> iter;
    iter start;
    iter end;
    iter dest;
    //copy(start, end, dest);
}

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;


TEST(ALLOCtEST, TEST_ALLOC_DEALLOC)
{
    int times = 0;
    for (int j = 0; j <= 1512; j++)
    {
        times++;
        char* intptr = (char*)single_client_alloc::allocate(j);
        char* intptr1 = (char*)single_client_alloc::allocate(j);
        int mod=0;
        int i;
        if (intptr != NULL)
            memset(intptr, 0, j); //3000ms

        // 1600ms
        //if (j > sizeof(int))
        //    mod = j % sizeof(int);
        //int* ptr = (int*)intptr;
        //for (i = 0; i < i - mod; i++)
        //{
        //    *(ptr + i) = 0;
        //}
        //for (i = 0; i < mod; i++)
        //{
        //    *(intptr + i) = 0;
        //}
        //alloc::deallocate(otr2, j);
        single_client_alloc::deallocate(intptr, j);
        single_client_alloc::deallocate(intptr1, j);
        if (j >= 1512) j = 0;
        if (times >= 100000) break;
    }
    single_client_alloc::destroy();
}
