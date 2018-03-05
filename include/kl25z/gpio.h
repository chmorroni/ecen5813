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
#include "MKL25Z4.h"

#define RGB_RED_PIN   (18)  /* Red LED: PORTB pin 18 */
#define RGB_BLUE_PIN  (1)   /* Blue LED: PORTD pin 1 */
#define RGB_GREEN_PIN (19)  /* Green LED: PORTB pin 19 */

/* Nice macros to make LED use simple */
#define RGB_RED_ON()        (PORTB_Clear(RGB_RED_PIN))
#define RGB_RED_OFF()       (PORTB_Set(RGB_RED_PIN))
#define RGB_RED_TOGGLE()    (PORTB_Toggle(RGB_RED_PIN))
#define RGB_GREEN_ON()      (PORTB_Clear(RGB_GREEN_PIN))
#define RGB_GREEN_OFF()     (PORTB_Set(RGB_GREEN_PIN))
#define RGB_GREEN_TOGGLE()  (PORTB_Toggle(RGB_GREEN_PIN))
#define RGB_BLUE_ON()       (PORTD_Clear(RGB_BLUE_PIN))
#define RGB_BLUE_OFF()      (PORTD_Set(RGB_BLUE_PIN))
#define RGB_BLUE_TOGGLE()   (PORTD_Toggle(RGB_BLUE_PIN))

/**
 * @brief Set the output value in PORTB at the given bit position
 *
 * Set the output value in PORTB at the given bit position
 * 
 * @param bit_num The bit in PORTB to set
 */
__attribute__((always_inline)) static inline void PORTB_Set(uint8_t bit_num)
{
  if (bit_num < 32) GPIOB_PSOR = (1 << bit_num);
}

/**
 * @brief Set the output value in PORTD at the given bit position
 *
 * Set the output value in PORTD at the given bit position
 *
 * @param bit_num The bit in PORTD to set
 */
__attribute__((always_inline)) static inline void PORTD_Set(uint8_t bit_num)
{
  if (bit_num < 32) GPIOD_PSOR = (1 << bit_num);
}

/**
 * @brief Clear the output value in PORTB at the given bit position
 *
 * Clear the output value in PORTB at the given bit position
 *
 * @param bit_num The bit in PORTB to clear
 */
__attribute__((always_inline)) static inline void PORTB_Clear(uint8_t bit_num)
{
  if (bit_num < 32) GPIOB_PCOR = (1 << bit_num);
}

/**
 * @brief Clear the output value in PORTD at the given bit position
 *
 * Clear the output value in PORTD at the given bit position
 * 
 * @param bit_num The bit in PORTD to clear
 */
__attribute__((always_inline)) static inline void PORTD_Clear(uint8_t bit_num)
{
  if (bit_num < 32) GPIOD_PCOR = (1 << bit_num);
}

/**
 * @brief Toggle the output value in PORTB at the given bit position
 *
 * Toggle the output value in PORTB at the given bit position
 *
 * @param bit_num The bit in PORTB to toggle
 */
__attribute__((always_inline)) static inline void PORTB_Toggle(uint8_t bit_num)
{
  if (bit_num < 32) GPIOB_PTOR = (1 << bit_num);
}

/**
 * @brief Toggle the output value in PORTD at the given bit position
 *
 * Toggle the output value in PORTD at the given bit position
 *
 * @param bit_num The bit in PORTD to toggle
 */
__attribute__((always_inline)) static inline void PORTD_Toggle(uint8_t bit_num)
{
  if (bit_num < 32) GPIOD_PTOR = (1 << bit_num);
}

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
__attribute__((always_inline)) static inline void Toggle_Red_LED()
{
  RGB_RED_TOGGLE();
}

#endif /* _GPIO_H_ */
