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
 * @file gpio.c
 * @brief Abstracts away platform-dependent GPIO operation
 * 
 * 
 * 
 * @author Matthew Haney
 * @date 2018-02-13
 */

#include <stdint.h>
#include "gpio.h"
#include "MKL25Z4.h"

void GPIO_Configure()
{
  /* Enable clock gating for LED pins */
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
  /* Configure LED pins to be used for GPIO */
  PORTB_PCR18 |= PORT_PCR_MUX(1);
  PORTB_PCR19 |= PORT_PCR_MUX(1);
  PORTD_PCR1 |= PORT_PCR_MUX(1);
  /* Initialize LEDs to off */
  RGB_RED_OFF();
  RGB_GREEN_OFF();
  RGB_BLUE_OFF();
  /* Configure LED pins to be outputs */
  GPIOB_PDDR |= (1 << 18);
  GPIOB_PDDR |= (1 << 19);
  GPIOD_PDDR |= (1 << 1);
}

void GPIO_nrf_init() {
  /* Set up SPI pins */
  /* Clock: SPSCK */
  PORTD_PCR1 = PORT_PCR_MUX(0x2);
  /* Output: MOSI */
  PORTD_PCR2 = PORT_PCR_MUX(0x2);
  /* Input: MISO */
  PORTD_PCR3 = PORT_PCR_MUX(0x2);
  /* Do CS manually via GPIO */
  PORTD_PCR0 = PORT_PCR_MUX(0x1);
  /* Drive CS high at first */
  GPIOD_PSOR |= (1 << 0);
}

