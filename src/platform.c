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
 * @file platform.c
 * @brief The source file that's more documentation than code
 *
 * This file contains __no_printf, which is used to replace the PRINTF macro
 * on platforms that don't support printf. Using this function allows printf
 * to be sliced out of code without having to insert #pragma declarations
 * everywhere.
 *
 * @author Matthew Haney
 * @date 02/05/2018
 */

/**
 * @brief A dummy function that does nothing and is optimized away by the compiler.
 */
void __no_printf() { return; }
