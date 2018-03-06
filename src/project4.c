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
 * @file project4.c 
 * @brief This file is to be used for project 4.
 *
 * @author Christopher Morroni
 * @date 2018-04-29
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "platform.h"
#include "circbuf.h"
#include "uart.h"
#include "log.h"
#include "conversion.h"
#include "profile.h"
#include "project4.h"

void project4()
{
#ifdef PLATFORM_KL25Z
  CB_t * ptr_rx_buf;
  UART_configure(115200, &ptr_rx_buf);
  
  log_pkt(LOGGER_INITIALIZED, 0, 0, NULL);
  
  uint8_t *src, *dst;
  uint8_t len, total_len;
  uint8_t conversion_buf[25];
  uint8_t out_buf[100];

  uint16_t profile_size_arr[] = PROFILE_SIZE_ARR;

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
  
  log_pkt(SYSTEM_INITIALIZED, 0, 0, NULL);
  
  char str[] = "Some log info.";
  log_pkt(INFO, 0, 14, str);

  /* Begin profiling */
  log_pkt(PROFILING_STARTED, 0, 0, NULL);

  uint8_t i;
  for(i = 0; i < PROFILE_SIZE_ARR_LEN; i++) {
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
  log_pkt(PROFILING_COMPLETED, 0, 0, NULL);
  /* Now send profiling results */
  for (i = 0; i < PROFILE_SIZE_ARR_LEN; i++) {
    /* stdlib memmove */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "memmove bs=");
    total_len = 11;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(std_lib_move_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
    /* stdlib memset */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "memset bs=");
    total_len = 10;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(std_lib_set_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
    /* my_memmove */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "my_memmove bs=");
    total_len = 14;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(mem_lib_move_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
    /* my_memset */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "my_memset bs=");
    total_len = 13;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(mem_lib_set_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
    /* my_memmove_opt */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "my_memmove_opt bs=");
    total_len = 18;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(opt_mem_lib_move_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
    /* my_memset_opt */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "my_memset_opt bs=");
    total_len = 17;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(opt_mem_lib_set_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
#ifdef PLATFORM_KL25Z
    /* memmove_dma */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "memmove_dma bs=");
    total_len = 15;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(dma_move_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
    /* my_memset_dma */
    out_buf[0] = '\0'; /* reset output buffer */
    strcat((char*)out_buf, "memset_dma bs=");
    total_len = 14;
    len = my_itoa(profile_size_arr[i], conversion_buf, BASE_10);
    strcat((char*)out_buf, (char*)conversion_buf);
    total_len += len;
    len = my_itoa(dma_set_avg[i], conversion_buf, BASE_10);
    total_len += len + 2;
    strcat((char*)out_buf, ": ");
    strcat((char*)out_buf, (char*)conversion_buf);
    log_pkt(PROFILING_RESULT, 0, total_len, out_buf);
#endif /* PLATFORM_KL25Z */
  }
  log_pkt(SYSTEM_HALTED, 0, 0, NULL);
  
  while(1);
#endif
}
