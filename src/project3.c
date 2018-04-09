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
 * @file project3.c 
 * @brief This file is to be used for project 3.
 *
 * @author Christopher Morroni
 * @date 2018-04-07
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "platform.h"
#include "profile.h"
#include "project3.h"

#ifdef PLATFORM_KL25Z
#include "dma.h"
#endif /* PLATFORM_KL25Z */

void project3()
{

#ifdef PLATFORM_KL25Z
  watermark_stack();
#endif /* PLATFORM_KL25Z */

#ifdef PROFILE
  uint16_t profile_size_arr[] = PROFILE_SIZE_ARR;
  uint8_t *src, *dst;

  profile_init();

#ifdef PLATFORM_KL25Z
  uint32_t std_lib_move_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t std_lib_set_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t mem_lib_move_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t mem_lib_set_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t opt_mem_lib_move_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t opt_mem_lib_set_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t dma_move_avg[PROFILE_SIZE_ARR_LEN];
  uint32_t dma_set_avg[PROFILE_SIZE_ARR_LEN];
#else
  clock_t std_lib_move_avg[PROFILE_SIZE_ARR_LEN];
  clock_t std_lib_set_avg[PROFILE_SIZE_ARR_LEN];
  clock_t mem_lib_move_avg[PROFILE_SIZE_ARR_LEN];
  clock_t mem_lib_set_avg[PROFILE_SIZE_ARR_LEN];
  clock_t opt_mem_lib_move_avg[PROFILE_SIZE_ARR_LEN];
  clock_t opt_mem_lib_set_avg[PROFILE_SIZE_ARR_LEN];
#endif /* PLATFORM_KL25Z */

  uint8_t i;
  for(i = 0; i < PROFILE_SIZE_ARR_LEN; i++)
  {
    /* overlap src and dst, so we don't need 10000+ bytes on the heap */
    dst = malloc(profile_size_arr[i] + 10);
    src = dst + 10;

    /* standard library */
    profile_std_lib(&std_lib_move_avg[i], &std_lib_set_avg[i], src, dst, profile_size_arr[i]);

    /* memory library */
    profile_mem_lib(&mem_lib_move_avg[i], &mem_lib_set_avg[i], src, dst, profile_size_arr[i]);

    /* optimized memory library */
    profile_opt_mem_lib(&opt_mem_lib_move_avg[i], &opt_mem_lib_set_avg[i], src, dst, profile_size_arr[i]);

#ifdef PLATFORM_KL25Z
    /* DMA */
    profile_dma(&dma_move_avg[i], &dma_set_avg[i], src, dst, profile_size_arr[i]);
#endif /* PLATFORM_KL25Z */

    free(dst);
  }

#ifdef PLATFORM_KL25Z
#else
  for(i = 0; i < PROFILE_SIZE_ARR_LEN; i++)
  {
    printf("Block size: %d\n", profile_size_arr[i]);
    printf("memmove avg: %ld\n", std_lib_move_avg[i]);
    printf("memset avg: %ld\n", std_lib_set_avg[i]);
    printf("my_memmove avg: %ld\n", mem_lib_move_avg[i]);
    printf("my_memset avg: %ld\n", mem_lib_set_avg[i]);
    printf("my_memmove_opt avg: %ld\n", opt_mem_lib_move_avg[i]);
    printf("my_memset_opt avg: %ld\n", opt_mem_lib_set_avg[i]);
    printf("\n");
  }
#endif /* PLATFORM_KL25Z */

#endif /* PROFILE */

#ifdef DMA_TEST
  dma_init();

  uint8_t * src = malloc(100);
  uint8_t * dst = malloc(100);
  uint8_t * set = malloc(100);

  memset_dma(set, 100, 0xA5);

  for(uint8_t i = 0; i < 100; i++)
  {
    src[i] = i;
  }
  memmove_dma(src, dst, 100);
  memmove_dma(&src[10], src, 50);

  for(uint8_t i = 0; i < 100; i++)
  {
    src[i] = i;
  }
  memmove_dma(src, &src[10], 50);
  while(1);
#endif /* DMA_TEST */

#ifdef PLATFORM_KL25Z
  uint32_t stack_used = max_stack_used();
  if(stack_used);
  while(1);
#endif /* PLATFORM_KL25Z */
}
