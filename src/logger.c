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
 * @file logger.c
 * @brief 
 *
 * 
 *
 * @author Christopher Morroni
 * @date 04/27/2018
 */

#include "conversion.h"
#include "circbuf.h"
#include "logger.h"

#ifdef PLATFORM_KL25Z
#include "uart.h"
#endif

extern CB_t * ptr_log_buf;

void log_send_data(void * data, uint8_t len)
{
#ifdef DEBUG
  PRINT_ITEM(data, len);
#endif
}

void log_send_string(char * str)
{
#ifdef DEBUG
  PRINT_STR(str);
#endif
}

void log_send_int(int32_t i)
{
#ifdef DEBUG
  uint8_t conversion_buf[12], len;
  len = my_itoa(i, conversion_buf, BASE_10);
  PRINT_ITEM(conversion_buf, len);
#endif
}

void log_flush()
{
#ifdef DEBUG
#ifdef PLATFORM_KL25Z
  while(!(UART0_S1 & UART0_S1_TC_MASK));
#else
  fflush(stdout);
#endif /* PLATFORM_KL25Z */
#endif /* DEBUG */
}

void log_init()
{
#ifdef DEBUG
#ifdef PLATFORM_KL25Z
  /* configure hardware */
  SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(2); /* set RTC_CLKIN as RTC source */
  SIM_SOPT1 &= ~SIM_SOPT1_OSC32KSEL(~2);
  SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(4); /* set MCGIRCLK as CLKOUT */
  SIM_SOPT2 &= ~SIM_SOPT2_CLKOUTSEL(~4);
  SIM_SCGC5 |= SIM_SCGC5_PORTC(1); /* enable clock to port C */
  SIM_SCGC6 |= SIM_SCGC6_RTC(1); /* enable RTC */
  PORTC_PCR1 |= PORT_PCR_MUX(1); /* set PTC1 to function as RTC_CLKIN */
  PORTC_PCR1 &= ~PORT_PCR_MUX(~1);
  PORTC_PCR3 |= PORT_PCR_MUX(5); /* set PTC3 to function as CLKOUT */
  PORTC_PCR3 &= ~PORT_PCR_MUX(~5);
  MCG_C1 |= MCG_C1_IRCLKEN(1); /* enable MCGIRCLK */

  /* configure RTC */
  RTC_TSR = RTC_INITIAL_VAL; /* initialize RTC value */
  RTC_CR |= RTC_CR_OSCE(1); /* enable the 32kHz oscillator */
  RTC_SR |= RTC_SR_TCE(1); /* enable RTC */
  RTC_IER |= RTC_IER_TSIE(1); /* enable interrupt every second */

  NVIC_EnableIRQ(RTC_Seconds_IRQn);
  __enable_irq();
#endif /* PLATFORM_KL25Z */
#endif /* DEBUG */
}

void log_send_item(log_item_t * log)
{
#ifdef DEBUG
#ifdef PLATFORM_KL25Z
  UART_send_log(log);
#else
  PRINT_ITEM((uint8_t *)log, sizeof(log->timestamp) + sizeof(log->id) + sizeof(log->source_id) + sizeof(log->len));
  PRINT_ITEM(log->payload, log->len);
  PRINT_ITEM(&log->crc, sizeof(log->crc));
#endif /* PLATFORM_KL25Z */
#endif /* DEBUG */
}

void log_send_packet(log_id_t id, uint8_t len, void * payload)
{
#ifdef DEBUG
  log_item_t log_item;
#ifdef PLATFORM_KL25Z
  log_item.timestamp = RTC_TSR;
#else
  log_item.timestamp = 0;
#endif /* PLATFORM_KL25Z */
  log_item.id = id;
  log_item.source_id = LOG_SOURCE_ID;
  log_item.len = len;
  log_item.payload = payload;

  uint8_t i;
  log_item.crc = 0;
  for(i = 0; i < 7; i++)
  {
    log_item.crc ^= *((uint8_t *)&log_item + i);
  }
  for(i = 0; i < log_item.len; i++)
  {
    log_item.crc ^= *((uint8_t *)log_item.payload + i);
  }

  log_send_item(&log_item);
#endif /* DEBUG */
}

void RTC_Seconds_IRQHandler()
{
#ifdef DEBUG
  log_send_packet(HEARTBEAT, 0, NULL);
#endif
}
