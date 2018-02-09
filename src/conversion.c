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
#include "memory.h"

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
  if (ptr == NULL || base < 2 || base > 16) {
    return 0;
  }

  uint8_t len = 0, val;

  /* check for sign */
  if(data < 0)
  {
    data *= -1;
    *ptr = '-';
    len++;
  }

  /* this uses modulus and divide to find the value in each place */
  do
  {
    val = data % base;
    *(ptr + len++) = val < 10 ? '0' + val : 'A' + val - 10;
    data /= base;
  } while(data != 0);

  /* reverse the numbers */
  if(*ptr == '-')
  {
    my_reverse(ptr + 1, len - 1);
  }
  else
  {
    my_reverse(ptr, len);
  }

  *(ptr + len++) = '\0';

  return len;
}

uint32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
  if (ptr == NULL || base < 2 || base > 16) {
    return 0;
  }

  uint32_t val = 0;

  /* start at the second character if negative */
  uint8_t i = *ptr == '-' ? 1 : 0;

  /* this multiplies and adds to convert to an integer */
  for(; i < digits - 1; i++)
  {
    val *= base;
    val = (*(ptr + i) > '9') ? (val + *(ptr + i) - 'A' + 10) : (val + *(ptr + i) - '0');
  }

  /* get the sign */
  if(*ptr == '-')
  {
    val *= -1;
  }

  return val;
}
