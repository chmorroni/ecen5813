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
 * @file circbuf.c
 * @brief A platform-independed circular buffer.
 * 
 * Implementations of circular buffer handling functions.
 * 
 * @author Matthew Haney
 * @date 2018-02-14
 */

#include "platform.h"
#include "circbuf.h"
#include <stdint.h>

CB_e CB_init(CB_t ** buffer, size_t len) {
  /* Check that input to function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  if (len < 1) return CB_BAD_LEN;

  /* Allocate memory for circular buffer struct */
  (*buffer) = (CB_t*)malloc(sizeof(CB_t));
  if (*buffer == NULL) return CB_BAD_MALLOC;

  /* Allocate memory for circular buffer data */
  (*buffer)->bmp = (__cbdata_t*)malloc(sizeof(__cbdata_t) * len);
  if ((*buffer)->bmp == NULL) return CB_BAD_MALLOC;

  /* Initialize buffer size and max size */
  (*buffer)->count = 0;
  (*buffer)->size = len;
  
  /* Initialize head and tail pointers */
  (*buffer)->head = (*buffer)->bmp;
  (*buffer)->tail = (*buffer)->bmp;
  
  return CB_SUCCESS;
}

CB_e CB_destroy(CB_t ** buffer) {
  /* Check that input to function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  if (*buffer == NULL) return CB_NULL_PTR;

  /* Free base memory pointer */
  free((*buffer)->bmp);

  /* Free buffer */
  free(*buffer);

  /* Reset buffer pointer */
  *buffer = NULL;
  
  return CB_SUCCESS;
}

CB_e CB_buffer_add_item(CB_t * buffer, __cbdata_t data) {
  /* Check that input to function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  /* Check that data can actually be added */
  if (buffer->count == buffer->size) return CB_FULL;

  START_CRITICAL();
  
  /* Push data to buffer */
  /* Place new data at head pointer */
  *(buffer->head) = data;
  /* Move head to next available space */
  if (buffer->head == buffer->bmp + buffer->size - 1) {
    /* If we're out of space, loop around */
    buffer->head = buffer->bmp;
  } else {
    /* If we have space, just advance the head */
    (buffer->head)++;
  }
  /* Update current buffer size */
  buffer->count += 1;

  END_CRITICAL();
  
  return CB_SUCCESS;
}

CB_e CB_buffer_remove_item(CB_t * buffer, __cbdata_t * data) {
  /* Check that input to the function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  /* Check that data can actually be removed */
  if (buffer->count == 0) return CB_EMPTY;

  START_CRITICAL();
  
  /* Pop data from buffer */
  /* Retrieve data from the tail of the buffer */
  *data = *(buffer->tail);
  /* Move tail to previous space */
  if (buffer->tail == buffer->bmp + buffer->size - 1) {
    /* If we're out of space, loop around */
    buffer->tail = buffer->bmp;
  } else {
    /* If we have space, just advance the tail */
    (buffer->tail)++;
  }
  /* Update current buffer size */
  buffer->count -= 1;

  END_CRITICAL();
  
  return CB_SUCCESS;
}

CB_e CB_peek(CB_t * buffer, size_t pos, __cbdata_t * data) {
  /* Check that input to the function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  if (data == NULL) return CB_NULL_PTR;
  
  START_CRITICAL();
  __cbdata_t * item = buffer->head;
  /* Walk through buffer */
  while (pos > 0) {
    if (item == buffer->bmp + buffer->size) {
      item = buffer->bmp;
    } else {
      item++;
    }
    pos--;
  }
  *data = *item;
  END_CRITICAL();
   
  return CB_SUCCESS;
}
