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

TEST(TypeTraitor, test_trait_type)
{
    int a = int();
    printf("int a '%d'\n", a);
    int *s = 0;
    int *d = 0;
    bool val = mcopy<int>(s, d, 12);
    EXPECT_EQ(true, val);
}


