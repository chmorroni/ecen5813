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
#include "MKL25Z4.h"
#include "circbuf.h"
#include "logger.h"
#include "logger_queue.h"

static CB_t * ptr_uart_tx_circ_buf = NULL;
static CB_t * ptr_uart_rx_circ_buf = NULL;
CB_t * ptr_log_buf = NULL;

#ifdef DEBUG
static void * ptr_to_free = NULL;
#endif

UART_e UART_configure(uint32_t baud, CB_t ** rx_buf)
{
  /* initialize Tx buffer */
  if( CB_init(&ptr_uart_tx_circ_buf, UART_TX_BUFFER_SIZE, sizeof(uint8_t)) != CB_SUCCESS ||
      ptr_uart_tx_circ_buf == NULL)
  {
    return UART_ERROR;
  }

  /* initialize Rx buffer */
  if( CB_init(&ptr_uart_rx_circ_buf, UART_RX_BUFFER_SIZE, sizeof(uint8_t)) != CB_SUCCESS ||
      ptr_uart_rx_circ_buf == NULL)
  {
    return UART_ERROR;
  }

  *rx_buf = ptr_uart_rx_circ_buf;

#ifdef DEBUG
  /* initialize log buffer */
  if( CB_init(&ptr_log_buf, LOG_BUFFER_SIZE, sizeof(log_item_t)) != CB_SUCCESS ||
      ptr_log_buf == NULL)
  {
    return UART_ERROR;
  }
#endif

  uint8_t oversampling_ratio = UART_DEFAULT_OVERSAMPLING_RATIO - 1;
  uint16_t baud_div = UART_CALC_BAUD_DIV(baud, oversampling_ratio);

  /* UART clock setup */
  SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); /* FLL or PLL/2 as UART0 clock */
  SIM_SOPT2 &= ~(SIM_SOPT2_UART0SRC(~1) |
                 SIM_SOPT2_PLLFLLSEL(~0)); /* select FLL clock */
  SIM_SCGC4 |= SIM_SCGC4_UART0(1); /* enable clock to UART module */

  /* set UART0 Rx and Tx sources */
  SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC(~0) |
                 SIM_SOPT5_UART0TXSRC(~0));

  /* enable clock to UART port, A */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

  /* set UART pins, PTA1 and PTA2, to correct mode */
  PORTA_PCR1 |= PORT_PCR_MUX(2);
  PORTA_PCR2 |= PORT_PCR_MUX(2);
  PORTA_PCR1 &= ~PORT_PCR_MUX(5);
  PORTA_PCR2 &= ~PORT_PCR_MUX(5);

  /* disable Rx and Tx */
  UART0_C2 &= ~( UART0_C2_TE(~0) | UART0_C2_RE(~0) );

  UART0_BDH = UART0_BDH_LBKDIE(0)   | /* disable LIN break detect interrupts */
              UART0_BDH_RXEDGIE(0)  | /* disable Rx input active edge interrupts */
              UART0_BDH_SBNS(1)     | /* 1 stop bit */
              UART0_BDH_SBR(baud_div >> 8); /* upper 4 bits of BAUD divisor */

  UART0_BDL = UART0_BDL_SBR(baud_div); /* lower 8 bits of BAUD divisor */

  UART0_C1 = UART0_C1_LOOPS(0)  | /* disable loops mode */
             UART0_C1_DOZEEN(0) | /* disable doze */
             UART0_C1_RSRC(0)   | /* receiver source select, meaningless when loops mode disabled */
             UART0_C1_M(0)      | /* 8 bits per character */
             UART0_C1_WAKE(0)   | /* receiver wakeup method */
             UART0_C1_ILT(0)    | /* idle line type */
             UART0_C1_PE(0)     | /* disable parity */
             UART0_C1_PT(0);      /* parity type */

  UART0_C2 = UART0_C2_TIE(0)    | /* disable transmit interrupts */
             UART0_C2_TCIE(0)   | /* disable transmission complete interrupts */
             UART0_C2_RIE(1)    | /* enable receiver interrupts */
             UART0_C2_ILIE(0)   | /* disable idle line interrupts */
             UART0_C2_TE(0)     | /* keep Tx disabled for now */
             UART0_C2_RE(0)     | /* keep Rx disabled for now */
             UART0_C2_RWU(0)    | /* receiver wakeup control, set to normal */
             UART0_C2_SBK(0);     /* disable sending break characters */

  UART0_C3 = UART0_C3_R8T9(0)   | /* nothing to transmit/receive yet */
             UART0_C3_R9T8(0)   | /* nothing to transmit/receive yet */
             UART0_C3_TXDIR(0)  | /* Tx direction, meaningless when loops mode disabled */
             UART0_C3_TXINV(0)  | /* disable inversion of Tx data */
             UART0_C3_ORIE(0)   | /* disable overrun interrupts */
             UART0_C3_NEIE(0)   | /* disable noise interrupts */
             UART0_C3_FEIE(0)   | /* disable framing error interrupts */
             UART0_C3_PEIE(0);    /* disable parity error interrupts */

  UART0_C4 = UART0_C4_MAEN1(0)  | /* disable match address mode */
             UART0_C4_MAEN2(0)  | /* disable match address mode */
             UART0_C4_M10(0)    | /* disable 10 bit characters */
             UART0_C4_OSR(oversampling_ratio); /* oversampling ratio (default 16) */

  UART0_S2 = UART0_S2_MSBF(0)   | /* LSb first */
             UART0_S2_RXINV(0);   /* disable inversion of Rx data */

  /* enable Rx and Tx */
  UART0_C2 |= UART0_C2_TE(1) | UART0_C2_RE(1) | UART0_C2_RIE(1);

  /* enable interrupts */
  NVIC_EnableIRQ(UART0_IRQn);
  __enable_irq();

  return UART_SUCCESS;
}

