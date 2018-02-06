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
 * @file conversion.c
 * @brief Functions for basic data manipulations
 *
 * This file contains the definitions for functions to manipulate data.
 *
 * @author Christopher Morroni
 * @date 01/31/2018
 */

#include <stdint.h>
#include <stddef.h> /* for NULL */
#include "conversion.h"

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
  if (ptr == NULL || base < 2 || base > 16) {
    return 0;
  }
  return 0;
}

uint32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
  if (ptr == NULL || base < 2 || base > 16) {
    return 0;
  }
  return 0;
}
