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
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  assert_non_null(buffer->bmp);
  assert_int_equal(buffer->size, 10);

  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_invalid_input_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(NULL, 10, sizeof(uint8_t)) == CB_NULL_PTR);
  assert_true(CB_init(&buffer, 0, sizeof(uint8_t)) == CB_BAD_LEN);
}

void circbuf_add_remove_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);
  
  uint8_t test_data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  uint8_t i;
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_add_item(buffer, (void *)&test_data[i]) == CB_SUCCESS);
  } /* add */
  uint8_t popped_data;
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_remove_item(buffer, (void *)&popped_data) == CB_SUCCESS);
    assert_true(popped_data == test_data[i]);
  } /* remove */
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_buffer_full_test(void ** state) {
  (void) state; /* not used */
  
  CB_t * buffer;
  assert_true(CB_init(&buffer, 1, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  uint8_t temp = 0;
  assert_int_equal(CB_buffer_add_item(buffer, (void *)&temp), CB_SUCCESS);
  temp = 1;
  assert_int_equal(CB_buffer_add_item(buffer, (void *)&temp), CB_FULL);
  assert_true(CB_is_full(buffer));
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_buffer_empty_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  assert_true(CB_is_empty(buffer));
  assert_int_equal(CB_buffer_remove_item(buffer, 0), CB_EMPTY);
    
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_wrap_add_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  uint8_t test_data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  uint8_t final_data[10] = {16, 17, 7, 6, 5, 4, 3, 2, 1, 0};
  uint8_t i;
  /* First: fill buffer */
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_add_item(buffer, (void *)&test_data[i]) == CB_SUCCESS);
  }
  assert_true(CB_is_full(buffer));
  /* Then: remove 2 items */
  uint8_t popped_data;
  for (i = 0; i < 2; i++) {
    assert_true(CB_buffer_remove_item(buffer, (void *)&popped_data) == CB_SUCCESS);
    assert_true(popped_data == test_data[i]);
  }
  assert_false(CB_is_full(buffer));
  /* Then: add 2 items */
  uint8_t temp = 16;
  assert_true(CB_buffer_add_item(buffer, (void *)&temp) == CB_SUCCESS);
  temp = 17;
  assert_true(CB_buffer_add_item(buffer, (void *)&temp) == CB_SUCCESS);
  assert_true(CB_is_full(buffer));
  
  assert_memory_equal(buffer->bmp, &final_data, 10);
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_wrap_remove_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  /* First: save time by artificially populating buffer */
  uint8_t test_data[10] = {2, 3, 4, 0, 0, 0, 0, 0, 0, 1};
  /*                       ^     ^                    ^   */
  /*                      bmp   head                 tail */
  uint8_t i;
  for (i = 0; i < 10; i++) {
    *(uint8_t *)(buffer->bmp + i) = test_data[i];
  }
  buffer->head = buffer->bmp + 2;
  buffer->tail = buffer->bmp + 9;
  buffer->count = 4;
  
  /* Then: remove 3 items */
  uint8_t popped_data;
  
  assert_true(CB_buffer_remove_item(buffer, (void *)&popped_data) == CB_SUCCESS);
  assert_true(popped_data == 1);
  assert_true(CB_buffer_remove_item(buffer, (void *)&popped_data) == CB_SUCCESS);
  assert_true(popped_data == 2);
  assert_true(CB_buffer_remove_item(buffer, (void *)&popped_data) == CB_SUCCESS);
  assert_true(popped_data == 3);
    
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_overfill_test(void ** state) {
  (void) state; /* not used */

  CB_t * buffer;
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  uint8_t test_data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  uint8_t i;
  /* First: fill buffer */
  for (i = 0; i < 10; i++) {
    assert_true(CB_buffer_add_item(buffer, (void *)&test_data[i]) == CB_SUCCESS);
  }
  assert_true(CB_is_full(buffer));
  
  uint8_t data = 42;
  assert_true(CB_buffer_add_item(buffer, (void *)&data) == CB_FULL);
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}

void circbuf_over_empty_test(void ** state) {
  (void) state; /* not used */
  
  CB_t * buffer;
  assert_true(CB_init(&buffer, 10, sizeof(uint8_t)) == CB_SUCCESS);
  assert_non_null(buffer);

  assert_true(CB_is_empty(buffer));
  uint8_t popped_data;
  assert_true(CB_buffer_remove_item(buffer, (void *)&popped_data) == CB_EMPTY);
  
  assert_true(CB_destroy(&buffer) == CB_SUCCESS);
  assert_null(buffer);
}
