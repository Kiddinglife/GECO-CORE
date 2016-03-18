/*
 * geco-algo-base.h
 *
 *  Created on: 18 Mar 2016
 *      Author: jakez
 */

#ifndef INCLUDE_GECO_ALGO_BASE_H_
#define INCLUDE_GECO_ALGO_BASE_H_

#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstddef>
#include <new>

#include "geco-pair.h"
#include "geco-type-traits.h"

#ifdef __STL_USE_NEW_IOSTREAMS
#include <iosfwd>
#else /* __STL_USE_NEW_IOSTREAMS */
#include <iostream>
#endif /* __STL_USE_NEW_IOSTREAMS */

//#include <geco-iterator-base.h>
//#include <geco-iterator.h>

GECO_BEGIN_NAMESPACE

// copy
// All of these auxiliary functions serve two purposes.
// (1) Replace calls to copy with memmove whenever possible.
// (Memmove, not memcpy,because the input and output ranges
// are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count.
template<class InputIter, class OutputIter, class Distance>
inline OutputIter copy(InputIter copy_start_pos, InputIter copy_end_pos,
        OutputIter destination, input_iterator_tag, Distance*)
{

}
GECO_END_NAMESPACE
#endif /* INCLUDE_GECO_ALGO_BASE_H_ */
