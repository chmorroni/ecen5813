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
 * @file dma.h
 * @brief Memory manipulation with DMA
 * 
 * This header file contains the prototypes for functions to
 * manipulate memory using DMA.
 * 
 * @author Christopher Morroni
 * @date 2018-04-07
 */

#ifndef __DMA_H_
#define __DMA_H_

#include <stdint.h>
#include <stddef.h>

#define DMA_BUFFER_SIZE (32)

typedef struct
{
  uint8_t * src;
  uint8_t * dst;
  size_t len;
  uint32_t dcr;
} dma_t;

/**
 * @brief Initializes DMA
 *
 * @return none
 */
void dma_init();

/**
 * @brief Starts next DMA transfer
 *
 * Pulls from the DMA buffer to start the next DMA transfer
 *
 * @return none
 */
void dma_start_next_transfer();

/**
 * @brief Copies a block of memory
 *
 * Given a pointer to each source and destination and their size,
 * this function copies the data from the source to the destination.
 * Guaranties no data corruption when source and destination overlap.
 * Uses DMA for less CPU intensive transfers.
 *
 * @param src Pointer to the source data
 * @param dst Pointer to the destination data
 * @param length The length of the memory block to copy
 *
 * @return A pointer to the destination memory
 */
uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Sets all bytes in a block of data to a given value
 *
 * Given a pointer to a source memory location and its size,
 * sets each byte in the block to the fiven value.
 *
 * @param src Pointer to the source block
 * @param length The length of the source block
 * @param value The byte that will be copied to each byte of the source block
 *
 * @return A pointer to the source memory block
 */
uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value);

/**
 *
 * @brief The interrupt handler for DMA
 *
 * Checks the DMA buffer to see if there is another transfer queued
 *
 *@return none
 */
void DMA0_IRQHandler();

#endif /* __DMA_H_ */
