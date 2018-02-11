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
 * @file arch_arm32.h
 * @brief Functions for ARM-specific functionality
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __ARCH_ARM32_H__
#define __ARCH_ARM32_H__

#define __SCB_ADDRESS (0xE000ED00)
#define __AIRCR_ADDRESS_OFFEST (0x0C)
#define __AIRCR (*((uint32_t *)(__SCB_ADDRESS + __AIRCR_ADDRESS_OFFSET)))
#define __AIRCR_ENDIANNESS_OFFSET (15)
#define __AIRCR_ENDIANNESS_MASK (0x1 << 15)

/**
 * @brief Get the endianness configuration of an ARM processor
 *
 * Checks the AIRCR register to determine endianness.
 *
 * @return The endianness of the ARM processer
 */
__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting();

#endif /* __ARCH_ARM32_H__ */
