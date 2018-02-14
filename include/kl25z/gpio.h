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
 * @file gpio.h
 * @brief Abstract away platform-dependent GPIO operation on the KL25Z
 * 
 * Abstract away platform-dependent GPIO operation on the KL25Z
 * 
 * @author Matthew Haney
 * @date 2018-02-13
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

#define RGB_RED_PIN 18 /* Red LED: PORTB pin 18 */
#define RGB_BLUE_PIN 1 /* Blue LED: PORTD pin 1 */
#define RGB_GREEN_PIN 19 /* Green LED: PORTB pin 19 */

/* Nice macros to make LED use simple */
#define RGB_RED_ON() (PORTB_Set(RGB_RED_PIN))
#define RGB_RED_OFF() (PORTB_Clear(RGB_RED_PIN))
#define RGB_RED_TOGGLE() (PORTB_Toggle(RGB_RED_PIN))
#define RGB_GREEN_ON() (PORTB_Set(RGB_GREEN_PIN))
#define RGB_GREEN_OFF() (PORTB_Clear(RGB_GREEN_PIN))
#define RGB_GREEN_TOGGLE() (PORTB_Toggle(RGB_GREEN_PIN))
#define RGB_BLUE_ON() (PORTD_Set(RGB_BLUE_PIN))
#define RGB_BLUE_OFF() (PORTD_Clear(RGB_BLUE_PIN))
#define RGB_BLUE_TOGGLE() (PORTD_Toggle(RGB_BLUE_PIN))

/**
 * @brief Configures RGB LEDs and sets their initial values
 *
 * Configures RGB LEDs and sets their initial values
 */
void GPIO_Configure();

/**
 * @brief Toggle the state of the red LED
 *
 * Toggle the state of the red LED
 */
void Toggle_Red_LED();

/**
 * @brief Set the output value in PORTB at the given bit position
 *
 * Set the output value in PORTB at the given bit position
 * 
 * @param bit_num The bit in PORTB to set
 */
void PORTB_Set(uint8_t bit_num);

/**
 * @brief Set the output value in PORTD at the given bit position
 *
 * Set the output value in PORTD at the given bit position
 *
 * @param bit_num The bit in PORTD to set
 */
void PORTD_Set(uint8_t bit_num);

/**
 * @brief Clear the output value in PORTB at the given bit position
 *
 * Clear the output value in PORTB at the given bit position
 *
 * @param bit_num The bit in PORTB to clear
 */
void PORTB_Clear(uint8_t bit_num);

/**
 * @brief Clear the output value in PORTD at the given bit position
 *
 * Clear the output value in PORTD at the given bit position
 * 
 * @param bit_num The bit in PORTD to clear
 */
void PORTD_Clear(uint8_t bit_num);

/**
 * @brief Toggle the output value in PORTB at the given bit position
 *
 * Toggle the output value in PORTB at the given bit position
 *
 * @param bit_num The bit in PORTB to toggle
 */
void PORTB_Toggle(uint8_t bit_num);

/**
 * @brief Toggle the output value in PORTD at the given bit position
 *
 * Toggle the output value in PORTD at the given bit position
 *
 * @param bit_num The bit in PORTD to toggle
 */
void PORTD_Toggle(uint8_t bit_num);

#endif /* _GPIO_H_ */
