#include "gtest/gtest.h"
#include "include/geco-ds-config.h"
#include "include/geco-ds-iter-base.h"
#include "include/geco-ds-type-traitor.h"

#ifdef GECO_USE_NAMESPACES
using namespace geco::ds;
#endif


//copy an array of elments which have non-trivial copy ctors.
template<class Type>
inline bool mcopy(Type* source, Type* destination, int n, false_type)
{
    return false;
}

//copy an array of elments which have trivial copy ctors. this function will use memcpy().
template<class Type>
inline bool mcopy(Type* source, Type* destination, int n, true_type)
{
    return true;
}

//copy an array of elements by using the most efficient copy mechanism.
template<class Type>
inline bool mcopy(Type* source, Type* destination, int n)
{
    typedef typename type_traitor<Type>::has_trivial_copy_ctor has_trivial_copy_ctor;
    return mcopy(source, destination, n, has_trivial_copy_ctor());
}
# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define GECO_PTHREADS
# endif
#include "include/geco-ds-type-traitor-ext.h"
TEST(TypeTraitor, test_trait_types)
{
    void **s = 0;
    void **d = 0;
    bool val = mcopy<void*>(s, d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<wchar_t>((wchar_t*)s, (wchar_t*)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned wchar_t>((unsigned wchar_t*)s, (unsigned wchar_t*)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<int>((int*)s, (int*)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned int>((unsigned int*)s, (unsigned int*)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<short>((short*)s, (short*)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned short>((unsigned short*)s, (unsigned short*)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<char>((char*)s, (char*)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned char>((unsigned char*)s, (unsigned char*)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<float>((float*)s, (float*)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<double>((double*)s, (double*)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<int*>((int**)s, (int**)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned int*>((unsigned int**)s, (unsigned int**)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<short*>((short**)s, (short**)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned short*>((unsigned short**)s, (unsigned short**)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<char*>((char**)s, (char**)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned char*>((unsigned char**)s, (unsigned char**)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<wchar_t*>((wchar_t**)s, (wchar_t**)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<unsigned wchar_t*>((unsigned wchar_t**)s, (unsigned wchar_t**)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<float*>((float**)s, (float**)d, 12);
    EXPECT_EQ(true, val);
    val = mcopy<double*>((double**)s, (double**)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<test_cus_type_false>((test_cus_type_false*)s, (test_cus_type_false*)d, 12);
    EXPECT_EQ(false, val);

    val = mcopy<test_cus_type_true>((test_cus_type_true*)s, (test_cus_type_true*)d, 12);
    EXPECT_EQ(true, val);

    val = mcopy<test_cus_type_false>((test_cus_type_false*)s, (test_cus_type_false*)d, 12);
    EXPECT_EQ(false, val);
}


