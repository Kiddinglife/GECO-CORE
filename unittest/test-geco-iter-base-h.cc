#include "gtest/gtest.h"
#include "include/geco-config.h"
#include "include/geco-type-traits.h"
#include "include/geco-iter-base.h"

#ifdef GECO_USE_NAMESPACES
using namespace geco::ds;
#endif

template<class InputIter, class Distance>
inline void advance(InputIter& i, Distance n, input_iterator_tag)
{
    printf("input_iterator_tag advance\n");
}

template<class BidirectionalIter, class Distance>
inline void advance(BidirectionalIter& i, Distance n,
        bidirectional_iterator_tag)
{
    printf("bidirectional_iterator_tag advance\n");
}

template<class _RandomAccessIterator, class Distance>
inline void advance(_RandomAccessIterator& i, Distance n,
        random_access_iterator_tag)
{
    printf("random_access_iterator_tag advance\n");
}

template<class IteType, class Distance>
inline void advance_(const IteType& i, Distance n)
{
    advance(i, n, GET_ITER_CATEGORY(i));
}

/*!
 * ITERATOR TRAITOR TEST
 * the reason why we use class partial specialization is that:
 * the iterator traitor is designed to trait all types of iterators' assciated types.
 * But for compiler that does not support class partial specialization,
 * raw pointer iterator's assciated types cannot be traited normally.
 * and so, these compilers have to use another way to trait assciated types,
 * which is called 'overloaded functons'
 */
TEST(IteratorTraitor, test_trait_assciated_types)
{
    //iterator delc
    //template<class Category,
    //class Type, class Distance = ptrdiff_t,
    //class Pointer = Type*, class Reference = Type&>
    //struct iterator {....}

    typedef iterator<random_access_iterator<int, ptrdiff_t>, int> iter;
    typedef iter::iterator_category cat;
    advance_(cat(), 12);

    typedef iterator<input_iterator<int, ptrdiff_t>, int> iter1;
    typedef iter1::iterator_category cat1;
    advance_(cat1(), 12);

}
