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
 * @file log.h
 * @brief 
 *
 * 
 *
 * @author Christopher Morroni
 * @date 04/27/2018
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <stdint.h>
#include "platform.h"

/* Platform-specific logging functions */
#ifdef PLATFORM_KL25Z
#define LOG_RAW_DATA(D, L) UART_send_n((D), (L))
#else
#define LOG_RAW_DATA(D, L) /* printf */
#endif /* LOG_RAW_DATA */

#ifdef PLATFORM_KL25Z
#define LOG_RAW_STRING(D) UART_send_str((D))
#else
#define LOG_RAW_STRING(D) printf(D)
#endif /* LOG_RAW_STRING */

#ifdef PLATFORM_KL25Z
#define LOG_RAW_INT(I) UART_send(itoa((I)))
#else
#define LOG_RAW_INT(I) printf("%d", (I))
#endif /* LOG_RAW_INT */

#ifdef PLATFORM_KL25Z
#define LOG_FLUSH() while (!(UART0_S1 & UART0_S1_TC_MASK));
#else
#define LOG_FLUSH() fflush(stdout);
#endif /* LOG_FLUSH */

#ifdef PLATFORM_KL25Z
#define LOG_RAW_ITEM(IT) /* UART */
#else
#define LOG_RAW_ITEM(IT) /* printf */
#endif /* LOG_RAW_ITEM */

#define LOG_ITEM(IT, BUF) CB_buffer_add_item((BUF), (IT))

typedef enum {
  SYSTEM_ID = 0,
  SYSTEM_VERSION,
  LOGGER_INITIALIZED,
  GPIO_INITIALIZED,
  SYSTEM_INITIALIZED,
  SYSTEM_HALTED,
  INFO,
  WARNING,
  ERROR,
  PROFILING_STARTED,
  PROFILING_RESULT,
  PROFILING_COMPLETED,
  DATA_RECEIVED,
  DATA_ANALYSIS_STARTED,
  DATA_ALPHA_COUNT,
  DATA_NUMERIC_COUNT,
  DATA_PUNCTUATION_COUNT,
  DATA_MISC_COUNT,
  DATA_ANALYSIS_COMPLETED,
  HEARTBEAT,
  CORE_DUMP
} log_id_t;

typedef struct {
  log_id_t id;
  uint8_t source_id;
  uint32_t timestamp;
  uint8_t len;
  uint8_t * payload;
  uint32_t crc;
} log_item_t;

/*
 * @brief Logs sequence of bytes to terminal
 */
void log_data(uint8_t * data, uint8_t len);

/* 
 * @brief Logs c-style string to terminal
 */
void log_string(uint8_t * str);

/*
 * @brief Logs integer to terminal
 */
void log_integer(uint32_t i);

/*
 * @brief Blocks until current logger buffer is empty
 */
void log_flush();

/*
 * @brief Adds a log item to the logger queue
 */
/* don't need to pass length - part of the struct */
void log_item(log_item_t * log);

#endif /* _LOG_H_ */
