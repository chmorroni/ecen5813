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
#include "platform.h"
#include "data.h"

void print_cstd_type_sizes()
{
#ifdef PLATFORM_HOST
  /* Unsigned long for host platform */
  PRINTF("char: %lu bytes\n", sizeof(char));
  PRINTF("short: %lu bytes\n", sizeof(short));
  PRINTF("int: %lu bytes\n", sizeof(int));
  PRINTF("long: %lu bytes\n", sizeof(long));
  PRINTF("double: %lu bytes\n", sizeof(double));
  PRINTF("float: %lu bytes\n", sizeof(float));
  PRINTF("unsigned char: %lu bytes\n", sizeof(unsigned char));
  PRINTF("unsigned int: %lu bytes\n", sizeof(unsigned int));
  PRINTF("unsigned long: %lu bytes\n", sizeof(unsigned long));
  PRINTF("signed char: %lu bytes\n", sizeof(signed char));
  PRINTF("signed int: %lu bytes\n", sizeof(signed int));
  PRINTF("signed long: %lu bytes\n", sizeof(signed long));
#endif
#ifdef PLATFORM_BBB
  /* Just unsigned int for BBB */
  PRINTF("char: %u bytes\n", sizeof(char));
  PRINTF("short: %u bytes\n", sizeof(short));
  PRINTF("int: %u bytes\n", sizeof(int));
  PRINTF("long: %u bytes\n", sizeof(long));
  PRINTF("double: %u bytes\n", sizeof(double));
  PRINTF("float: %u bytes\n", sizeof(float));
  PRINTF("unsigned char: %u bytes\n", sizeof(unsigned char));
  PRINTF("unsigned int: %u bytes\n", sizeof(unsigned int));
  PRINTF("unsigned long: %u bytes\n", sizeof(unsigned long));
  PRINTF("signed char: %u bytes\n", sizeof(signed char));
  PRINTF("signed int: %u bytes\n", sizeof(signed int));
  PRINTF("signed long: %u bytes\n", sizeof(signed long));
#endif
}

void print_stdint_type_sizes()
{
#ifdef PLATFORM_HOST
  /* Unsigned long for host platform */
  PRINTF("int8_t: %lu bytes\n", sizeof(int8_t));
  PRINTF("uint8_t: %lu bytes\n", sizeof(uint8_t));
  PRINTF("int16_t: %lu bytes\n", sizeof(int16_t));
  PRINTF("uint16_t: %lu bytes\n", sizeof(uint16_t));
  PRINTF("int32_t: %lu bytes\n", sizeof(int32_t));
  PRINTF("uint32_t: %lu bytes\n", sizeof(uint32_t));
  PRINTF("uint_fast8_t: %lu bytes\n", sizeof(uint_fast8_t));
  PRINTF("uint_fast16_t: %lu bytes\n", sizeof(uint_fast16_t));
  PRINTF("uint_fast32_t: %lu bytes\n", sizeof(uint_fast32_t));
  PRINTF("uint_least8_t: %lu bytes\n", sizeof(uint_least8_t));
  PRINTF("uint_least16_t: %lu bytes\n", sizeof(uint_least16_t));
  PRINTF("uint_least32_t: %lu bytes\n", sizeof(uint_least32_t));
  PRINTF("size_t: %lu bytes\n", sizeof(size_t));
  PRINTF("ptrdiff_t: %lu bytes\n", sizeof(ptrdiff_t));
#endif
#ifdef PLATFORM_BBB
  /* Just unsigned int for BBB */
  PRINTF("int8_t: %u bytes\n", sizeof(int8_t));
  PRINTF("uint8_t: %u bytes\n", sizeof(uint8_t));
  PRINTF("int16_t: %u bytes\n", sizeof(int16_t));
  PRINTF("uint16_t: %u bytes\n", sizeof(uint16_t));
  PRINTF("int32_t: %u bytes\n", sizeof(int32_t));
  PRINTF("uint32_t: %u bytes\n", sizeof(uint32_t));
  PRINTF("uint_fast8_t: %u bytes\n", sizeof(uint_fast8_t));
  PRINTF("uint_fast16_t: %u bytes\n", sizeof(uint_fast16_t));
  PRINTF("uint_fast32_t: %u bytes\n", sizeof(uint_fast32_t));
  PRINTF("uint_least8_t: %u bytes\n", sizeof(uint_least8_t));
  PRINTF("uint_least16_t: %u bytes\n", sizeof(uint_least16_t));
  PRINTF("uint_least32_t: %u bytes\n", sizeof(uint_least32_t));
  PRINTF("size_t: %u bytes\n", sizeof(size_t));
  PRINTF("ptrdiff_t: %u bytes\n", sizeof(ptrdiff_t));
#endif
}

void print_pointer_sizes()
{
#ifdef PLATFORM_HOST
  /* Unsigned long for host platform */
  PRINTF("char*: %lu bytes\n", sizeof(char*));
  PRINTF("short*: %lu bytes\n", sizeof(short*));
  PRINTF("int*: %lu bytes\n", sizeof(int*));
  PRINTF("long*: %lu bytes\n", sizeof(long*));
  PRINTF("double*: %lu bytes\n", sizeof(double*));
  PRINTF("float*: %lu bytes\n", sizeof(float*));
  PRINTF("void*: %lu bytes\n", sizeof(void*));
  PRINTF("int8_t*: %lu bytes\n", sizeof(int8_t*));
  PRINTF("int16_t*: %lu bytes\n", sizeof(int16_t*));
  PRINTF("int32_t*: %lu bytes\n", sizeof(int32_t*));
  PRINTF("char**: %lu bytes\n", sizeof(char**));
  PRINTF("int**: %lu bytes\n", sizeof(int**));
  PRINTF("void**: %lu bytes\n", sizeof(void**));
#endif
#ifdef PLATFORM_BBB
  /* Just unsigned int for BBB */
  PRINTF("char*: %u bytes\n", sizeof(char*));
  PRINTF("short*: %u bytes\n", sizeof(short*));
  PRINTF("int*: %u bytes\n", sizeof(int*));
  PRINTF("long*: %u bytes\n", sizeof(long*));
  PRINTF("double*: %u bytes\n", sizeof(double*));
  PRINTF("float*: %u bytes\n", sizeof(float*));
  PRINTF("void*: %u bytes\n", sizeof(void*));
  PRINTF("int8_t*: %u bytes\n", sizeof(int8_t*));
  PRINTF("int16_t*: %u bytes\n", sizeof(int16_t*));
  PRINTF("int32_t*: %u bytes\n", sizeof(int32_t*));
  PRINTF("char**: %u bytes\n", sizeof(char**));
  PRINTF("int**: %u bytes\n", sizeof(int**));
  PRINTF("void**: %u bytes\n", sizeof(void**));
#endif
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
