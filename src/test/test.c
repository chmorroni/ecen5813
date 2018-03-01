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
 * @file test.c
 * @brief CMOCKA unit testing entry point
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test.h"
#include "memory_test.h"
#include "data_test.h"
#include "conversion_test.h"
#include "circbuf_test.h"

int main(void) {
  /* Circular buffer tests */
  const struct CMUnitTest circbuf_tests[] = {
    cmocka_unit_test(circbuf_allocate_free_test),
    cmocka_unit_test(circbuf_invalid_pointer_test),
    cmocka_unit_test(circbuf_buffer_initialize_test),
    cmocka_unit_test(circbuf_add_remove_test),
    cmocka_unit_test(circbuf_buffer_full_test),
    cmocka_unit_test(circbuf_buffer_empty_test),
    cmocka_unit_test(circbuf_wrap_add_test),
    cmocka_unit_test(circbuf_wrap_remove_test),
    cmocka_unit_test(circbuf_overfill_test),
    cmocka_unit_test(circbuf_over_empty_test)
  };

  /* Memory tests */
  const struct CMUnitTest memory_tests[] = {
    cmocka_unit_test(memmove_invalid_pointers_test),
    cmocka_unit_test(memmove_no_overlap_test),
    cmocka_unit_test(memmove_src_overlap_dst_test),
    cmocka_unit_test(memmove_dst_overlap_src_test),
    cmocka_unit_test(memmove_same_src_dst_test),
    cmocka_unit_test(memset_invalid_pointers_test),
    cmocka_unit_test(memset_check_set_test),
    cmocka_unit_test(memzero_invalid_pointers_test),
    cmocka_unit_test(memzero_check_set_test),
    cmocka_unit_test(reverse_invalid_pointers_test),
    cmocka_unit_test(reverse_check_even_test),
    cmocka_unit_test(reverse_check_odd_test),
    cmocka_unit_test(reverse_check_charset_test)
  };

  /* Data tests */
  const struct CMUnitTest data_tests[] = {
    cmocka_unit_test(data_endianness_invalid_pointers_test),
    cmocka_unit_test(data_endianness_conversion_valid_test)
  };

  /* Conversion tests */
  const struct CMUnitTest conversion_tests[] = {
    cmocka_unit_test(itoa_invalid_input_test),
    cmocka_unit_test(itoa_negative_test),
    cmocka_unit_test(itoa_positive_test),
    cmocka_unit_test(atoi_invalid_input_test),
    cmocka_unit_test(atoi_negative_test),
    cmocka_unit_test(atoi_positive_test),
    cmocka_unit_test(atoi_zero_zero_test),
    cmocka_unit_test(atoi_large_number_string_test)
  };
  
  /* Run tests */
  /* Not really bothering with states, so just pass NULL for start and end */
  int circbuf_result = cmocka_run_group_tests(circbuf_tests, NULL, NULL);
  int memory_result = cmocka_run_group_tests(memory_tests, NULL, NULL);
  int data_result = cmocka_run_group_tests(data_tests, NULL, NULL);
  int conversion_result = cmocka_run_group_tests(conversion_tests, NULL, NULL);
  
  /* Pass failures (if any) to shell */
  return circbuf_result | memory_result | data_result | conversion_result;
}