UART_e UART_free_buffers()
{
  CB_destroy(&ptr_uart_tx_circ_buf);
  CB_destroy(&ptr_uart_rx_circ_buf);
#ifdef DEBUG
  CB_destroy(&ptr_log_buf);
#endif

  return UART_SUCCESS;
}

UART_e UART_send(uint8_t * data)
{
  if(data == NULL)
  {
    return UART_NULL_PTR;
  }

  /* wait for room in Tx buffer */
  while(!(UART0_S1 & UART0_S1_TDRE_MASK));

  /* place data in buffer */
  UART0_D = *data;

  /* wait for transmission to complete */
  while(!(UART0_S1 & UART0_S1_TC_MASK));

  return UART_SUCCESS;
}

UART_e UART_send_str(uint8_t * data)
{
  if (data == NULL) {
    return UART_NULL_PTR;
  }

  while (*data != '\0') UART_send(data++);
  return UART_SUCCESS;
}

UART_e UART_send_n(uint8_t * data, uint32_t bytes)
{
  if(data == NULL)
  {
    return UART_NULL_PTR;
  }

  uint32_t i;
  for(i = 0; i < bytes; i++)
  {
    UART_send(data + i);
  }

  return UART_SUCCESS;
}

UART_e UART_send_async(uint8_t * data, uint32_t bytes)
{
  if(data == NULL)
  {
    return UART_NULL_PTR;
  }

  uint32_t i;
  for(i = 0; i < bytes; i++)
  {
    /* add data to buffer */
    CB_e ret = CB_buffer_add_item(ptr_uart_tx_circ_buf, (void *)(data + i));
    if(ret == CB_FULL)
    {
      /* enable Tx interrupts if any data was added to the buffer */
      if(i != 0)
      {
        UART0_C2 |= UART0_C2_TIE(1);
      }
      return UART_BUFFER_FULL;
    }
    else if(ret != CB_SUCCESS)
    {
      return UART_ERROR;
    }
  }

  /* enable Tx interrupts */
  UART0_C2 |= UART0_C2_TIE(1);

  return UART_SUCCESS;
}

UART_e UART_send_log(log_item_t * data)
{
  if(data == NULL)
  {
    return UART_NULL_PTR;
  }

  /* add data to buffer */
  CB_e ret = CB_buffer_add_item(ptr_log_buf, (void *)data);
  if(ret != CB_SUCCESS)
  {
    return UART_ERROR;
  }

  /* enable Tx interrupts */
  UART0_C2 |= UART0_C2_TIE(1);

  return UART_SUCCESS;
}

UART_e UART_receive(uint8_t * data)
{
  if(data == NULL)
  {
    return UART_NULL_PTR;
  }

  /* wait for received data */
  while(!(UART0_S1 & UART0_S1_RDRF_MASK));

  /* fetch data */
  *data = UART0_D;

  return UART_SUCCESS;
}

UART_e UART_receive_n(uint8_t * data, uint32_t bytes)
{
  if(data == NULL)
  {
    return UART_NULL_PTR;
  }

  uint32_t i;
  for(i = 0; i < bytes; i++)
  {
    UART_receive(data + i);
  }

  return UART_SUCCESS;
}

void UART0_IRQHandler()
{
  /* Must handle both Tx and Rx interrupts */
  /* Must handle both if both are available */
  if(UART0_S1 & UART0_S1_RDRF_MASK) /* Rx interrupt */
  {
    /* fetch data, this clears the interrupt */
    uint8_t data = UART0_D;
    if( CB_buffer_add_item(ptr_uart_rx_circ_buf, (void *)&data) != CB_SUCCESS )
    {
      /* maybe log something, but there's not a whole lot else we can do */
    }
  }
  if(UART0_C2 & UART0_C2_TIE_MASK &&
     UART0_S1 & UART0_S1_TDRE_MASK) /* Tx interrupt */
  {
    uint8_t data;
    CB_e ret = CB_buffer_remove_item(ptr_uart_tx_circ_buf, (void *)&data);

    if(ret == CB_SUCCESS)
    {
      /* send data, this clears the interrupt */
      UART0_D = data;
    }
    else if(ret == CB_EMPTY)
    {
#ifdef DEBUG
      if(ptr_to_free != NULL)
      {
        free(ptr_to_free);
        ptr_to_free = NULL;
      }

      log_item_t log_item;
      ret = CB_buffer_remove_item(ptr_log_buf, (void *)&log_item);

      if(ret == CB_SUCCESS)
      {
        /* add log packet to the UART Tx buffer */
        CB_add_log_packet(ptr_uart_tx_circ_buf, &log_item);
        ptr_to_free = log_item.payload;
      }
      else
      {
        /* disable Tx interrupts when Tx buffer is empty and no log packets to send */
        UART0_C2 &= ~UART0_C2_TIE(~0);
      }
#else
      /* disable Tx interrupts when Tx buffer is empty */
      UART0_C2 &= ~UART0_C2_TIE(~0);
#endif /* DEBUG */
    }
    else
    {
      /* some other error, disable Tx interrupts */
      UART0_C2 &= ~UART0_C2_TIE(~0);
      /* maybe log something in the future */
    }
  }
}
