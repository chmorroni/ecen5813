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
 * @file profile.h 
 * @brief This file is to be used for profiling memory operations.
 *
 * @author Christopher Morroni
 * @date 2018-04-08
 *
 */
#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <stdint.h>

#ifndef PLATFORM_KL25Z
#include <time.h>
#endif /* !PLATFORM_KL25Z */

#define PROFILE_SIZE_ARR {10, 100, 1000, 5000}
#define PROFILE_SIZE_ARR_LEN (4)
#define PROFILE_NUM_REPS (10)

/**
 * @brief initialize for the profiling functions
 *
 * Sets up SysTick and DMA for profiling
 *
 * @return none
 */
void profile_init();

/**
 * @brief profile the standard library memmove and memset functions
 *
 * Uses SysTick and time.h to profile memmove and memset from the standard library
 * Runs the test multiple times and calculates the average run time
 *
 * @param ptr_move_avg A pointer to the location to store the average time for memmove
 * @param ptr_set_avg A pointer to the location to store the average time for memset
 * @param src The location of the source memory block for memove nd memset
 * @param dst The location of the destination memory block for memmove
 * @param block_size The size of the src and dst blocks in bytes
 *
 * @return none
 */
#ifdef PLATFORM_KL25Z
void profile_std_lib(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#else
void profile_std_lib(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#endif

/**
 * @brief profile the memory library memmove and memset functions
 *
 * Uses SysTick and time.h to profile memmove and memset from the memory library
 * Runs the test multiple times and calculates the average run time
 *
 * @param ptr_move_avg A pointer to the location to store the average time for memmove
 * @param ptr_set_avg A pointer to the location to store the average time for memset
 * @param src The location of the source memory block for memove nd memset
 * @param dst The location of the destination memory block for memmove
 * @param block_size The size of the src and dst blocks in bytes
 *
 * @return none
 */
#ifdef PLATFORM_KL25Z
void profile_mem_lib(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#else
void profile_mem_lib(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#endif

/**
 * @brief profile the optimized memory library memmove and memset functions
 *
 * Uses SysTick and time.h to profile memmove and memset from the optimized memory library
 * Runs the test multiple times and calculates the average run time
 *
 * @param ptr_move_avg A pointer to the location to store the average time for memmove
 * @param ptr_set_avg A pointer to the location to store the average time for memset
 * @param src The location of the source memory block for memove nd memset
 * @param dst The location of the destination memory block for memmove
 * @param block_size The size of the src and dst blocks in bytes
 *
 * @return none
 */
#ifdef PLATFORM_KL25Z
void profile_opt_mem_lib(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#else
void profile_opt_mem_lib(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#endif

/**
 * @brief profile the DMA memmove and memset functions
 *
 * Uses SysTick and time.h to profile DMA memmove and memset
 * Runs the test multiple times and calculates the average run time
 * Uses global variables and requires the DMA ISR set the variables when done
 *
 * @param ptr_move_avg A pointer to the location to store the average time for memmove
 * @param ptr_set_avg A pointer to the location to store the average time for memset
 * @param src The location of the source memory block for memove nd memset
 * @param dst The location of the destination memory block for memmove
 * @param block_size The size of the src and dst blocks in bytes
 *
 * @return none
 */
#ifdef PLATFORM_KL25Z
void profile_dma(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size);
#endif

#endif /* __PROFILE_H__ */
