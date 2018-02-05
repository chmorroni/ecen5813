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
 * @file debug.c
 * @brief Functions for debug printing
 *
 * This file contains the definitions for functions to print while debugging.
 *
 * @author Christopher Morroni
 * @date 01/31/2018
 */

#include <stdint.h>
#include "platform.h"

void print_array(uint8_t * start, uint32_t length)
{
#ifdef DEBUG
  uint8_t i;
  for (i = 0; i < length; i++) {
    PRINTF("%x", start + i);
  }
#endif
  return;
}
