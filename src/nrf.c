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
 * @file nrf.c
 * @brief Interface with nRF24L01 chip over SPI
 * 
 * Interface with nRF24L01 chip over SPI
 * 
 * @author Matthew Haney
 * @date 2018-04-08
 */

#include <stdint.h>
#include <stddef.h> /* NULL and size_t */

#include "nrf.h"



uint8_t nrf_read_register(uint8_t register) {
  
}

void nrf_write_register(uint8_t register, uint8_t value) {

}

uint8_t nrf_read_status() {

}

void nrf_write_config(uint8_t config) {

}

uint8_t nrf_read_config() {

}

uint8_t nrf_read_rf_setup() {

}

void nrf_write_rf_setup(uint8_t config) {

}

uint8_t nrf_read_rf_ch() {

}

void nrf_write_rf_ch(uint8_t channel) {

}

void nrf_read_TX_ADDR(uint8_t * address) {

}

void nrf_write_TX_ADDR(uint8_t * tx_addr) {

}

uint8_t nrf_read_fifo_status() {

}

void nrf_flush_tx_fifo() {
  nrf_chip_enable();
  SPI_write_byte(0xc1);
  nrf_chip_disable();
}

void nrf_flush_rx_fifo() {
  nrf_chip_enable();
  SPI_write_byte(0xc2);
  nrf_chip_disable();
}
