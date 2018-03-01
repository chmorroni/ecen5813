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
 * @file data_test.h
 * @brief CMOCKA unit tests for data.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#ifndef __DATA_TEST_H__
#define __DATA_TEST_H__

/**
 * @brief endianness conversion functions should fail if passed NULL pointers
 */
void data_endianness_invalid_pointers_test(void ** state);

/**
 * @brief Test that endianness conversion works
 *
 * Test big-to-little gives expected result
 * Test little-to-big gives expected result
 * Test big-to-little followed by little-to-big preserves original
 */
void data_endianness_conversion_valid_test(void ** state);

#endif /* __DATA_TEST_H__ */
