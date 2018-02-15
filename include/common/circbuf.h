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
 * @file circbuf.h
 * @brief A platform-independed circular buffer.
 * 
 * Prototypes and documentation for circular buffer functions, as well as
 * the appropriate data structures.
 * 
 * @author Matthew Haney
 * @date 2018-02-13
 */

#ifndef _CIRCBUF_H_
#define _CIRCBUF_H_

#include <stdint.h>

typedef __cbdata_t uint8_t;

/**
 * @brief Circular buffer data structure
 *
 * Circular buffer data structure
 */
typedef struct {
  __cbdata_t * bmp;
  __cbdata_t * head;
  __cbdata_t * tail;
  size_t size;
  size_t count;
} CB_t;

/**
 * @brief Circular buffer status/error codes
 *
 * Enumeration of different status and error codes that are returned by
 * circular buffer handling functions.
 */
typedef enum {
  CB_SUCCESS,
  CB_NULL_PTR,
  CB_BAD_LEN,
  CB_FULL,
  CB_EMPTY
} CB_e;

/**
 * @brief Initialize circular buffer
 * 
 * Allocate memory for circular buffer (pointer passed by reference) and set
 * up the buffer by allocating base memory of the specified size. Returns 
 * CB_SUCCESS if successful, and an error code otherwise.
 * 
 * @param buffer A pointer to the circular buffer pointer to be allocated
 * @param len The length of the buffer to allocate in memory
 * @return A circular buffer status code
 */
CB_e CB_init(CB_t ** buffer, size_t len);

/**
 * @brief Destroy circular buffer
 *
 * Free memory used by circular buffer, then free memory used to store
 * circular buffer metadata.
 * 
 * @param buffer The buffer to be destroyed
 * @return A circular buffer status code
 */
CB_e CB_destroy(CB_t * buffer);

/**
 * @brief Add item to circular buffer
 * 
 * Add data to circular buffer pointed to by first argument.
 * 
 * @param buffer Pointer to the circular buffer
 * @param data Data to add to buffer
 * @return A circular buffer status code
 */
CB_e CB_buffer_add_item(CB_t * buffer, __cbdata_t data);

/**
 * @brief Remove item from circular buffer
 *
 * Remove data from circular buffer pointed to by first argument.
 * 
 * @param buffer Pointer to the circular buffer
 * @param data Pointer to where data removed from buffer will be stored
 * @return A circular buffer status code
 */
CB_e CB_buffer_remove_item(CB_t * buffer, __cbdata_t * data);

/**
 * @brief Check if circular buffer is full
 * 
 * Check if circular buffer is full
 *
 * @return A circular buffer status code
 */
__attribute__((always_inline)) inline CB_e CB_is_full(CB_t * buffer);

/**
 * @brief Check if circular buffer is empty
 * 
 * Check if circular buffer is empty
 *
 * @return A circular buffer status code
 */
__attribute__((always_inline)) inline CB_e CB_is_empty(CB_t * buffer);

/**
 * @brief Peek into the buffer without removing data
 * 
 * Peek into the circular buffer some number of positions in front of the head
 * and store the data there at the specified location.
 * 
 * @param buffer Pointer to the circular buffer
 * @param pos The number of positions after the head of the buffer to peek
 * @param data Pointer to where the data peeked from the buffer will be stored
 * @return A circular buffer status code
 */
CB_e CB_peek(CB_t * buffer, size_t pos, __cbdata_t * data);

#endif /* _CIRCBUF_H_ */