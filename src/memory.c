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
 * @file memory.c
 * @brief Memory manipulation functions
 *
 * This file contains the definitions for functions to manipulate memory.
 *
 * @author Christopher Morroni
 * @date 01/31/2018
 */

#include <stdint.h>
#include <stddef.h> /* for size_t and NULL */
#include <stdlib.h> /* for malloc and free */
#include "memory.h"

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
  if (src == NULL || dst == NULL) {
    return NULL;
  }

  uint8_t * temp = (uint8_t*)malloc(length);
  my_memcpy(src, temp, length);
  my_memcpy(temp, dst, length);
  free(temp);

  return dst;
}

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length)
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

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value)
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

uint8_t * my_memzero(uint8_t * src, size_t length)
{
  if (src == NULL) {
    return NULL;
  }

  int32_t i;
  for(i = 0; i < length; i++)
  {
    *(src + i) = 0;
  }

  return src;
}

uint8_t * my_reverse(uint8_t * src, size_t length)
{
  if (src == NULL) {
    return NULL;
  }

  uint8_t temp;
  int32_t i;
  for(i = 0; i < length / 2; i++)
  {
    temp = *(src + i);
    *(src + i) = *(src + length - 1 - i);
    *(src + length - 1 - i) = temp;
  }

  return src;
}

int32_t * reserve_words(size_t length)
{
  return malloc(length * 4);
}

uint8_t free_words(uint32_t * src)
{
  if(src == NULL)
  {
    return 1;
  }

  free(src);
  return 0;
}
