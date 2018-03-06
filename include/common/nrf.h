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
 * @file nrf.h
 * @brief Interface with nRF24L01 chip over SPI
 * 
 * Interface with nRF24L01 chip over SPI
 * 
 * @author Matthew Haney
 * @date 2018-04-08
 */

#ifndef _NRF_H_
#define _NRF_H_

#include "spi.h"

/* Constants */
#define NRF_STATUS_REG (0x00)
#define NRF_TXADDR_REG (0x10)
#define NRF_POWER_UP (1)
#define NRF_POWER_DOWN (0)
#define NRF_POWER_UP_MASK (0x02)

/**
 * @brief Read the register and return the value
 * @param register The register
 * @return The value
 */
uint8_t nrf_read_register(uint8_t register);

/**
 * @brief Write to the given register with the data.
 * @param register The register
 * @param value Value to write
 * @return Status code
 */
void nrf_write_register(uint8_t register, uint8_t value);

/**
 * @brief Reads the STATUS register
 * @return value of nRF STATUS register
 */
uint8_t nrf_read_status();

/**
 * @brief Write to CONFIG register
 * @param config Value to write to nRF CONFIG register
 */
void nrf_write_config(uint8_t config);

/**
 * @brief Read the CONFIG register
 * @return Value of nRF CONFIG register
 */
uint8_t nrf_read_config();

/**
 * @brief Reads RF_SETUP register
 * @return Value of nRF RF_SETUP register
 */
uint8_t nrf_read_rf_setup();

/**
 * @brief Writes to the RF_SETUP register
 * @param config Value of nRF RF_SETUP register to write
 */
void nrf_write_rf_setup(uint8_t config);

/**
 * @brief Reads RF_CH register
 * @return Value of nRF RF_CH register
 */
uint8_t nrf_read_rf_ch();

/**
 * @brief Writes to the RF_CH register
 * @param channel Value to write to nRF RF_CH register
 */
void nrf_write_rf_ch(uint8_t channel);

/**
 * @brief Reads the 5 bytes of the TX_ADDR register
 * @param address Address at which to store value of TX_ADDR register
 */
void nrf_read_TX_ADDR(uint8_t * address);

/**
 * @brief Writes the 5 byte TX_ADDR register
 * @param address Address from which to write value of TX_ADDR register
 */
void nrf_write_TX_ADDR(uint8_t * tx_addr);

/**
 * @brief Reads FIFO_STATUS register
 * @return Value of FIFO_STATUS register
 */
uint8_t nrf_read_fifo_status();

/**
 * @brief Sends the command FLUSH_TX
 */
void nrf_flush_tx_fifo();

/**
 * @brief Sends the command FLUSH_RX
 */
void nrf_flush_rx_fifo();

__attribute__((always_inline)) inline void nrf_chip_enable() {
  GPIOD_PCOR |= (1 << 0);
}
  
__attribute__((always_inline)) inline void nrf_chip_disable() {
  GPIOD_PSOR |= (1 << 0);
}

__attribute__((always_inline)) inline void nrf_transmit_enable() {
  
}

__attribute__((always_inline)) inline void nrf_transmit_disable() {
  
}

#endif
