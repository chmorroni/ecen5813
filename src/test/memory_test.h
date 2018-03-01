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
 * @file memory_test.h
 * @brief CMOCKA unit tests for memory.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#ifndef __MEMORY_TEST_H__
#define __MEMORY_TEST_H__

/**
 * @brief memmove should return fail if pointers are NULL
 */
void memmove_invalid_pointers_test(void ** state);

/**
 * @brief memmove should pass when moving without overlap
 */
void memmove_no_overlap_test(void ** state);

/**
 * @brief memmove should pass when SRC overlaps DST
 */
void memmove_src_overlap_dst_test(void ** state);

/**
 * @brief memmove should pass when DST overlaps SRC
 */
void memmove_dst_overlap_src_test(void ** state);

/**
 * @brief memmove should pass when DST == SRC
 */
void memmove_same_src_dst_test(void ** state);

/**
 * @brief memset should fail if passed NULL pointers
 */
void memset_invalid_pointers_test(void ** state);

/**
 * @brief memset should accurately set region for length value
 */
void memset_check_set_test(void ** state);

/**
 * @brief memzero should fail if passed NULL pointers
 */
void memzero_invalid_pointers_test(void ** state);

/**
 * @brief memzero should accurately set region to zeros
 */
void memzero_check_set_test(void ** state);

/**
 * @brief reverse should fail if passed NULL pointers
 */
void reverse_invalid_pointers_test(void ** state);

/**
 * @brief reverse should succeeded for even length
 */
void reverse_check_even_test(void ** state);

/**
 * @brief reverse should succeeded for odd length
 */
void reverse_check_odd_test(void ** state);

/**
 * @brief reverse should be able to reverse any ASCII character array
 * 
 * Uses 256 byte array of 0-255
 */
void reverse_check_charset_test(void ** state);

#endif /* __MEMORY_TEST_H__ */
