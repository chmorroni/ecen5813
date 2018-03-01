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
 * @file conversion_test.c
 * @brief CMOCKA unit tests for conversion.c
 * 
 * Liberties were taken with implementing these tests from the
 * project requirements - "zero integer" and "max sized integer"
 * were not clear, and these tests feel much more complete.
 *
 * @author Matthew Haney
 * @date 2018-03-01
 */

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "conversion.h"
#include "conversion_test.h"

void itoa_invalid_input_test(void ** state) {
  (void) state; /* not used */

  /* Passing NULL */
  assert_true(my_itoa(-10, NULL, 10) == 0);
  
  /* Passing invalid base */
  uint8_t conversion_buf[25];
  assert_true(my_itoa(-10, conversion_buf, 40) == 0);
}

void itoa_negative_test(void ** state) {
  (void) state; /* not used */
  
  /* A couple different negative numbers to different bases */
  uint8_t conversion_buf[25];
  assert_true(my_itoa(-10, conversion_buf, 10) == 4);
  assert_string_equal(conversion_buf, "-10");
  assert_true(my_itoa(-255, conversion_buf, 16) == 4);
  assert_string_equal(conversion_buf, "-FF");
  assert_true(my_itoa(-7, conversion_buf, 2) == 5);
  assert_string_equal(conversion_buf, "-111");
  assert_true(my_itoa(-11, conversion_buf, 8) == 4);
  assert_string_equal(conversion_buf, "-13");
}

void itoa_positive_test(void ** state) {
  (void) state; /* not used */

  /* A couple different numbers to different bases */
  uint8_t conversion_buf[25];
  assert_true(my_itoa(4, conversion_buf, 10) == 2);
  assert_string_equal(conversion_buf, "4");
  assert_true(my_itoa(1748, conversion_buf, 14) == 4);
  assert_string_equal(conversion_buf, "8CC");
  assert_true(my_itoa(7, conversion_buf, 6) == 3);
  assert_string_equal(conversion_buf, "11");
  assert_true(my_itoa(32857, conversion_buf, 2) == 17);
  assert_string_equal(conversion_buf, "1000000001011001");
}

void atoi_invalid_input_test(void ** state) {
  (void) state; /* not used */

  /* Passing NULL */
  assert_true(my_atoi(NULL, 1, 10) == 0);
  
  /* Passing invalid base */
  assert_true(my_atoi((uint8_t*)"23", 2, 40) == 0);
}

void atoi_negative_test(void ** state) {
  (void) state; /* not used */

  assert_int_equal(my_atoi((uint8_t*)"-2", 2, 10), -2);
  assert_int_equal(my_atoi((uint8_t*)"-9", 2, 10), -9);
  assert_int_equal(my_atoi((uint8_t*)"-14", 3, 9), -13);
  assert_int_equal(my_atoi((uint8_t*)"-253", 4, 13), -406);
}

void atoi_positive_test(void ** state) {
  (void) state; /* not used */
  
  assert_int_equal(my_atoi((uint8_t*)"427", 3, 10), 427);
  assert_int_equal(my_atoi((uint8_t*)"DEADBEE", 7, 16), 0xdeadbee);
  assert_int_equal(my_atoi((uint8_t*)"12", 2, 6), 8);
  assert_int_equal(my_atoi((uint8_t*)"14", 2, 10), 0xe);
}

void atoi_zero_zero_test(void ** state) {
  (void) state; /* not used */

  /* Pass in zero digits to convert */
  assert_int_equal(my_atoi((uint8_t*)"1353588", 0, 9), 0);
}

void atoi_large_number_string_test(void ** state) {
  (void) state; /* not used */

  assert_int_not_equal(my_atoi((uint8_t*)"ffffffff", 8, 16), 0xffffffff);
  assert_int_not_equal(my_atoi((uint8_t*)"-ffffffff", 9, 16), -0xffffffff);
}
