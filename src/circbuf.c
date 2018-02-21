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
  buffer->bmp = (__cbdata_t*)malloc(sizeof(__cbdata_t) * len);
  if (buffer->bmp == NULL) return CB_BAD_MALLOC;

  /* Initialize buffer size and max size */
  buffer->count = 0;
  buffer->size = len;
  
  /* Initialize head and tail pointers */
  buffer->head = buffer->bmp;
  buffer->tail = buffer->bmp;
  
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
  buffer = NULL;
  
  return CB_SUCCESS;
}

CB_e CB_buffer_add_item(CB_t * buffer, __cbdata_t data) {
  /* Check that input to function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  /* Check that data can actually be added */
  if (buffer->count == buffer->size) return CB_FULL;

  /* Push data to buffer */
  /* Move head to next available space */
  if (buffer->head == buffer->bmp + buffer->size) {
    /* If we're out of space, loop around */
    buffer->head = buffer->bmp;
  } else {
    /* If we have space, just advance the head */
    (buffer->head)++;
  }
  /* Place new data at head pointer */
  *(buffer->head) = data;
  /* Update current buffer size */
  buffer->count += 1;
  
  return CB_SUCCESS;
}

CB_e CB_buffer_remove_item(CB_t * buffer, __cbdata_t * data) {
  /* Check that input to the function is valid */
  if (buffer == NULL) return CB_NULL_PTR;
  /* Check that data can actually be removed */
  if (buffer->count == 0) return CB_EMPTY;
  
  /* Pop data from buffer */
  /* Retrieve data from the tail of the buffer */
  *data = *(buffer->tail);
  /* Move tail to previous space */
  if (buffer->tail == buffer->bmp) {
    /* If we're out of space, loop around */
    buffer->tail = buffer->bmp + buffer->size;
  } else {
    /* If we have space, just recess the tail */
    (buffer->tail)--;
  }
  /* Update current buffer size */
  buffer->count += 1;
  
  return CB_SUCCESS;
}

__attribute__((always_inline)) inline CB_e CB_is_full(CB_t * buffer) {
  return buffer->count == buffer->size;
}

__attribute__((always_inline)) inline CB_e CB_is_empty(CB_t * buffer) {
  return buffer->count == 0;
}

CB_e CB_peek(CB_t * buffer, size_t pos, __cbdata_t * data) {
  /* Check that input to the function is valid */
  if (buffer == NULL) return CB_NULL;
  if (data == NULL) return CB_NULL;

  /* This is easy to do with modular offset math */
  /* This one liner is the same as: */
  /*   size_t offset = count + pos; */
  /*   offset = offset % size; */
  /*   data = *(buffer->bmp + offset); */
  data = *(buffer->bmp + ((buffer->count + pos) % buffer->size) );
  
  return CB_SUCCESS
}
