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
 * @file memory_test.c
 * @brief CMOCKA unit tests for memory.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include "memory.h"
#include "memory_test.h"

void memmove_invalid_pointers_test(void ** state) {
  (void) state; /* not used */
  uint8_t data = 12;
  uint8_t * ptr = &data;
  assert_null(my_memmove(NULL, ptr, 2));
  assert_null(my_memmove(ptr, NULL, 2));
}

void memmove_no_overlap_test(void ** state) {
  (void) state; /* not used */
  
  uint8_t * orig_set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t * set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t i;
  for (i = 0; i < 16; i++) {
    orig_set[i] = i;
    set[i] = i;
  }
  uint8_t * ptr1 = &set[0];
  uint8_t * ptr2 = &set[8];
  assert_memory_equal(ptr1, orig_set, 8);
  assert_memory_equal(ptr2, orig_set + 8 * sizeof(uint8_t), 8);
  my_memmove(ptr1, ptr2, 8);
  assert_memory_equal(ptr1, orig_set, 8);
  assert_memory_equal(ptr2, orig_set, 8);
  free(set);
  free(orig_set);
}

void memmove_src_overlap_dst_test(void ** state) {
  (void) state; /* not used */

  uint8_t * orig_set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t * set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t i;
  for (i = 0; i < 16; i++) {
    orig_set[i] = i;
    set[i] = i;
  }
  uint8_t * ptr1 = &set[0];
  uint8_t * ptr2 = &set[4];
  assert_memory_equal(ptr1, orig_set, 8);
  assert_memory_equal(ptr2, orig_set + 4 * sizeof(uint8_t), 8);
  my_memmove(ptr1, ptr2, 8);
  assert_memory_equal(ptr1, orig_set, 4);
  assert_memory_equal(ptr1 + 4 * sizeof(uint8_t), orig_set, 4);
  assert_memory_equal(ptr2, orig_set, 8);
  free(set);
  free(orig_set);
}

void memmove_dst_overlap_src_test(void ** state) {
  (void) state; /* not used */

  uint8_t * orig_set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t * set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t i;
  for (i = 0; i < 16; i++) {
    orig_set[i] = i;
    set[i] = i;
  }
  uint8_t * ptr1 = &set[0];
  uint8_t * ptr2 = &set[4];
  assert_memory_equal(ptr1, orig_set, 8);
  assert_memory_equal(ptr2, orig_set + 4 * sizeof(uint8_t), 8);
  my_memmove(ptr2, ptr1, 8);
  assert_memory_equal(ptr1, orig_set + 4 * sizeof(uint8_t), 8);
  assert_memory_equal(ptr2, orig_set + 8 * sizeof(uint8_t), 4);
  assert_memory_equal(ptr2 + 4 * sizeof(uint8_t), orig_set + 8 * sizeof(uint8_t), 4);
  free(set);
  free(orig_set);
}

void memmove_same_src_dst_test(void ** state) {
  (void) state; /* not used */

  uint8_t * orig_set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t * set = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t i;
  for (i = 0; i < 16; i++) {
    orig_set[i] = i;
    set[i] = i;
  }
  uint8_t * ptr1 = &set[0];
  uint8_t * ptr2 = &set[0];
  assert_memory_equal(ptr1, orig_set, 8);
  assert_memory_equal(ptr2, orig_set, 8);
  my_memmove(ptr1, ptr2, 8);
  assert_memory_equal(ptr1, orig_set, 8);
  assert_memory_equal(ptr2, orig_set, 8);
  free(set);
  free(orig_set);
}

void memset_invalid_pointers_test(void ** state) {
  (void) state; /* not used */
  
  assert_null(my_memset(NULL, 8, 8));
}

void memset_check_set_test(void ** state) {
  (void) state; /* not used */
  
  uint8_t * data_region = (uint8_t*)malloc(8 * sizeof(uint8_t));
  uint8_t data_expected_1[8] = {4, 4, 4, 4, 4, 4, 4, 4};
  uint8_t data_expected_2[8] = {6, 6, 4, 4, 4, 4, 4, 4};
  data_region = my_memset(data_region, 8, 4);
  assert_memory_equal(data_region, data_expected_1, 8);
  data_region = my_memset(data_region, 2, 6);
  assert_memory_equal(data_region, data_expected_2, 8);
  free(data_region);
}

void memzero_invalid_pointers_test(void ** state) {
  (void) state; /* not used */

  assert_null(my_memzero(NULL, 8));
}

void memzero_check_set_test(void ** state) {
  (void) state; /* not used */

  uint8_t * data_region = (uint8_t*)malloc(8 * sizeof(uint8_t));
  data_region = my_memset(data_region, 8, 4);
  uint8_t data_expected_1[8] = {0, 0, 0, 0, 4, 4, 4, 4};
  uint8_t data_expected_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  data_region = my_memzero(data_region, 4);
  assert_memory_equal(data_region, data_expected_1, 8);
  data_region = my_memzero(data_region, 8);
  assert_memory_equal(data_region, data_expected_2, 8);
  free(data_region);
}

void reverse_invalid_pointers_test(void ** state) {
  (void) state; /* not used */

  assert_null(my_reverse(NULL, 6));
}

void reverse_check_even_test(void ** state) {
  (void) state; /* not used */

  uint8_t * data_region = (uint8_t*)malloc(16 * sizeof(uint8_t));
  uint8_t i;
  for (i = 0; i < 16; i++) {
    data_region[i] = i;
  }
  uint8_t data_expected[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  data_region = my_reverse(data_region, 16);
  assert_memory_equal(data_region, data_expected, 16);
  free(data_region);
}

void reverse_check_odd_test(void ** state) {
  (void) state; /* not used */
  
  uint8_t * data_region = (uint8_t*)malloc(15 * sizeof(uint8_t));
  uint8_t i;
  for (i = 0; i < 15; i++) {
    data_region[i] = i;
  }
  uint8_t data_expected[15] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  data_region = my_reverse(data_region, 15);
  assert_memory_equal(data_region, data_expected, 15);
  free(data_region);
}

void reverse_check_charset_test(void ** state) {
  (void) state; /* not used */

  uint8_t * data_region = (uint8_t*)malloc(256 * sizeof(uint8_t));
  uint8_t * data_expected = (uint8_t*)malloc(256 * sizeof(uint8_t));
  uint16_t i;
  for (i = 0; i < 256; i++) {
    data_region[i] = i;
    data_expected[i] = 255 - i; 
  }

  data_region = my_reverse(data_region, 256);
  assert_memory_equal(data_region, data_expected, 256);
  
  free(data_region);
  free(data_expected);
}
