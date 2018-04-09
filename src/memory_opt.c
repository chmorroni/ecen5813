/******************************************************************************
 * Copyright (C) 2018
 * Christopher Morroni and Matthew Haney
 * University of Colorado, Boulder
 *
 * Redistribution, modification, or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Christopher Morroni, Matthew Haney, and the University of
 * Colorado are not liable for any misuse of this material.
 *
 *****************************************************************************/
/**
 * @file memory_opt.c
 * @brief Optimized versions of selected memory operations from memory.c
 *
 * This file contains the definitions for functions to manipulate memory.
 *
 * @author Christopher Morroni
 * @date 2018-04-08
 */

#include <stdint.h>
#include <stddef.h> /* for size_t and NULL */
#include "memory_opt.h"

uint8_t * __attribute__((optimize("O3"))) my_memmove_opt(uint8_t * src, uint8_t * dst, size_t length)
{
  if (src == NULL || dst == NULL) {
    return NULL;
  }

  if( src < dst && src + length > dst )
  {
    int32_t i;
    for(i = length - 1; i >= 0; i--)
    {
      *(dst + i) = *(src + i);
    }
  }
  else
  {
    my_memcpy_opt(src, dst, length);
  }

  return dst;
}

uint8_t * __attribute__((optimize("O3"))) my_memcpy_opt(uint8_t * src, uint8_t * dst, size_t length)
{
  if (src == NULL || dst == NULL) {
    return NULL;
  }

  int32_t i;
  for(i = 0; i < length; i++)
  {
    *(dst + i) = *(src + i);
  }

  return dst;
}

uint8_t * __attribute__((optimize("O3"))) my_memset_opt(uint8_t * src, size_t length, uint8_t value)
{
  if (src == NULL) {
    return NULL;
  }

  int32_t i;
  for(i = 0; i < length; i++)
  {
    *(src + i) = value;
  }

  return src;
}
