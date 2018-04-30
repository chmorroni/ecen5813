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
 * @file logger_queue.h
 * @brief 
 *
 * 
 *
 * @author Christopher Morroni
 * @date 04/29/2018
 */

#ifndef _LOGGER_QUEUE_H_
#define _LOGGER_QUEUE_H_

#include <stdint.h>
#include "platform.h"

/*
 * @brief add a log packet to a buffer of bytes
 *
 * @param ptr_circ_buf A circular buffer of bytes
 * @param ptr_log_item The log item to add to the buffer
 *
 * @return none
 */
void CB_add_log_packet(CB_t * ptr_circ_buf, log_item_t * ptr_log_item);

#endif /* _LOGGER_QUEUE_H_ */
