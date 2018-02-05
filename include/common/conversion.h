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
 * @file conversion.h
 * @brief Functions for basic data manipulations
 *
 * This header file contains the prototypes for functions to manipulate data.
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

/**
 * @brief Converts integers to ASCII strings
 *
 * Converts an integer of a given base to an ASCII string,
 * and stores the string at a given address.
 *
 * @param data The integer to convert
 * @param ptr Pointer to the location for the string
 * @param base The base of the given integer
 *
 * @return The length of the ASCII string
 */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

/**
 * @brief Converts ASCII strings to integers
 *
 * Converts an ASCII string of a given length and base to an integer.
 *
 * @param ptr Pointer to the ASCII string
 * @param digits The length ot the string
 * @param base The base of the given string
 *
 * @return The converted integer
 */
uint32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

#endif /* __CONVERSIONS_H__ */
