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

CB_e CB_init(CB_t ** buffer, size_t len) {
  if (buffer == NULL) return CB_NULL_PTR;
  if (len < 1) return CB_BAD_LEN;

  return CB_SUCCESS;
}

CB_e CB_destroy(CB_t * buffer) {
  if (buffer == NULL) return CB_NULL_PTR;

  return CB_SUCCESS;
}

CB_e CB_buffer_add_item(CB_t * buffer, __cbdata_t data) {
  if (buffer == NULL) return CB_NULL_PTR;
  if (buffer->count == buffer->size) return CB_FULL;

  return CB_SUCCESS;
}

CB_e CB_buffer_remove_item(CB_t * buffer, __cbdata_t * data) {
  if (buffer == NULL) return CB_NULL_PTR;
  if (buffer->count == 0) return CB_EMPTY;

  return CB_SUCCESS;
}

__attribute__((always_inline)) inline CB_e CB_is_full(CB_t * buffer) {
  return buffer->count == buffer->size;
}

__attribute__((always_inline)) inline CB_e CB_is_empty(CB_t * buffer) {
  return buffer->count == 0;
}

CB_e CB_peek(CB_t * buffer, size_t pos, __cbdata_t * data) {
  if (buffer == NULL) return CB_NULL;
  if (data == NULL) return CB_NULL;

  return CB_SUCCESS
}
