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
 * @file uart.h
 * @brief Abstract away platform-dependent UART operation on the KL25Z
 * 
 * Abstract away platform-dependent UART operation on the KL25Z
 * 
 * @author Christopher Morroni
 * @date 2018-02-28
 */

#ifndef __UART_H_
#define __UART_H_

#include <stdint.h>

#include "circbuf.h"

#define KL25Z_PROCESSOR_FREQ_MHZ (22.29)
#define UART_DEFAULT_OVERSAMPLING_RATIO (16)
#define UART_CALC_BAUD_DIV(baud, oversamling_ratio) \
  (KL25Z_PROCESSOR_FREQ_MHZ * 1000000 / (baud * (oversamling_ratio + 1)))

/* Circular buffer for Rx interrupts */
#define RX_BUFFER_SIZE 20
extern CB_t * rxbuf;

typedef enum
{
  UART_SUCCESS,
  UART_ERROR
} UART_e;

/**
 * @brief Configures UART to given settings
 *
 * 
 *
 * @param baud The desired BAUD rate
 *
 * @return An enumeration indicating success or failure
 */
UART_e UART_configure(uint32_t baud);

/**
 * @brief Sends a single byte through UART
 *
 * Sends a single byte, blocking until finished
 *
 * @param data A pointer to the byte to send
 *
 * @return An enumeration indicating success or failure
 */
UART_e UART_send(uint8_t * data);

/**
 * @brief Sends a C-style string over UART
 *
 * Sends data over UART using UART_send method until hitting a null character
 *
 * @param data A pointer to the C string to send
 *
 * @return An enumeration indicating success or failure
 */
UART_e UART_send_str(uint8_t * data);

/**
 * @brief Sends a contiguous block of data through UART
 *
 * Sends a block of data, blocking until finished
 *
 * @param data A pointer to the first byte in the block
 * @param bytes The number of bytes to send
 *
 * @return An enumeration indicating success or failure
 */
UART_e UART_send_n(uint8_t * data, uint32_t bytes);

/**
 * @brief Receives a single byte of data from UART
 *
 * Receives a byte, blocking until the byte is received
 *
 * @param data A pointer to store the received byte
 *
 * @return An enumeration indicating success or failure
 */
UART_e UART_receive(uint8_t * data);

/**
 * @brief Receives a number of bytes from UART
 *
 * Receives a given number of bytes, blocking until finished
 *
 * @param data A pointer to store the first byte
 * @param bytes The number of bytes to receive
 *
 * @return An enumeration indicating success or failure
 */
UART_e UART_receive_n(uint8_t * data, uint32_t bytes);

/**
 * @brief The interrupt handler for UART
 *
 * Handles TX and RX interrupts
 *
 * @return none
 */
void UART0_IRQHandler();

#endif /* __UART_H_ */
