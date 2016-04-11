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
 * geco-malloc.h
 *
 *  Created on: 22 Mar 2016
 * Author:     jake zhang
 * E - mail:   Jakezhang1989@hotmail.com
 * GitHub:    https://!github.com/Kiddinglife
 */

#ifndef __INCLUDE_GECO_DS_MALLOC_H
#define __INCLUDE_GECO_DS_MALLOC_H

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cassert>
#ifndef __RESTRICT
#  define __RESTRICT
#endif
#include "geco-ds-config.h"

#ifdef __SUNPRO_CC
#   define PRIVATE public
//! SUN编译器对private限制过多, 需要开放权限 
//! Extra access restrictions prevent us from really making some things
//! private.
#else
#   define PRIVATE private
#endif

//! 为了保证兼容性, 对于不支持模板类静态成员的情况, 使用malloc()进行内存分配 
#ifdef GECO_STATIC_TEMPLATE_MEMBER_BUG
#  define GECO_USE_MALLOC
#endif

//! allocation primitives意在分配不大于原始STL allocator分配的独立的对象  
//! This implements some standard node allocators.  These are
//! NOT the same as the allocators in the C++ draft standard or in
//! in the original STL.  They do not encapsulate different pointer
//! types; indeed we assume that there is only one pointer type.
//! The allocation primitives are intended to allocate individual objects,
//! not larger arenas as with the original STL allocators.
#ifndef THROW_BAD_ALLOC
#  if defined(GECO_NO_BAD_ALLOC) || !defined(GECO_USE_EXCEPTIONS)
#    include <cstdio>
#    define THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1)
#  else /* Standard conforming out-of-memory handling */
#    include <new>
#    define THROW_BAD_ALLOC throw std::bad_alloc()
#  endif
#endif

#if defined(GECO_USE_STL_THREADS) && !defined(GECO_NO_THREADS)
#include "geco-stl-thread.h"
#define GECO_ALLOC_USES_THREAD true
# ifdef GECO_SGI_THREADS
//! We test whether threads are in use before locking.
//! Perhaps this should be moved into stl_threads.h, but that
//! probably makes it harder to avoid the procedure call when
//! it isn't needed.
extern "C"
{
    extern int __us_rsthread_malloc;
}
//! The above is copied from malloc.h.  Including <malloc.h>
//! would be cleaner but fails with certain levels of standard
//! conformance.
# define GECO_ALLOC_LOCK \
if (threads && __us_rsthread_malloc) \
{ _S_node_allocator_lock._M_acquire_lock(); }
# define GECO_ALLOC_UNLOCK
if (threads && __us_rsthread_malloc)
{   _S_node_allocator_lock._M_release_lock();}
# else /* !GECO_SGI_THREADS */
# define GECO_ALLOC_LOCK \
{ if (threads) _S_node_allocator_lock._M_acquire_lock(); }
# define GECO_ALLOC_UNLOCK \
{ if (threads) _S_node_allocator_lock._M_release_lock(); }
# endif
#else
//!  Thread-unsafe
# define GECO_ALLOC_LOCK
# define GECO_ALLOC_UNLOCK
# define GECO_ALLOC_USES_THREAD false
#endif

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

GECO_BEGIN_NAMESPACE
//! Malloc-based allocator.  Typically slower than default alloc below.
//! Typically thread-safe and more storage efficient.
#ifdef GECO_STATIC_TEMPLATE_MEMBER_BUG
# ifdef DECLARE_GLOBALS_HERE
void (* __malloc_alloc_oom_handler)() = 0;
//! g++ 2.7.2 does not handle static template data members.
# else
extern void (* __malloc_alloc_oom_handler)();
# endif
#endif

#define alloc_type_first 1
#define alloc_type_second 2

//! 一级配置器  使用malloc()分配内存
template<int inst>
class malloc_alloc
{
private:

#ifndef GECO_STATIC_TEMPLATE_MEMBER_BUG
    //!! 如果编译器支持模板类静态成员, 则使用错误处理函数, 类似C++的set_new_handler()  
    //!! 默认值为0, 如果不设置, 则内存分配失败时直接THROW_BAD_ALLOC. 
    static void(*oom_handler)();
#endif

