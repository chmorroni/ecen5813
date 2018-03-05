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
 * @file spi.c
 * @brief SPI implementation for both KL25Z and BBB
 * 
 * SPI implementations for both KL25Z and BBB
 * BBB implementation to come later (Project 4)
 * 
 * @author Matthew Haney
 * @date 2018-04-06
 */

#ifndef _SPI_H_
#define _SPI_H_

/**
 * @brief Initializes the SPI controller
 */
void SPI_init();

/**
 * @brief Reads a single byte from the SPI bus
 * @param byte The byte read from the SPI bus
 */
void SPI_read_byte(uint8_t * byte);

/**
 * @brief Sends a single byte on the SPI bus
 * @param byte The byte to write to the SPI bus
 */
void SPI_write_byte(uint8_t byte);

/**
 * @brief Send multiple bytes over SPI bus
 * 
 * Sends numerous SPI Bytes given a pointer to a byte array and a length of how many bytes to send.
 * @param p Packet of data to send
 * @param length Length of packet to send
 */
void SPI_send_packet(uint8_t * p, size_t length);

/**
 * @brief Blocks until SPI transmit buffer has completed transmitting
 */
void SPI_flush();

#endif
