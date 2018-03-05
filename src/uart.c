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
#include "conversion.h"

static CB_t * ptr_uart_tx_circ_buf = NULL;
static CB_t * ptr_uart_rx_circ_buf = NULL;

/* CRC16 algorithm */
static unsigned short crc_table [256] = {

  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5,
  0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b,
  0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 0x1231, 0x0210,
  0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
  0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c,
  0xf3ff, 0xe3de, 0x2462, 0x3443, 0x0420, 0x1401,
  0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a, 0xb54b,
  0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6,
  0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719, 0x8738,
  0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5,
  0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969,
  0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96,
  0x1a71, 0x0a50, 0x3a33, 0x2a12, 0xdbfd, 0xcbdc,
  0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
  0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03,
  0x0c60, 0x1c41, 0xedae, 0xfd8f, 0xcdec, 0xddcd,
  0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97, 0x6eb6,
  0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
  0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a,
  0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca, 0xa1eb,
  0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1,
  0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c,
  0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2,
  0x4235, 0x5214, 0x6277, 0x7256, 0xb5ea, 0xa5cb,
  0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
  0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447,
  0x5424, 0x4405, 0xa7db, 0xb7fa, 0x8799, 0x97b8,
  0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3, 0x36f2,
  0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9,
  0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806, 0x6827,
  0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c,
  0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
  0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0,
  0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d,
  0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 0x7c26, 0x6c07,
  0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
  0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba,
  0x8fd9, 0x9ff8, 0x6e17, 0x7e36, 0x4e55, 0x5e74,
  0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

uint16_t CRCCCITT(uint8_t *data, size_t length, uint16_t seed, uint16_t final)
{

  size_t count;
  uint32_t crc = seed;
  uint32_t temp;

  for (count = 0; count < length; ++count)
    {
      temp = (*data++ ^ (crc >> 8)) & 0xff;
      crc = crc_table[temp] ^ (crc << 8);
    }

  return (uint16_t)(crc ^ final);

} 
/* CRC16 algorithm */

UART_e UART_configure(uint32_t baud, CB_t ** rx_buf)
{
  /* initialize Tx buffer */
  if( CB_init(&ptr_uart_tx_circ_buf, UART_TX_BUFFER_SIZE) != CB_SUCCESS ||
      ptr_uart_tx_circ_buf == NULL)
  {
    return UART_ERROR;
  }

  /* initialize Rx buffer */
  if( CB_init(&ptr_uart_rx_circ_buf, UART_RX_BUFFER_SIZE) != CB_SUCCESS ||
      ptr_uart_rx_circ_buf == NULL)
  {
    return UART_ERROR;
  }

  *rx_buf = ptr_uart_rx_circ_buf;

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

#ifdef DO_NOT_DEFINE
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
    CB_e ret = CB_buffer_add_item(ptr_uart_tx_circ_buf, (__cbdata_t)*(data + i));
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
#endif

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
    if( CB_buffer_add_item(ptr_uart_rx_circ_buf, (uint8_t)data) != CB_SUCCESS )
    {
      /* maybe log something, but there's not a whole lot else we can do */
    }
  }
  if(UART0_C2 & UART0_C2_TIE_MASK &&
     UART0_S1 & UART0_S1_TDRE_MASK) /* Tx interrupt */
  {
    __cbdata_t data;
    CB_e ret = CB_buffer_remove_item(ptr_uart_tx_circ_buf, (__cbdata_t *)&data);

    if(ret == CB_SUCCESS)
    {
      /* send data, this clears the interrupt */
      /* UART0_D = data; */
      uint8_t conversion_buf[25];
      uint8_t converted_length = 0;
      UART_send_n(data.str, data.len);
      converted_length = my_itoa(data.len, conversion_buf, 10);
      UART_send_n(conversion_buf, converted_length);
      data.crc = CRCCCITT(data.str, data.len, 0, 0xffff);
      converted_length = my_itoa(data.crc, conversion_buf, 10);
      UART_send_n(conversion_buf, converted_length);
    }
    else if(ret == CB_EMPTY)
    {
      /* disable Tx interrupts when Tx buffer is empty */
      UART0_C2 &= ~UART0_C2_TIE(~0);
    }
    else
    {
      /* some other error, disable Tx interrupts */
      UART0_C2 &= ~UART0_C2_TIE(~0);
      /* maybe log something in the future */
    }
  }
}
