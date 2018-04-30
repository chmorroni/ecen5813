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
 * @file logger_queue.c
 * @brief 
 *
 * 
 *
 * @author Christopher Morroni
 * @date 04/29/2018
 */

#include "circbuf.h"
#include "logger.h"

#ifdef PLATFORM_KL25Z
#include "uart.h"
#endif

extern CB_t * ptr_log_buf;

void CB_add_log_packet(CB_t * ptr_circ_buf, log_item_t * ptr_log_item)
{
  uint8_t i;
  for(i = 0; i < 7; i++)
  {
    CB_buffer_add_item(ptr_circ_buf, (void *)((uint8_t *)ptr_log_item + i));
  }
  for(i = 0; i < ptr_log_item->len; i++)
  {
    CB_buffer_add_item(ptr_circ_buf, (void *)(ptr_log_item->payload + i));
  }
  CB_buffer_add_item(ptr_circ_buf, (void *)&ptr_log_item->crc);
}
