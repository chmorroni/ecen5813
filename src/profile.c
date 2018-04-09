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
 * @file profile.c 
 * @brief This file is to be used for profiling memory operations.
 *
 * @author Christopher Morroni
 * @date 2018-04-08
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "memory_opt.h"
#include "platform.h"
#include "profile.h"

#ifdef PLATFORM_KL25Z
#include "dma.h"

uint32_t systick_post_clock, systick_post_ctrl;

#else
#include <time.h>
#endif /* PLATFORM_KL25Z */

void profile_init()
{
#ifdef PLATFORM_KL25Z
  SysTick->CTRL &= ~(1 << SysTick_CTRL_ENABLE_Pos); /* disable systick */
  SysTick->CTRL = (1 << SysTick_CTRL_CLKSOURCE_Pos); /* set systick source */
  SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos); /* enable systick */

  dma_init();
#endif /* PLATFORM_KL25Z */
}

#ifdef PLATFORM_KL25Z
void profile_std_lib(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  uint32_t elapsed_arr[PROFILE_NUM_REPS];
#else
void profile_std_lib(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  clock_t pre_clock, post_clock;
  clock_t elapsed_arr[PROFILE_NUM_REPS];
#endif /* PLATFORM_KL25Z */

  uint8_t i;

  /* memmove */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

#ifdef PLATFORM_KL25Z
    SysTick->VAL = 0;
#else
    pre_clock = clock();
#endif /* PLATFORM_KL25Z */

    memmove(dst, src, block_size);

#ifdef PLATFORM_KL25Z
    systick_post_clock = SysTick->VAL;
    systick_post_ctrl = SysTick->CTRL;
    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];
#else
    post_clock = clock();
    elapsed_arr[i] = post_clock - pre_clock;
#endif /* PLATFORM_KL25Z */

  }

  /* calculate average time elapsed */
  *ptr_move_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_move_avg += elapsed_arr[i];
  }
  *ptr_move_avg /= PROFILE_NUM_REPS;

  /* memset */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

#ifdef PLATFORM_KL25Z
    SysTick->VAL = 0;
#else
    pre_clock = clock();
#endif /* PLATFORM_KL25Z */

    memset(src, 0xA5, block_size);

#ifdef PLATFORM_KL25Z
    systick_post_clock = SysTick->VAL;
    systick_post_ctrl = SysTick->CTRL;
    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];
#else
    post_clock = clock();
    elapsed_arr[i] = post_clock - pre_clock;
#endif /* PLATFORM_KL25Z */

  }

  /* calculate average time elapsed */
  *ptr_set_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_set_avg += elapsed_arr[i];
  }
  *ptr_set_avg /= PROFILE_NUM_REPS;
}

#ifdef PLATFORM_KL25Z
void profile_mem_lib(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  uint32_t elapsed_arr[PROFILE_NUM_REPS];
#else
void profile_mem_lib(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  clock_t pre_clock, post_clock;
  clock_t elapsed_arr[PROFILE_NUM_REPS];
#endif /* PLATFORM_KL25Z */

  uint8_t i;

  /* memmove */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

#ifdef PLATFORM_KL25Z
    SysTick->VAL = 0;
#else
    pre_clock = clock();
#endif /* PLATFORM_KL25Z */

    my_memmove(src, dst, block_size);

#ifdef PLATFORM_KL25Z
    systick_post_clock = SysTick->VAL;
    systick_post_ctrl = SysTick->CTRL;
    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];
#else
    post_clock = clock();
    elapsed_arr[i] = post_clock - pre_clock;
#endif /* PLATFORM_KL25Z */

  }

  /* calculate average time elapsed */
  *ptr_move_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_move_avg += elapsed_arr[i];
  }
  *ptr_move_avg /= PROFILE_NUM_REPS;

  /* memset */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

#ifdef PLATFORM_KL25Z
    SysTick->VAL = 0;
#else
    pre_clock = clock();
#endif /* PLATFORM_KL25Z */

    my_memset(src, block_size, 0xA5);

