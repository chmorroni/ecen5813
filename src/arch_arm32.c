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

#include <stdint.h>
#include "arch_arm32.h"

__attribute__((always_inline)) inline uint32_t ARM32_AIRCR_get_endianness_setting()
{
  return ( (__AIRCR & __AIRCR_ENDIANNESS_MASK) >> __AIRCR_ENDIANNESS_OFFSET );
}

__attribute__((always_inline)) inline uint32_t ARM32_CCR_get_stack_alignment()
{
  return ( (__CCR & __CCR_STK_ALIGNMENT_MASK) >> __CCR_STK_ALIGNMENT_OFFSET );
}

__attribute__((always_inline)) inline uint32_t ARM32_CPUID_get_part_number()
{
  return ( (__CPUID & __CPUID_PART_NO_MASK) >> __CPUID_PART_NO_OFFSET );
}

__attribute__((always_inline)) inline void ARM32_CCR_enable_divide_by_zero_trap()
{
  __CCR |= __CCR_DIVIDE_BY_ZERO_TRAP_MASK;
}

__attribute__((always_inline)) inline void ARM32_CCR_enable_unaligned_access_trap()
{
  __CCR |= __CCR_UNALIGNED_ACCESS_TRAP_MASK;
}

void ARM32_create_unaligned_access_trap()
{
  uint32_t dummy_variable = 0;
  void * dangerous_pointer = (void*)&dummy_variable;
  dangerous_pointer = (void*)( (uint32_t)(dangerous_pointer) + 1 );
  dummy_variable = *((uint32_t*)dangerous_pointer); /* trap should occur here */
}

void ARM32_create_divide_by_zero_trap()
{
  uint32_t dummy_variable = 32;
  uint32_t other_dummy_variable = 0;
  dummy_variable /= other_dummy_variable; /* trap should occur here */
}
