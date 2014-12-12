/*
 * File: bsp.h
 * Author: fascio
 * 
 * Created on November 13th, 2014, 17:18
 */ 
 
#ifndef __BSP_H__
#define __BSP_H__

//**********************************************************************
// BSP Includes
//**********************************************************************
#ifdef __ATMEGA_8535__
#include <mega8535.h>
#endif /* #ifdef __ATMEGA_8535__ */

#include <SPI.h>
#include <delay.h>

//**********************************************************************
// BSP Defines
//**********************************************************************
#define OUTPUT 						(1)
#define INPUT  						(0)
#define LOW                         (0)
#define HIGH                        (1)

//**********************************************************************
// BSP Data Types
//**********************************************************************
typedef enum bsp_ports{
	BSP_PIN_A0,
	BSP_PIN_A1,
	BSP_PIN_A2,
	BSP_PIN_A3,	
	BSP_PIN_B0,
	BSP_PIN_B1,
	BSP_PIN_B2,
	BSP_PIN_B3,
	BSP_PIN_D3,
	BSP_PIN_D4,
	BSP_PIN_D5,
	BSP_PIN_D6
}BSP_PORT;

//**********************************************************************
// BSP System Prototype Functions
//**********************************************************************
void bsp_setup(void);
void bsp_delay_ms(int mscount);
void bsp_delay_100us(void);


//**********************************************************************
// BSP IO Prototype Functions
//**********************************************************************
void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin);
void bsp_io_write(BSP_PORT bsp_pin, int state_pin);
//void bsp_io_toggle(BSP_PORT bsp_pin);

//**********************************************************************
// BSP SPI Functions
//**********************************************************************
void bsp_spi_setup(void);
void bsp_spi_send(int data);


//**********************************************************************
// BSP USART Functions
//**********************************************************************

// BSP USART Defines  
#define BSP_USART_COM_HDLR											(1)	

#define BSP_NO_ERROR_CODE											(0)
#define BSP_USART_READ_DATA_LENGHT_ERROR_CODE						(-1)
#define BSP_USART_WRITE_DATA_LENGHT_ERROR_CODE						(-2)

#define RXB8 														(1)
#define TXB8 														(0)
#define UPE 														(2)
#define OVR 														(3)
#define FE 															(4)
#define UDRE 														(5)
#define RXC 														(7)

#define FRAMING_ERROR 											(1<<FE)
#define PARITY_ERROR 											(1<<UPE)
#define DATA_OVERRUN 											(1<<OVR)
#define DATA_REGISTER_EMPTY 									(1<<UDRE)
#define RX_COMPLETE 											(1<<RXC)

// USART Receiver buffer
#define RX_BUFFER_SIZE 												(128)

// USART Transmitter buffer
#define TX_BUFFER_SIZE 												(128)

// COM

#define BSP_TX_BUFFER_SIZE								(TX_BUFFER_SIZE)

void bsp_usart_setup(void);
void bsp_usart_putc(char data);
char bsp_usart_getc(void);
int  bsp_usart_status(void);
int bsp_usart_fstatus(void);
void bsp_usart_flush(void);
int bsp_usart_write(char * data, int data_lenght);
int bsp_usart_read(char * data, int data_lenght);

//**********************************************************************
// BSP TIMER 16 bits Functions
//**********************************************************************

// Vartypes
typedef void (*BSP_TIMER_UPDATE_FUNCTION)(void);

// API Prototype
void bsp_timer_setup(BSP_TIMER_UPDATE_FUNCTION update_function);


#endif /* __BSP_H__ */
