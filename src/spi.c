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

#include <stdint.h>
#include <stddef.h> /* NULL and size_t */

#include "spi.h"
#include "gpio.h"
#include "MKL25Z4.h"

void SPI_init() {
  /* Clock SPI0 module */
  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
  /* Master configuration */
  /* SPI0_BR */
  /** SCK frequency allowed by nRF: 0-4MHz */
  /** So use 4MHz */
  /** 48MHz clock --> divide by 12 */
  /** Prescaler: 3; divisor: 4 */
  SPI0_BR |= (2 << 4) | (1 << 0);
  /* SPI0_C1 */
  /** SPE = 1 */
  /** MSTR = 1 */
  /** CPOL = 0 (conform to nRF chip) */
  /** CPHA = 0 (conform to nRF chip) */
  /** LSBFE = 0 (conform to nRF chip) */
  SPI0_C1 |= (1 << 6) | (1 << 4);
  /* SPI0_C2 */
  /** No config needed */
}

void SPI_read_byte(uint8_t * byte) {
  if (byte == NULL) return;
  /* Wait for data to be available */
  while (!(SPI0_S & (1 << 7))) { }
  /* Write data */
  (*byte) = SPI0_D;
}

void SPI_write_byte(uint8_t byte) {
  /* Wait for buffer to be empty */
  while (!(SPI0_S & (1 << 5))) { }
  /* Write data */
  SPI0_D = byte;
  /* Wait for buffer to be empty */
  while (!(SPI0_S & (1 << 5))) { }
}

void SPI_send_packet(uint8_t * p, size_t length) {
  if (p == NULL) return;
  /* Wait for buffer to be empty */
  while (!(SPI0_S & (1 << 5))) { }
  for (; p < (p + length); p++) {
    /* Write data */
    SPI0_D = *p;
    /* Wait for buffer to be empty */
    while (!(SPI0_S & (1 << 5))) { }
  }
}

void SPI_flush() {
  /* Wait for SPTEF flag to go low */
  while (!(SPI0_S & (1 << 5))) { }
}
