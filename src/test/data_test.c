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
 * @file data_test.c
 * @brief CMOCKA unit tests for data.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "data.h"
#include "data_test.h"

void data_endianness_invalid_pointers_test(void ** state) {
  (void) state; /* not used */

  assert_true(swap_data_endianness(NULL, 2) == SWAP_ERROR);
}

void data_endianness_conversion_valid_test(void ** state) {
  (void) state; /* not used */

  uint32_t data = 0xdeadbeef;
  assert_true(swap_data_endianness((uint8_t*)&data, sizeof(data)) == SWAP_NO_ERROR);
  assert_true(data == 0xefbeadde);
  assert_true(swap_data_endianness((uint8_t*)&data, sizeof(data)) == SWAP_NO_ERROR);
  assert_true(data == 0xdeadbeef);
}
