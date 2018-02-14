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
 * @file platform.h
 * @brief Definitions to control platform-specific features
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if defined(PLATFORM_KL25Z)
/* Disable use of printf in KL25Z target executable */
void __no_printf();
#define PRINTF(X, ...) __no_printf()
#define START_CRITICAL __disable_irq()
#define END_CRITICAL __enable_irq()

#elif defined(PLATFORM_BBB)
/* Enable use of printf in BeagleBone target executable */
#include <stdio.h>
#define PRINTF printf
#define START_CRITICAL
#define END_CRITICAL

#elif defined(PLATFORM_HOST)
/* Enable use of printf in host target executable */
#include <stdio.h>
#define PRINTF printf
#define START_CRITICAL
#define END_CRITICAL

#else
#error "Please define a PLATFORM variable using the -D option."

#endif /* PLATFORM variable checks */

#endif /* __PLATFORM_H__ */