    //!! 使用malloc()循环分配内存,  直到成功分配  
    static void* oom_malloc(size_t size)
    {
        //! 如果设置了oom_handler, 则首先执行错误处理函数, 然后循环分配直到成功
        //! 如果未设置oom_handler, THROW_BAD_ALLOC  
        void(*my_oom_handler)() = 0;
        void* result = 0;
        while (result == 0)
        {
            my_oom_handler = oom_handler;
            if (my_oom_handler == 0)
            {   THROW_BAD_ALLOC;}
            (*my_oom_handler)();
            result = malloc(size);
        }
        return result;
    }

    //!! 使用realloc()循环分配内存,  直到成功分配 
    static void* oom_realloc(void* pointer, size_t size)
    {
        void(*my_oom_handler)() = 0;
        void* result = 0;
        while (result == 0)
        {
            my_oom_handler = oom_handler;
            if (my_oom_handler == 0)
            {   THROW_BAD_ALLOC;}
            (*my_oom_handler)();
            result = realloc(pointer, size);
        }
        return result;
    }

public:
    //!! 分配指定大小的内存(size_t n)， 如果分配失败, 则进入循环分配阶段
    //!! 循环分配前提是要保证正确设置了oom_handler.
    static void* allocate(size_t size)
    {
        void* result = malloc(size);
        if (0 == result) result = oom_malloc(size);
        return result;
    }

    //!! 后面的size_t是为了兼容operator delele
    static void deallocate(void* pointer, size_t size)
    {
        free(pointer);
    }

    //! 重新分配内存大小, 第二个参数是为了兼容operator new 
    static void* reallocate(void* pointer, size_t old_size, size_t new_size)
    {
        void* result = realloc(pointer, new_size);
        if (0 == result) result = oom_realloc(pointer, new_size);
        return result;
    }

    //!! 设置错误处理函数, 返回原来的函数指针 
    //!! 不属于C++标准规定的接口  
    static void(*set_oom_handler(void(*oom_handler_)()))()
    {
        void(*old)() = oom_handler;
        oom_handler = oom_handler_;
        return (old);
    }
};

//! 这个版本的STL并没有使用non-type模板参数 
typedef typename malloc_alloc<0> malloc_allocator;

//! initialize out-of-memory handler when malloc() fails
#ifndef GECO_STATIC_TEMPLATE_MEMBER_BUG
template <int inst>
void(*malloc_alloc<inst>::oom_handler)() = 0;
#endif

//! simple_alloc中的接口其实就是STL标准中的allocator的接口  
//! 实际上所有的SGI STL都使用这个进行内存配置  
//! 例如: stl_vector.h中  
//! template <class T, class Alloc = alloc>  
//! class vector  
//! {  
//!      ...  
//! protected:  
//!      typedef simple_alloc<value_type, Alloc> data_allocator;  
//!      ...  
//!};  
template <class ValueType, class Alloc>
class simple_alloc
{
public:
    static ValueType* allocate(size_t size)
    {
        return size == 0 ? 0 : Alloc::allocate(size*sizeof(ValueType));
    }
    static ValueType* allocate(void)
    {
        return (ValueType*)Alloc::allocate(sizeof(ValueType));
    }
    static void deallocate(ValueType* pointer, size_t size)
    {
        if (0 != size) Alloc::deallocate(pointer, size * sizeof(ValueType));
    }
    static void deallocate(ValueType* pointer)
    {
        Alloc::deallocate(pointer, sizeof(ValueType));
    }
};

//! Allocator adaptor to check size arguments for debugging.
//! Reports errors using assert.  Checking can be disabled with
//! NDEBUG, but it's far better to just use the underlying allocator
//! instead when no checking is desired.
//! There is some evidence that this can confuse Purify.
//! Purify is the C/C++ memory checker
template <class Alloc>
class debug_alloc
{
private:
    enum
    {   extra_size = 8};  //! Size of space used to store size.  Note

    //! that this must be large enough to preserve
    //! alignment.
    //! extra 保证不会分配为0的内存空间, 而且要保证内存对齐  
    //! 把分配内存的最前面设置成n的大小, 用于后面校验  
    //! 内存对齐的作用就是保护前面extra大小的数据不被修改  
    static void* allocate(size_t size)
    {
        char* __result = (char*)Alloc::allocate(size + (int)extra_size);
        *(size_t*)__result = size;
        return __result + (int)extra_size;
    }

