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
 * @file dma.c
 * @brief Memory manipulation with DMA
 *
 * This file contains the definitions for functions to
 * manipulate memory using DMA.
 *
 * @author Christopher Morroni
 * @date 2018-04-07
 */

#include <stdint.h>
#include <stddef.h> /* for size_t and NULL */
#include "dma.h"

uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length)
{
  if (src == NULL || dst == NULL) {
    return NULL;
  }

  return dst;
}

uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value)
{
  if (src == NULL) {
    return NULL;
  }

  return src;
}
