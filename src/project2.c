/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file project2.c 
 * @brief This file is to be used for project 2.
 *
 * @author Matthew Haney
 * @date March 1, 2018
 *
 */

#include <stdint.h>
#include "platform.h"
#include "project2.h"
#include "conversion.h"
#include "uart.h"

/* Data statistics */
uint32_t count_alpha = 0;
uint32_t count_numeric = 0;
uint32_t count_punct = 0;
uint32_t count_misc = 0;

void project2() {
  /* Set up UART interrupt */
  UART_configure();
  
  /* Main execution loop */
  uint8_t c;
  do {
    /* Wait for buffer to contain data */
    /* UART_receive_n is blocking - this tries again on an error */
    while (UART_receive_n(&c, 1) == UART_ERROR);
    /* Process UART data from circular buffer */
    if ((c >= 'A' && c <= 'Z') ||
	(c >= 'a' && c <= 'z')) { /* Alphabetic */
      count_alpha++;
    } else if (c >= '0' && c <= '9') { /* Numeric */
      count_numeric++;
    } else if ((c >= '!' && c <= '/') ||
	       (c >= ':' && c <= '@') ||
	       (c >= '[' && c <= '`') ||
	       (c >= '{' && c <= '~')) { /* Punctuation */
      count_punct++;
    } else { /* Miscellaneous */
      count_misc++;
    }
  } while (c != '\n'); /* until EOF character is received */
  /* Dump statistics */
  uint8_t conversion_buf[25];
  UART_send((uint8_t*)"###################\n");
  UART_send((uint8_t*)"# Data Statistics #\n");
  UART_send((uint8_t*)"###################\n");
  UART_send((uint8_t*)" Alphabetic: ");
  my_itoa(count_alpha, conversion_buf, 10);
  UART_send(conversion_buf);
  UART_send((uint8_t*)"\n Numeric: ");
  my_itoa(count_numeric, conversion_buf, 10);
  UART_send(conversion_buf);
  UART_send((uint8_t*)"\n Punctuation: ");
  my_itoa(count_punct, conversion_buf, 10);
  UART_send(conversion_buf);
  UART_send((uint8_t*)"\n Miscellaneous: ");
  my_itoa(count_misc, conversion_buf, 10);
  UART_send(conversion_buf);
  UART_send((uint8_t*)"\n");
}