#ifdef PLATFORM_KL25Z
    systick_post_clock = SysTick->VAL;
    systick_post_ctrl = SysTick->CTRL;
    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];
#else
    post_clock = clock();
    elapsed_arr[i] = post_clock - pre_clock;
#endif /* PLATFORM_KL25Z */

  }

  /* calculate average time elapsed */
  *ptr_set_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_set_avg += elapsed_arr[i];
  }
  *ptr_set_avg /= PROFILE_NUM_REPS;
}

#ifdef PLATFORM_KL25Z
void profile_opt_mem_lib(uint32_t * ptr_move_avg, uint32_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  uint32_t elapsed_arr[PROFILE_NUM_REPS];
#else
void profile_opt_mem_lib(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  clock_t pre_clock, post_clock;
  clock_t elapsed_arr[PROFILE_NUM_REPS];
#endif /* PLATFORM_KL25Z */

  uint8_t i;

  /* memmove */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

#ifdef PLATFORM_KL25Z
    SysTick->VAL = 0;
#else
    pre_clock = clock();
#endif /* PLATFORM_KL25Z */

    my_memmove_opt(src, dst, block_size);

#ifdef PLATFORM_KL25Z
    systick_post_clock = SysTick->VAL;
    systick_post_ctrl = SysTick->CTRL;
    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];
#else
    post_clock = clock();
    elapsed_arr[i] = post_clock - pre_clock;
#endif /* PLATFORM_KL25Z */

  }

  /* calculate average time elapsed */
  *ptr_move_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_move_avg += elapsed_arr[i];
  }
  *ptr_move_avg /= PROFILE_NUM_REPS;

  /* memset */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

#ifdef PLATFORM_KL25Z
    SysTick->VAL = 0;
#else
    pre_clock = clock();
#endif /* PLATFORM_KL25Z */

    my_memset_opt(src, block_size, 0xA5);

#ifdef PLATFORM_KL25Z
    systick_post_clock = SysTick->VAL;
    systick_post_ctrl = SysTick->CTRL;
    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];
#else
    post_clock = clock();
    elapsed_arr[i] = post_clock - pre_clock;
#endif /* PLATFORM_KL25Z */

  }

  /* calculate average time elapsed */
  *ptr_set_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_set_avg += elapsed_arr[i];
  }
  *ptr_set_avg /= PROFILE_NUM_REPS;
}

#ifdef PLATFORM_KL25Z
void profile_dma(clock_t * ptr_move_avg, clock_t * ptr_set_avg, uint8_t * src, uint8_t * dst, uint16_t block_size)
{
  uint32_t elapsed_arr[PROFILE_NUM_REPS];

  uint8_t i;

  /* memmove */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

    SysTick->VAL = 0;

    memmove_dma(src, dst, block_size);

    /* wait for DMA to finish */
    while( (DMA_DSR_BCR0 & DMA_DSR_BCR_REQ_MASK) || (DMA_DSR_BCR0 & DMA_DSR_BCR_BSY_MASK) );

    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];

  }

  /* calculate average time elapsed */
  *ptr_move_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_move_avg += elapsed_arr[i];
  }
  *ptr_move_avg /= PROFILE_NUM_REPS;

  /* memset */
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {

    SysTick->VAL = 0;

    memset_dma(src, block_size, 0xA5);

    /* wait for DMA to finish */
    while( (DMA_DSR_BCR0 & DMA_DSR_BCR_REQ_MASK) || (DMA_DSR_BCR0 & DMA_DSR_BCR_BSY_MASK) );

    elapsed_arr[i] = SysTick_VAL_CURRENT_Msk - systick_post_clock;
    elapsed_arr[i] = (systick_post_ctrl & SysTick_CTRL_COUNTFLAG_Msk) ? elapsed_arr[i] + 0x1000000 : elapsed_arr[i];

  }

  /* calculate average time elapsed */
  *ptr_set_avg = 0;
  for(i = 0; i < PROFILE_NUM_REPS; i++)
  {
    *ptr_set_avg += elapsed_arr[i];
  }
  *ptr_set_avg /= PROFILE_NUM_REPS;
}
#endif /* PLATFORM_KL25Z */
