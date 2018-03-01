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
 * @file circbuf_test.c
 * @brief CMOCKA unit tests for circbuf.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>

#include "circbuf.h"
#include "circbuf_test.h"

void circbuf_allocate_initialize_free_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);

  assert_non_null(buffer->bmp);
  assert_int_equal(buffer->size, 10);

  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_invalid_input_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(NULL, 10) == CB_NULL_PTR);
  assert_true(CB_init(&buffer, 0) == CB_BAD_LEN);
}

void circbuf_add_remove_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);
  
  __cbdata_t test_data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  uint8_t i;
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_add_item(buffer, test_data[i]) == CB_SUCCESS);
  } /* add */
  __cbdata_t popped_data;
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_remove_item(buffer, &popped_data) == CB_SUCCESS);
    assert_true(popped_data == test_data[i]);
  } /* remove */
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_buffer_full_test(void ** state) {
  (void) state; /* not used */
  
  CB_t * buffer;
  assert_true(CB_init(&buffer, 1) == CB_SUCCESS);
  assert_non_null(buffer);

  assert_int_equal(CB_buffer_add_item(buffer, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(buffer, 1), CB_FULL);
  assert_true(CB_is_full(buffer));
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_buffer_empty_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);

  assert_true(CB_is_empty(buffer));
  assert_int_equal(CB_buffer_remove_item(buffer, 0), CB_EMPTY);
    
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_wrap_add_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);

  __cbdata_t test_data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  uint8_t i;
  /* First: fill buffer */
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_add_item(buffer, test_data[i]) == CB_SUCCESS);
  }
  /* Then: remove 2 items */
  __cbdata_t popped_data;
  for (i = 0; i < 2; i++) {
    assert_true(CB_buffer_remove_item(buffer, &popped_data) == CB_SUCCESS);
    assert_true(popped_data == test_data[i]);
  }
  /* Then: add 2 items */
  assert_true(CB_buffer_add_item(buffer, 16) == CB_SUCCESS);
  assert_true(CB_buffer_add_item(buffer, 17) == CB_SUCCESS);
  /* Then: check that data is correct */
  assert_true(CB_peek(buffer, -1, &popped_data) == CB_SUCCESS);
  assert_int_equal(popped_data, 17);
  assert_true(CB_peek(buffer, -2, &popped_data) == CB_SUCCESS);
  assert_int_equal(popped_data, 16);
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_wrap_remove_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);

  fail();
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_overfill_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);

  fail();
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_over_empty_test(void ** state) {
  (void) state; /* not used */
  
  CB_t * buffer;
  assert_true(CB_init(&buffer, 10) == CB_SUCCESS);
  assert_non_null(buffer);

  fail();
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}
