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
 * @file circbuf_test.h
 * @brief CMOCKA unit tests for circbuf.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#ifndef __CIRCBUF_TEST_H__
#define __CIRCBUF_TEST_H__

/**
 * @brief Checks that a dynamic buffer can be created on the heap
 */
void circbuf_allocate_initialize_free_test(void ** state);

/**
 * @brief CB_init should die with bad input
 */
void circbuf_invalid_input_test(void ** state);

/**
 * @brief Check that add and then a remove returns the same item for full length of buffer
 */
void circbuf_add_remove_test(void ** state);

/**
 * @brief Check buffer reports true for full
 */
void circbuf_buffer_full_test(void ** state);

/**
 * @brief Check buffer reports true for empty
 */
void circbuf_buffer_empty_test(void ** state);

/**
 * @brief Test that your buffer can wrap around the edge boundary and add to the front
 */
void circbuf_wrap_add_test(void ** state);

/**
 * @brief Test that your buffer tail point can wrap around the edge boundary when a remove occurs at the boundary
 */
void circbuf_wrap_remove_test(void ** state);

/**
 * @brief Test that your buffer fails when too many items are added
 */
void circbuf_overfill_test(void ** state);

/**
 * @brief Test that your buffer fails to remove an item when empty
 */
void circbuf_over_empty_test(void ** state);

#endif /* __CIRCBUF_TEST_H__ */
