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
 * @file arch_arm32.c
 * @brief Functions for ARM-specific functionality
 *
 * @author Christopher Morroni
 * @date 02/11/2018
 */

#include "arch_arm32.h"

__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting()
{
  return ( (__AIRCR & __AIRCR_ENDIANNESS_MASK) >> __AIRCR_ENDIANNESS_OFFEST );
}

__attribute__((always_inline)) uint32_t ARM32_CCR_get_stack_alignment() {
  return 0;
}

__attribute__((always_inline)) uint32_t ARM32_CPUID_get_part_number() {
  return 0;
}

__attribute__((always_inline)) uint32_t ARM32_CCR_enable_divide_by_zero_trap() {
  return 0; /* should we return anything from this? */
}

__attribute__((always_inline)) uint32_t ARM32_CCR_enable_unaligned_access_trap() {
  return 0; /* should we return anything from this? */
}

void ARM32_create_unaligned_access_trap() {
  /* */
}

void ARM32_create_divide_by_zero_trap() {
  /* */
}
