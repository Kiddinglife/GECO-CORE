///*
//*
//* Copyright (c) 1994
//* Hewlett-Packard Company SGI_STL
//*
//* Permission to use, copy, modify, distribute and sell this software
//* and its documentation for SGI_STL purpose is hereby granted without fee,
//* provided that the above copyright notice appear in all copies and
//* that both that copyright notice and this permission notice appear
//* in supporting documentation.  Hewlett-Packard Comp SGI_STL makes no
//* representations about the suitability of this software for SGI_STL
//* purpose.  It is provided "as is" without express or implied warranty.
//*
//* Copyright (c) 1997
//* Silicon Graphics
//*
//* Permission to use, copy, modify, distribute and sell this software
//* and its documentation for SGI_STL purpose is hereby granted without fee,
//* provided that the above copyright notice appear in all copies and
//* that both that copyright notice and this permission notice appear
//* in supporting documentation.  Silicon Graphics makes no
//* representations about the suitability of this software for SGI_STL
//* purpose.  It is provided "as is" without express or implied warranty.
//*
//* Copyright (c) 2016
//* Geco Gaming Company
//*
//* Permission to use, copy, modify, distribute and sell this software
//* and its documentation for GECO purpose is hereby granted without fee,
//* provided that the above copyright notice appear in all copies and
//* that both that copyright notice and this permission notice appear
//* in supporting documentation.  GECO makes no representations about
//* the suitability of this software for GECO purpose.
//* It is provided "as is" without express or implied warranty.
//*
//*/
//
///*
//* geco-malloc.h
//*
//* Created:   10 April 2016
//* Author:     jake zhang
//* E - mail:   Jakezhang1989@hotmail.com
//* GitHub:    https://github.com/Kiddinglife
//*/
//
//#ifndef DEFALLOC_H
//#define DEFALLOC_H
//
//#include <new>
//#include <cstddef>
//#include <cstdlib>
//#include <climits>
//#include <iostream>
//#include "geco-ds-malloc.h"
//
//template <class T>
//inline T* allocate(ptrdiff_t size, T*)
//{
//    set_new_handler(0);
//    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
//    if (tmp == 0) {
//        cerr << "out of memory" << endl;
//        exit(1);
//    }
//    return tmp;
//}
//
//
//template <class T>
//inline void deallocate(T* buffer) {
//    ::operator delete(buffer);
//}
//
//template <class T>
//class allocator {
//    public:
//    typedef T value_type;
//    typedef T* pointer;
//    typedef const T* const_pointer;
//    typedef T& reference;
//    typedef const T& const_reference;
//    typedef size_t size_type;
//    typedef ptrdiff_t difference_type;
//    pointer allocate(size_type n) {
//        return ::allocate((difference_type)n, (pointer)0);
//    }
//    void deallocate(pointer p) { ::deallocate(p); }
//    pointer address(reference x) { return (pointer)&x; }
//    const_pointer const_address(const_reference x) {
//        return (const_pointer)&x;
//    }
//    size_type init_page_size() {
//        return max(size_type(1), size_type(4096 / sizeof(T)));
//    }
//    size_type max_size() const {
//        return max(size_type(1), size_type(UINT_MAX / sizeof(T)));
//    }
//};
//
//class allocator<void> {
//    public:
//    typedef void* pointer;
//};
//
//
//
//#endif
