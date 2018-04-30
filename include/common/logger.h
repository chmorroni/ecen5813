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
 * @file logger.h
 * @brief 
 *
 * 
 *
 * @author Christopher Morroni
 * @date 04/27/2018
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdint.h>
#include "platform.h"

#define LOG_BUFFER_SIZE (16)
#define RTC_INITIAL_VAL (1525369500) /* scheduled demo time */

#ifdef PLATFORM_KL25Z
#define LOG_SOURCE_ID (0x10)
#elif defined PLATFORM_BBB
#define LOG_SOURCE_ID (0x01)
#elif defined PLATFORM_HOST
#define LOG_SOURCE_ID (0x00)
#else
#define LOG_SOURCE_ID (0xFF)
#endif

/* Platform-specific logging functions */
#ifdef PLATFORM_KL25Z
#define PRINT_ITEM(IT, L) UART_send_n((IT), (L))
#else
#define PRINT_ITEM(IT, L) printf("%.*s", (uint32_t)(L), (char *)(IT))
#endif

#ifdef PLATFORM_KL25Z
#define PRINT_STR(STR) UART_send_str((uint8_t *)STR)
#else
#define PRINT_STR(STR) printf("%s", (STR))
#endif

typedef enum
{
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

typedef struct
{
  uint32_t timestamp;
  uint8_t id;
  uint8_t source_id;
  uint8_t len;
  uint8_t * payload;
  uint8_t crc;
} log_item_t;

/*
 * @brief Logs sequence of bytes to terminal
 */
void log_send_data(void * data, uint8_t len);

/* 
 * @brief Logs c-style string to terminal
 */
void log_send_string(char * str);

/*
 * @brief Logs integer to terminal
 */
void log_send_int(int32_t i);

/*
 * @brief Blocks until current logger buffer is empty
 */
void log_flush();

/*
 * @brief Initialises the necessary functions for logging, minus UART
 */
void log_init();

/*
 * @brief Adds a log item to the logger queue
 */
void log_send_item(log_item_t * log);

/*
 * @brief Creates and sends log packet
 */
void log_send_packet(log_id_t id, uint8_t len, void * payload);

#endif /* _LOGGER_H_ */
