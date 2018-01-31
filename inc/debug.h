/**
 * @file debug.h
 * @brief Functions for debug printing
 *
 * This header file contains the prototypes for functions to print while debugging.
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

/**
 * @brief Prints a given array
 *
 * Prints the array to a location specified by the architecture.
 *
 * @param start Pointer to the first byte in array
 * @param length The length of the array
 *
 * @return void
 */
void print_array(uint8_t * start, uint32_t length);

#endif /* __DEBUG_H__ */