    static void deallocate(void* pointer, size_t size)
    {
        char* __real_p = (char*)pointer - (int)extra_size;
        assert(*(size_t*)__real_p == size); //! 如果*(size_t *)real_p != n则肯定发生向前越界
        Alloc::deallocate(__real_p, size + (int)extra_size);
    }

    static void* reallocate(void* pointer, size_t __old_sz, size_t __new_sz)
    {
        char* __real_p = (char*)pointer - (int)extra_size;
        assert(*(size_t*)__real_p == __old_sz);
        char* result = (char*)Alloc::reallocate(__real_p,
                __old_sz + (int)extra_size,
                __new_sz + (int)extra_size);
        *(size_t*)result = __new_sz;
        return result + (int)extra_size;
    }
};

//!编译器不支持template member的话，使用malloc()
#ifdef GECO_USE_MALLOC
typedef typename malloc_alloc_0 alloc;
typedef typename malloc_alloc_0 single_client_alloc;
#else
//! Sun C++ compiler需要在类外定义这些枚举  
#if defined(__SUNPRO_CC) || defined(__GNUC__)  || defined(__HP_aCC)
//! breaks if we make these template class members:
enum
{   ALIGN = 8};
enum
{   MAX_BYTES = 256};
enum
{   NFREELISTS = 32}; //! _MAX_BYTES/_ALIGN
#endif
//! Default node allocator.
//! With a reasonable compiler, this should be roughly as fast as the
//! original STL class-specific allocators, but with less fragmentation.
//! default_alloc parameters are experimental and MAY
//! DISAPPEAR in the future.  Clients should just use alloc for now.
//!
//! Important implementation properties:
//! 1. If the client request an object of size > _MAX_BYTES, the resulting
//!    object will be obtained directly from malloc.
//! 2. In all other cases, we allocate an object of size exactly
//!    _S_round_up(requested_size).  Thus the client has enough size
//!    information that we can return the object to the proper free list
//!    without permanently losing part of the object.
//!

//! The first template parameter specifies whether more than one thread
//! may use this allocator.  It is safe to allocate an object from
//! one instance of a default_alloc and deallocate it with another
//! one.  This effectively transfers its ownership to the second one.
//! This may have undesirable effects on reference locality.
//! The second parameter is unreferenced and serves only to allow the
//! creation of multiple default_alloc instances.
//! Node that containers built on different allocator instances have
//! different types, limiting the utility of this approach.
template <bool threads, int inst>
class default_alloc
{
    PRIVATE:
    // the sizeof(Unit) = bigger member's size = sizeof(Unit*) = 4 bytes
    union Unit
    {
        // when allcate, this field will be used to update next avaiable freelist
        // then it will be given to client who will be using this union safely
        //when reclaim, this field will be assigne a value and link to another uable freelist
        union Unit* _M_free_list_link;
        // The client sees this because it will be returned as pointer to client
        char _M_client_data[1];
    };

private:
#if ! (defined(__SUNPRO_CC) || defined(__GNUC__))
    //! Really we should use static const int x = N
    //! instead of enum { x = N }, but few compilers accept the former.
    enum
    {   ALIGN = 8};
    enum
    {   MAX_BYTES = 256};
    enum
    {   NFREELISTS = 32}; //! _MAX_BYTES/_ALIGN
# endif

# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
    static Unit* GECO_VOLATILE free_list[];
    // Specifying a size results in duplicate def for 4.1
# else
    // 这里分配的free_list为16  
    // 对应的内存链容量分别为8, 16, 32 ... 128  
    static Unit* GECO_VOLATILE free_list[NFREELISTS];
# endif

    // Unit allocation state.
    static char* start_free;// pool start address in each chunk
    static char* end_free;//  pool end address in each chunk
    static size_t heap_size;// 已经在堆上分配的空间大小

    // threads
# ifdef __STL_THREADS
    static _STL_mutex_lock _S_node_allocator_lock;
# endif

