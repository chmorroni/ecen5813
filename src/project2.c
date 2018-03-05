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
#include "circbuf.h"

#ifdef PLATFORM_KL25Z
#include "gpio.h"
#include "uart.h"
#endif

void dump_statistics(uint32_t * count_alpha,
                     uint32_t * count_numeric,
                     uint32_t * count_punctuation,
                     uint32_t * count_white_space,
                     uint32_t * count_misc)
{
  uint8_t conversion_buf[25], len;

#ifndef PLATFORM_KL25Z
  UNUSED(len);
#endif

  SEND_STR((uint8_t*)"\n\r###################\n\r", 23);
  SEND_STR((uint8_t*)"# Data Statistics #\n\r", 21);
  SEND_STR((uint8_t*)"###################\n\r", 21);

  SEND_STR((uint8_t*)" Alphabetic: ", 13);
  len = my_itoa(*count_alpha, conversion_buf, BASE_10);
  SEND_STR(conversion_buf, len);

  SEND_STR((uint8_t*)"\n\r Numeric: ", 12);
  len = my_itoa(*count_numeric, conversion_buf, BASE_10);
  SEND_STR(conversion_buf, len);

  SEND_STR((uint8_t*)"\n\r Punctuation: ", 16);
  len = my_itoa(*count_punctuation, conversion_buf, BASE_10);
  SEND_STR(conversion_buf, len);

  SEND_STR((uint8_t*)"\n\r White Space: ", 16);
  len = my_itoa(*count_white_space, conversion_buf, BASE_10);
  SEND_STR(conversion_buf, len);

  SEND_STR((uint8_t*)"\n\r Miscellaneous: ", 18);
  len = my_itoa(*count_misc, conversion_buf, BASE_10);
  SEND_STR(conversion_buf, len);
  SEND_STR((uint8_t*)"\n\r", 2);

  /* clear counts */
  *count_alpha = 0;
  *count_numeric = 0;
  *count_punctuation = 0;
  *count_white_space = 0;
  *count_misc = 0;
}

void project2()
{
#ifdef PLATFORM_KL25Z
  /* set up uart */
  CB_t * ptr_rx_buf;
  UART_configure(115200, &ptr_rx_buf);
#endif

#if defined PLATFORM_HOST || defined PLATFORM_KL25Z
  uint32_t count_alpha = 0;
  uint32_t count_numeric = 0;
  uint32_t count_punctuation = 0;
  uint32_t count_white_space = 0;
  uint32_t count_misc = 0;

#ifdef PLATFORM_HOST
  uint8_t data;
  while( scanf("%c", &data) != EOF )
  {
    if(data)
#else
  __cbdata_t data;
  while(1)
  {
    if( CB_buffer_remove_item(ptr_rx_buf, &data) == CB_SUCCESS )
#endif
    {
      uint8_t rx_char = (uint8_t)data;

      /* interpret data */
      if( (rx_char >= 'A' && rx_char <= 'Z') ||
          (rx_char >= 'a' && rx_char <= 'z') )
      {
        count_alpha++;
      }
      else if(rx_char >= '0' && rx_char <= '9')
      {
        count_numeric++;
      }
      else if( (rx_char >= '!' && rx_char <= '/') ||
               (rx_char >= ':' && rx_char <= '@') ||
               (rx_char >= '[' && rx_char <= '`') ||
               (rx_char >= '{' && rx_char <= '~') )
      {
        count_punctuation++;
      }
      else if( rx_char == ' ' ||
               rx_char == '\n' ||
               rx_char == '\r' ||
               rx_char == '\t')
      {
        count_white_space++;
      }
      else
      {
        count_misc++;
      }

#ifdef PLATFORM_KL25Z
      /* print data on EOF - KL25Z */
      if(rx_char == 0x04)
      {
        dump_statistics( &count_alpha, &count_numeric, &count_punctuation, &count_white_space, &count_misc );
      }
#endif
    }
  }

  /* print data on EOF - HOST */
  dump_statistics( &count_alpha, &count_numeric, &count_punctuation, &count_white_space, &count_misc );

#endif /* defined PLATFORM_HOST || defined PLATFORM_KL25Z */
}

