// !!! remmber myself must put gtest header at the front otherwise you get xltmath errors noted at 24-March-2016
#include "gtest/gtest.h"
#include "include/geco-ds-config.h"
#include "include/geco-ds-iter-base.h"
#include "include/geco-ds-type-traitor.h"
#include "include/geco-ds-initialized.h"

#ifdef GECO_USE_NAMESPACES
using namespace geco::ds;
#endif

/*!
 * ITERATOR TRAITOR TEST
 * the reason why we use class partial specialization is that:
 * the iterator traitor is designed to trait all types of iterators' assciated types.
 * But for compiler that does not support class partial specialization,
 * raw pointer iterator's assciated types cannot be traited normally.
 * and so, these compilers have to use another way to trait assciated types,
 * which is called 'overloaded functons'
 */
template<class Category, class Type, class Distance = ptrdiff_t,
        class Pointer = Type*, class Reference = Type&>
struct test_inter: public iterator<Category, Type, Distance, Pointer, Reference>
{
        const test_inter& operator++()
        {
            return *this;
        }

        test_inter operator++(int n)
        {
            return *this;
        }
};

TEST(IteratorTraitor, test_trait_assciated_types)
{

    //iterator delc
    //template<class Category,
    //class Type, class Distance = ptrdiff_t,
    //class Pointer = Type*, class Reference = Type&>
    //struct iterator {....}

    //! first use standard iterator when GECO_CLASS_PARTIAL_SPECIALIZATION defined
    //! itertor traitor will be used to trait iter cate
    typedef test_inter<forward_iterator_tag, int> iter;
    iter input_iter = iter();
    __advance(input_iter, 12, iterator_traitor<iter>::iterator_category());

    //! first use non-standard iterator when GECO_CLASS_PARTIAL_SPECIALIZATION NOT defined
    //! function overload will be used to trait iter cate
    typedef test_inter<forward_iterator<int, ptrdiff_t>, int> iter1;
    iter1 input_iter1 = iter1();
    __advance(input_iter1, 12, iter1::iterator_category::iterator_category());

}