    // It would be nice to use _STL_auto_lock here.  But we
    // don't need the NULL check.  And we do need a test whether
    // threads have actually been started.
    struct Guard;
    friend struct Guard;
    struct Guard
    {
        Guard()
        {   GECO_ALLOC_LOCK;}
        ~Guard()
        {   GECO_ALLOC_UNLOCK;}
    };

    //! 向上舍入操作
    //! 解释一下, ALIGN - 1指明的是实际内存对齐的粒度
    //! 例如ALIGN = 8时, 我们只需要7就可以实际表示8个数(0~7)
    //! 那么~(ALIGN - 1)就是进行舍入的粒度
    //! 我们将(bytes) + ALIGN-1)就是先进行进位, 然后截断
    //! 这就保证了我是向上舍入的
    //! 例如byte = 100, ALIGN = 8的情况
    //! ~(ALIGN - 1) = (1 000)B
    //! ((bytes) + ALIGN-1) = (1 101 011)B
    //! (((bytes) + ALIGN-1) & ~(ALIGN - 1)) = (1 101 000 )B = (104)D
    //! 104 / 8 = 13, 这就实现了向上舍入
    //! 对于byte刚好满足内存对齐的情况下, 结果保持byte大小不变
    //! 记得《Hacker's Delight》上面有相关的计算
    //! 这个表达式与下面给出的等价
    //! ((((bytes) + _ALIGN - 1) * _ALIGN) / _ALIGN)
    //! 但是SGI STL使用的方法效率非常高
    static size_t round_up(size_t size)
    {
        return (((size)+(size_t)ALIGN - 1) & ~((size_t)ALIGN - 1));
    }

    //! 根据待待分配的空间大小, 在free_list中选择合适的大小
    static size_t freelist_index(size_t size)
    {
        return (((size)+(size_t)ALIGN - 1) / (size_t)ALIGN - 1);
    }

    //! Returns an object of size __n, and optionally adds to size __n free list.
    static void* refill(size_t size);

    //! Allocates a number of chunks one-shot. num may be reduced
    //! if it is inconvenient to allocate the requested number.
    static char* alloc_chunk(size_t aligned_uint_size, int& unit_num);

public:
    static void* allocate(size_t size)
    {
        void* ret = 0;
        if (size > (size_t)MAX_BYTES)
        {
            ret = malloc_allocator::allocate(size);
        }
        else
        {
            Unit* GECO_VOLATILE* my_free_list = free_list + freelist_index(size);
            // Acquire the lock here with a constructor call.
            // This ensures that it is released in exit or during stack
            // unwinding.
#if defined(GECO_USE_STL_THREADS) && !defined(GECO_NO_THREADS)
            Guard locker_guard;
#endif
            Unit* __RESTRICT result = *my_free_list;
            if(result == 0)
            {
                ret = refill(round_up(size));
            }
            else
            {
                *my_free_list = result->_M_free_list_link;
                ret = result;
            }
        }
        return ret;
    }

    static void deallocate(void* pointer, size_t size)
    {
        GECO_assert(pointer != 0);

    }
};

typedef typename default_alloc<GECO_ALLOC_USES_THREAD, 0> alloc;
typedef typename default_alloc<false, 0> single_client_alloc;

// INITIALIZE MEMBERS
#ifdef __STL_THREADS
template <bool __threads, int __inst>
_STL_mutex_lock
default_alloc<__threads, __inst>::_S_node_allocator_lock
__STL_MUTEX_INITIALIZER;
#endif

template<bool threads, int inst>
char* default_alloc<threads, inst>::start_free = 0;
template<bool threads, int inst>
char* default_alloc<threads, inst>::end_free = 0;
template<bool threads, int inst>
size_t default_alloc<threads, inst>::heap_size = 0;

template<bool threads, int inst>
typename default_alloc<threads, inst>::Unit* GECO_VOLATILE
default_alloc<threads, inst>::free_list[
#if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
NFREELISTS
# else
default_alloc<threads, inst>::NFREELISTS
# endif
] =
{   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// The 16 zeros are necessary to make version 4.1 of the SunPro
// compiler happy.  Otherwise it appears to allocate too little
// space for the array.

#endif
GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_DS_MALLOC_H_ */
