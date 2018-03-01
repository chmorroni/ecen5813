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
 * @file uart.c
 * @brief Abstract away platform-dependent UART operation on the KL25Z
 * 
 * Abstract away platform-dependent UART operation on the KL25Z
 * 
 * @author Christopher Morroni
 * @date 2018-02-28
 */

#include <stdint.h>
#include <stddef.h> /* for size_t and NULL */
#include "uart.h"

UART_e UART_configure()
{
  return UART_SUCCESS;
}

UART_e UART_send(uint8_t * data)
{
  if(data == NULL)
  {
    return UART_ERROR;
  }
  return UART_SUCCESS;
}

UART_e UART_send_n(uint8_t * data, uint32_t bytes)
{
  if(data == NULL)
  {
    return UART_ERROR;
  }
  return UART_SUCCESS;
}

UART_e UART_receive(uint8_t * data)
{
  if(data == NULL)
  {
    return UART_ERROR;
  }
  return UART_SUCCESS;
}

UART_e UART_receive_n(uint8_t * data, uint32_t bytes)
{
  if(data == NULL)
  {
    return UART_ERROR;
  }
  return UART_SUCCESS;
}

void UART0_IRQHandler()
{
  
}
