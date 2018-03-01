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
 * @file test.h
 * @brief CMOCKA unit testing entry point
 * 
 * For unit testing: intercept calls to malloc(), free(), realloc(),
 * and calloc() with CMOCKA methods that detect memory leaks, etc.
 *
 * @author Matthew Haney
 * @date 2018-03-01
 */

#ifndef __TEST_H__
#define __TEST_H__

extern void* _test_malloc(const size_t size, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)

extern void* _test_realloc(void * ptr, const size_t size, const char* file, const int line);
#define realloc(ptr, size) _test_realloc(ptr, size, __FILE__, __LINE__)

extern void* _test_calloc(const size_t nmemb, const size_t size, const char* file, const int line);
#define calloc(nmemb, size) _test_calloc(nmemb, size, __FILE__, __LINE__)

extern void _test_free(void * const ptr, const char* file, const int line);
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)

#endif /* __TEST_H__ */
