#include "gtest/gtest.h"
#include "geco-type-traits.h"

//copy an array of elments which have non-trivial copy ctors.
template<class Type>
inline bool copy(Type* source, Type* destination, int n, FalseType falseType)
{
    return false;
}

//copy an array of elments which have trivial copy ctors. this function will use memcpy().
template<class Type>
inline bool copy(Type* source, Type* destination, int n, TrueType trueType)
{
    return true;
}

//copy an array of elements by using the most efficient copy mechanism.
template<class Type>
inline bool copy(Type* source, Type* destination, int n)
{
    typedef typename TypeTraits<Type>::has_trivial_copy_ctor has_trivial_copy_ctor;
    return copy(source, destination, n, has_trivial_copy_ctor());
}

TEST(testcase2, testHello2)
{
    int *s = 0;
    int *d = 0;
    bool val = copy<int>(s, d, 12);
    EXPECT_EQ(true, val);
}

