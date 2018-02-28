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

/* Project 1 constants for determining system endianness */
#define __SCB_ADDRESS (0xE000ED00)
#define __AIRCR_ADDRESS_OFFEST (0x0C)
#define __AIRCR (*((uint32_t *)(__SCB_ADDRESS + __AIRCR_ADDRESS_OFFSET)))
#define __AIRCR_ENDIANNESS_OFFSET (15)
#define __AIRCR_ENDIANNESS_MASK (0x1 << 15)

/* Project 2 constants for reading and writing processor configuration registers */
#define __SCB_ADDRESS (0)
#define __CPUID_ADDRESS_OFFSET (0) #define __CPUID (0)
#define __CPUID_PART_NO_OFFSET (0)
#define __CPUID_PART_NO_MASK (0)
#define __CCR_ADDRESS_OFFSET (0)
#define __CCR (0)
#define __CCR_STK_ALIGNMENT_OFFSET (0)
#define __CCR_STK_ALIGNMENT_MASK (0)
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET (0)
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK (0)
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET (0)
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK (0)

/**
 * @brief Get the endianness configuration of an ARM processor
 *
 * Checks the AIRCR register to determine endianness.
 *
 * @return The endianness of the ARM processer
 */
__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting();

/**
 * @brief Read stack alignment setting
 * 
 * Accesses the appropriate bits of the ARM CCR register
 * 
 * @return 0 if 4-byte (word) aligned, 1 if 8-byte (double word) aligned
 */
__attribute__((always_inline)) uint32_t ARM32_CCR_get_stack_alignment();

/**
 * @brief Read CPU part number
 * 
 * Read contents of CPUID register
 * 
 * @return Part number value - expect 0xC24 for KL25Z
 */
__attribute__((always_inline)) uint32_t ARM32_CPUID_get_part_number();

/**
 * @brief Enables divide-by-zero traps
 *
 * Write to DIV_0_TRAP bit in CCR
 *
 * @return ???
 */
__attribute__((always_inline)) uint32_t ARM32_CCR_enable_divide_by_zero_trap();

/**
 * @brief Enables unaligned access traps
 *
 * Write to UNALIGN_TRAP bit in CCR
 *
 * @return ???
 */
__attribute__((always_inline)) uint32_t ARM32_CCR_enable_unaligned_access_trap();

/**
 * @brief Triggers an unaligned access trap by running bad code
 */
void ARM32_create_unaligned_access_trap();

/**
 * @brief Triggers a divide by zero trap by running bad code
 */
void ARM32_create_divide_by_zero_trap();

#endif /* __ARCH_ARM32_H__ */
