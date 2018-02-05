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

#ifndef PLATFORM
#error "Please define a PLATFORM variable using the -D option."
#endif

#if(PLATFORM == KL25Z)
/* Disable use of printf in KL25Z target executable */
/* Also suppress warnings through a clever define */
#define PRINTF (void)

#elif(PLATFORM == BBB)
/* Enable use of printf in BeagleBone target executable */
#define PRINTF printf

#elif(PLATFORM == HOST)
/* Enable use of printf in host target executable */
#define PRINTF printf

#else
#error "Unsupported platform."

#endif

#endif /* __PLATFORM_H__ */
