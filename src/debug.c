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
