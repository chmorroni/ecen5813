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
 * @file data.c
 * @brief Functions for printing the sizes of variable types
 *
 * @author Christopher Morroni
 * @date 01/31/2018
 */

#include <stdint.h>
#include <stddef.h> /* for size_t and NULL */
#include "data.h"

void print_cstd_type_sizes()
{
}

void print_stdint_type_sizes()
{
}

void print_pointer_sizes()
{
}

int32_t swap_data_endianness(uint8_t * data, size_t type_length)
{
  if (data == NULL) {
    /* Return error if null pointer is passed */
    return SWAP_ERROR;
  } else if (type_length == 1) {
    /* Don't do anything if it's just a byte */
    return SWAP_NO_ERROR;
  }
  /* Do endianness swap */
  size_t offset;
  uint8_t tmp_byte;
  for (offset = 0; offset < type_length / 2; offset++) {
    tmp_byte = *(data + offset);
    *(data + offset) = *(data + type_length - offset - 1);
    *(data + type_length - offset - 1) = tmp_byte;
  }
  return SWAP_NO_ERROR;
}

uint32_t determine_endianness()
{
  uint16_t end_test = 0xABCD;
  uint8_t * top_half = (uint8_t*) &end_test;
  if (*top_half == 0xCD) {
    return LITTLE_ENDIAN;
  } else if (*top_half == 0xAB) {
    return BIG_ENDIAN;
  } else {
    /* This should not happen */
    return -1;
  }
}
