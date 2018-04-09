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
#include "conversion.h"
#include "platform.h"
#include "profile.h"
#include "project3.h"

#ifdef PLATFORM_KL25Z
#include "dma.h"
#include "uart.h"
#endif /* PLATFORM_KL25Z */

void project3()
{

#ifdef PLATFORM_KL25Z
  watermark_stack();

  /* set up UART */
  CB_t * ptr_rx_buf;
  UART_configure(115200, &ptr_rx_buf);
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

  uint8_t conversion_buf[25], len;

#ifndef PLATFORM_KL25Z
  UNUSED(len);
#endif /* PLATFORM_KL25Z */

  SEND_STR((uint8_t*)"\n\r##############\n\r", 18);
  SEND_STR((uint8_t*)"# Statistics #\n\r", 16);
  SEND_STR((uint8_t*)"##############\n\r", 16);

  for(i = 0; i < PROFILE_SIZE_ARR_LEN; i++)
  {
    SEND_STR((uint8_t*)" Block size: ", 13);
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    SEND_STR((uint8_t*)"\n\r memmove: ", 12);
    len = my_itoa(std_lib_move_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    SEND_STR((uint8_t*)"\n\r memset: ", 11);
    len = my_itoa(std_lib_set_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    SEND_STR((uint8_t*)"\n\r my_memmove: ", 15);
    len = my_itoa(mem_lib_move_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    SEND_STR((uint8_t*)"\n\r my_memset: ", 14);
    len = my_itoa(mem_lib_set_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    for(uint32_t j = 0; j < 10000; j++);

    SEND_STR((uint8_t*)"\n\r my_memmove_opt: ", 19);
    len = my_itoa(opt_mem_lib_move_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    SEND_STR((uint8_t*)"\n\r my_memset_opt: ", 18);
    len = my_itoa(opt_mem_lib_set_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

#ifdef PLATFORM_KL25Z
    SEND_STR((uint8_t*)"\n\r memmove_dma: ", 16);
    len = my_itoa(dma_move_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);

    SEND_STR((uint8_t*)"\n\r memset_dma: ", 15);
    len = my_itoa(dma_set_avg[i], conversion_buf, BASE_10);
    SEND_STR(conversion_buf, len);
#endif /* PLATFORM_KL25Z */

    SEND_STR((uint8_t*)"\n\r\n\r", 4);

    for(uint32_t j = 0; j < 10000; j++);

  }

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

  SEND_STR((uint8_t*)" stack used (words): ", 21);
  len = my_itoa(stack_used, conversion_buf, BASE_10);
  SEND_STR(conversion_buf, len);
  SEND_STR((uint8_t*)"\n\r\n\r", 4);

  while(1);
#endif /* PLATFORM_KL25Z */
}
