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
 * @file dma.c
 * @brief Memory manipulation with DMA
 *
 * This file contains the definitions for functions to
 * manipulate memory using DMA.
 *
 * @author Christopher Morroni
 * @date 2018-04-07
 */

#include <stdint.h>
#include <stddef.h> /* for size_t and NULL */
#include "platform.h"
#include "circbuf.h"
#include "dma.h"

static CB_t * ptr_dma_buffer = NULL;

/* unless I come up with a clever way to use the heap without leaking memory */
static uint8_t memset_val;

#ifdef PROFILE
extern uint32_t systick_post_clock, systick_post_ctrl;
#endif /* PROFILE */

void dma_init()
{
  /* initialize buffer */
  if( CB_init(&ptr_dma_buffer, DMA_BUFFER_SIZE, sizeof(dma_t)) != CB_SUCCESS ||
      ptr_dma_buffer == NULL)
  {
    return;
  }

  SIM_SCGC6 = SIM_SCGC6_DMAMUX(1); /* enable clock to DMA */

  NVIC_EnableIRQ(DMA0_IRQn);
  __enable_irq();
}

void dma_start_next_transfer()
{
  dma_t next_dma;
  if( CB_buffer_remove_item(ptr_dma_buffer, (void *)&next_dma) != CB_SUCCESS )
  {
    while(1);
  }

  DMA_SAR0 = (uint32_t)next_dma.src;
  DMA_DAR0 = (uint32_t)next_dma.dst;
  DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(next_dma.len);
  DMA_DCR0 = next_dma.dcr;
}

uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length)
{
  if (src == NULL || dst == NULL) {
    return NULL;
  }

  dma_t temp_dma;
  temp_dma.dcr = DMA_DCR_EINT(1) | /* enable interrupt on completion of transfer */
                 DMA_DCR_ERQ(0) | /* disable peripheral request */
                 DMA_DCR_CS(0) | /* disable cycle steal */
                 DMA_DCR_AA(0) | /* disable auto-align */
                 DMA_DCR_EADREQ(0) | /* disable asynchronous DMA requests */
                 DMA_DCR_SINC(1) | /* enable source increment */
                 DMA_DCR_SSIZE(1) | /* set source size to 8 bit */
                 DMA_DCR_DINC(1) | /* enable destination increment */
                 DMA_DCR_DSIZE(1) | /* set destination size to 8 bit */
                 DMA_DCR_START(1) | /* enable DMA */
                 DMA_DCR_SMOD(0) | /* disable source circular buffer */
                 DMA_DCR_DMOD(0) | /* disable destination circular buffer */
                 DMA_DCR_D_REQ(0) | /* disable clearing of the ERQ bit */
                 DMA_DCR_LINKCC(0) | /* disable channel linking */
                 DMA_DCR_LCH1(0) | /* set link channel 1 */
                 DMA_DCR_LCH2(0); /* set link channel 2 */

  /* if src and dst overlap, check which direction to run the transfer */
  if( src < dst && src + length > dst )
  {
    /* copy backwards through src using block size of the non-overlapped region */
    size_t copy_len = dst - src;
    uint8_t * i;
    /* queue all transfers that have size copy_len */
    for(i = src + length; i > dst; i -= copy_len)
    {
      temp_dma.src = i - copy_len;
      temp_dma.dst = i;
      temp_dma.len = copy_len;
      CB_buffer_add_item(ptr_dma_buffer, (void *)&temp_dma);
      length -= copy_len;
    }

    /* queue the last block */
    temp_dma.src = src;
    temp_dma.dst = dst;
    temp_dma.len = length;
    CB_buffer_add_item(ptr_dma_buffer, (void *)&temp_dma);
  }
  else
  {
    /* copy forward, no need to break into chunks */
    temp_dma.src = src;
    temp_dma.dst = dst;
    temp_dma.len = length;
    CB_buffer_add_item(ptr_dma_buffer, (void *)&temp_dma);
  }

  /* if the DMA is free, start transfer, otherwise ISR will do it */
  if( !(DMA_DSR_BCR0 & DMA_DSR_BCR_REQ_MASK) && !(DMA_DSR_BCR0 & DMA_DSR_BCR_BSY_MASK))
  {
    dma_start_next_transfer();
  }

  return dst;
}

uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value)
{
  if (src == NULL) {
    return NULL;
  }
  
  dma_t temp_dma;
  temp_dma.dcr = DMA_DCR_EINT(1) | /* enable interrupt on completion of transfer */
                 DMA_DCR_ERQ(0) | /* disable peripheral request */
                 DMA_DCR_CS(0) | /* disable cycle steal */
                 DMA_DCR_AA(0) | /* disable auto-align */
                 DMA_DCR_EADREQ(0) | /* disable asynchronous DMA requests */
                 DMA_DCR_SINC(0) | /* disable source increment */
                 DMA_DCR_SSIZE(1) | /* set source size to 8 bit */
                 DMA_DCR_DINC(1) | /* enable destination increment */
                 DMA_DCR_DSIZE(1) | /* set destination size to 8 bit */
                 DMA_DCR_START(1) | /* enable DMA */
                 DMA_DCR_SMOD(0) | /* disable source circular buffer */
                 DMA_DCR_DMOD(0) | /* disable destination circular buffer */
                 DMA_DCR_D_REQ(0) | /* disable clearing of the ERQ bit */
                 DMA_DCR_LINKCC(0) | /* disable channel linking */
                 DMA_DCR_LCH1(0) | /* set link channel 1 */
                 DMA_DCR_LCH2(0); /* set link channel 2 */

  /* we need a more permanent place for the value to live */
  memset_val = value;

  temp_dma.src = &memset_val;
  temp_dma.dst = src;
  temp_dma.len = length;

  CB_buffer_add_item(ptr_dma_buffer, (void *)&temp_dma);

  /* if the DMA is free, start transfer, otherwise ISR will do it */
  if( !(DMA_DSR_BCR0 & DMA_DSR_BCR_REQ_MASK) && !(DMA_DSR_BCR0 & DMA_DSR_BCR_BSY_MASK))
  {
    dma_start_next_transfer();
  }

  return src;
}

void DMA0_IRQHandler()
{
#ifdef PROFILE
  systick_post_clock = SysTick->VAL;
  systick_post_ctrl = SysTick->CTRL;
#endif /* PROFILE */
  /* clear interrupt */
  DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE(1);

  /* start next queued transfer */
  if(ptr_dma_buffer->count > 0)
  {
    dma_start_next_transfer();
  }
}
