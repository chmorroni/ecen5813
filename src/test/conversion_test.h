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
 * @file conversion_test.h
 * @brief CMOCKA unit tests for conversion.c
 * 
 * @author Matthew Haney
 * @date 2018-03-01
 */

#ifndef __CONVERSION_TEST_H__
#define __CONVERSION_TEST_H__

/**
 * @brief itoa should fail if passed NULL pointer or an invalid base
 */
void itoa_invalid_input_test(void ** state);

/**
 * @brief itoa works on negative numbers
 */
void itoa_negative_test(void ** state);

/**
 * @brief itoa works on positive numbers
 */
void itoa_positive_test(void ** state);

/**
 * @brief atoi should fail if passed NULL pointer or an invalid base
 */
void atoi_invalid_input_test(void ** state);

/**
 * @brief atoi works on negative numbers
 */
void atoi_negative_test(void ** state);

/**
 * @brief atoi gracefully returns 0 if asked to convert 0 digits
 */
void atoi_zero_zero_test(void ** state);

/**
 * @brief atoi behavior when converting large number
 * 
 * If atoi is passed a string whose integer value would exceed
 * +/- 2^31, atoi has undefined behavior. What should we expect?
 */
void atoi_large_number_string_test(void ** state);


#endif /* __CONVERSION_TEST_H__ */
