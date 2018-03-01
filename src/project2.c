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

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "project2.h"
#include "conversion.h"
#include "uart.h"
#include "circbuf.h"

/* Circular buffer */
#define BUFFER_SIZE 20
CB_t * rxbuf;
CB_t * txbuf;

/* Data statistics */
uint32_t count_alpha = 0;
uint32_t count_numeric = 0;
uint32_t count_punct = 0;
uint32_t count_misc = 0;

void project2() {
  /* Initialize buffer */
  if (CB_init(&rxbuf, BUFFER_SIZE) != CB_SUCCESS) {
    return; /* Die if buffer couldn't be initialized */
  }
  
  /* Set up UART interrupt */
  
  
  /* Main execution loop */
  __cbdata_t c;
  do {
    /* Wait for buffer to contain data */
    while (CB_buffer_remove_item(rxbuf, &c) == CB_EMPTY);
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
  
}

