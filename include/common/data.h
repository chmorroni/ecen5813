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
 * @file data.h
 * @brief Functions for printing the sizes of variable types
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __DATA_H__
#define __DATA_H__

#define LITTLE_ENDIAN (0)
#define BIG_ENDIAN    (1)
#define SWAP_NO_ERROR (0)
#define SWAP_ERROR    (1)

/**
 * @brief Prints the sizes of each C standard type
 *
 * For each of the C standard types, gets its size and prints the type name and size.
 *
 * @return void
 */
void print_cstd_type_sizes();

/**
 * @brief Prints the sizes of each standard integer type
 *
 * For each of the standard integer types, gets its size and prints the type name and size.
 *
 * @return void
 */
void print_stdint_type_sizes();

/**
 * @brief Prints the sizes of each pointer
 *
 * For each pointer type, gets its size and prints the type name and size.
 *
 * @return void
 */
void print_pointer_sizes();

/**
 * @brief Reverses data endianness
 *
 * Moves bytes around to switch the endianness of a given array of bytes.
 *
 * @param data Pointer to the array of data
 * @param type_length The length of the data
 *
 * @return Whether the swap was successful
 */
int32_t swap_data_endianness(uint8_t * data, size_t type_length);

/**
 * @brief Determines data endianness of program
 *
 * Determines whether the current endianness for the program is little or big.
 *
 * @return Whether the program is big or little endian.
 */
uint32_t determine_endianness();

#endif /* __DATA_H__ */
