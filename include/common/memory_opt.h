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
 * @file memory_opt.h
 * @brief Optimized versions of selected memory operations from memory.h
 *
 * This header file contains the prototypes for functions to manipulate memory.
 *
 * @author Christopher Morroni
 * @date 2018-04-08
 */
#ifndef __MEMORY_OPT_H__
#define __MEMORY_OPT_H__

#include <stdint.h>

/**
 * @brief Copys a block of memory
 *
 * Given a pointer to each source and destination and their size,
 * this function copies the data from the source to the destination.
 * Guaranties no data corruption when source and destination overlap.
 *
 * @param src Pointer to the source data
 * @param dst Pointer to the destination data
 * @param length The length of the memory block to copy
 *
 * @return A pointer to the destination memory
 */
uint8_t * __attribute__((optimize("O3"))) my_memmove_opt(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Copys a block of memory
 *
 * Given a pointer to each source and destination and their size,
 * this function copies the data from the source to the destination.
 *
 * @param src Pointer to the source data
 * @param dst Pointer to the destination data
 * @param length The length of the memory block to copy
 *
 * @return A pointer to the destination memory
 */
uint8_t * __attribute__((optimize("O3"))) my_memcpy_opt(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Sets all bytes in a block of data to a given value
 *
 * Given a pointer to a source memory location and its size,
 * sets each byte in the block to the given value.
 *
 * @param src Pointer to the source block
 * @param length The length of the source block
 * @param value The byte that will be copied to each byte of the source block
 *
 * @return A pointer to the source memory block
 */
uint8_t * __attribute__((optimize("O3"))) my_memset_opt(uint8_t * src, size_t length, uint8_t value);

#endif /* __MEMORY_OPT_H__ */
