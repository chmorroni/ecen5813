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
 * @file project4.c 
 * @brief This file is to be used for project 4.
 *
 * @author Christopher Morroni
 * @date 2018-04-29
 *
 */

#include "platform.h"
#include "circbuf.h"
#include "uart.h"
#include "log.h"
#include "project4.h"

void project4()
{
#ifdef PLATFORM_KL25Z
  CB_t * ptr_rx_buf;
  UART_configure(115200, &ptr_rx_buf);

//  PRINT_STR("Hello world!\n\r");
//  log_string("Hello logger!\n\r");
//
//  log_pkt(LOGGER_INITIALIZED, 0, 0, NULL);
//
//  PRINT_STR("Now I'm doing some stuff");
//  log_string(" for ");
//  log_int(5);
//  log_string(" minutes");
//  PRINT_STR(".\n\r");

  char str[] = "Some log info.";
  log_pkt(INFO, 0, 14, str);

//  PRINT_STR("That's all, folks!\n\r");
//  log_string("Closing connection.\n\r");

  while(1);
#endif
}
