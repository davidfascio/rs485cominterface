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
#include <mega8535.h>
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
	BSP_PIN_A0	
}BSP_PORT;

//**********************************************************************
// BSP System Prototype Functions
//**********************************************************************
void bsp_setup(void);
void bsp_delay_ms(int mscount);


//**********************************************************************
// BSP IO Prototype Functions
//**********************************************************************
void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin);
void bsp_io_write(BSP_PORT bsp_pin, int state_pin);


//**********************************************************************
// BSP SPI Functions
//**********************************************************************
void bsp_spi_setup(void);
void bsp_spi_send(int data);


//**********************************************************************
// BSP USART Functions
//**********************************************************************
void bsp_usart_setup(void);
void bsp_usart_putc(char data);
char bsp_usart_getc(void);
int  bsp_usart_status(void);
int bsp_usart_fstatus(void);
void bsp_usart_flush(void);
int bsp_usart_write(char * data, int data_lenght);
int bsp_usart_read(char * data, int data_lenght);


/***********************************************************************
 *
 * File name: BSP.C 
 *
 * #include "bsp.h"
 *
 **********************************************************************/

//**********************************************************************
// BSP System Functions
//**********************************************************************
void bsp_setup(void){
	// Declare your local variables here

	// Input/Output Ports initialization
	// Port A initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTA=0x00;
	DDRA=0x00;

	// Port B initialization
	// Func7=Out Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
	// State7=0 State6=T State5=0 State4=0 State3=T State2=T State1=T State0=T 
	PORTB=0x00;
	DDRB=0xB0;

	// Port C initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTC=0x00;
	DDRC=0x00;

	// Port D initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTD=0x00;
	DDRD=0x00;

	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: Timer 0 Stopped
	// Mode: Normal top=FFh
	// OC0 output: Disconnected
	TCCR0=0x00;
	TCNT0=0x00;
	OCR0=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: Timer 1 Stopped
	// Mode: Normal top=FFFFh
	// OC1A output: Discon.
	// OC1B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer 1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;

	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: Timer 2 Stopped
	// Mode: Normal top=FFh
	// OC2 output: Disconnected
	ASSR=0x00;
	TCCR2=0x00;
	TCNT2=0x00;
	OCR2=0x00;

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// INT2: Off
	MCUCR=0x00;
	MCUCSR=0x00;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x00;

	// Analog Comparator initialization
	// Analog Comparator: Off
	// Analog Comparator Input Capture by Timer/Counter 1: Off
	ACSR=0x80;
	SFIOR=0x00;
}

void bsp_delay_ms(int mscount){
	
    delay_ms(mscount);
}

//**********************************************************************
// BSP IO Functions
//**********************************************************************
void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin){
	
	switch(bsp_pin){
		case BSP_PIN_A0:
			DDRA.0 = dir_pin ; /*DDRA |(dir_pin << 0x00);*/
			break;
			
		default:
			break;			
	}	
}

void bsp_io_write(BSP_PORT bsp_pin, int state_pin){
	
	switch(bsp_pin){
		case BSP_PIN_A0:
			PORTA.0 = state_pin;
			break;
			
		default:
			break;			
	}		
}

//**********************************************************************
// BSP SPI Functions
//**********************************************************************

void bsp_spi_setup(void){
	
	// SPI initialization
	// SPI Type: Master
	// SPI Clock Rate: 31.250 kHz
	// SPI Clock Phase: Cycle Half
	// SPI Clock Polarity: Low
	// SPI Data Order: MSB First
	SPCR=0x53;
	SPSR=0x00;
}

void bsp_spi_send(int data){

	spi(data);
}


//**********************************************************************
// BSP USART Functions
//**********************************************************************

// BSP USART Defines  

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
char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE < (256)
	unsigned char rx_wr_index,rx_rd_index,rx_counter;
#else
	unsigned int rx_wr_index,rx_rd_index,rx_counter;
#endif

// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow;

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
	char status,data;
	status=UCSRA;
	data=UDR;
	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	{
		rx_buffer[rx_wr_index]=data;
		
		if (++rx_wr_index == RX_BUFFER_SIZE) 
			rx_wr_index=0;
			
		if (++rx_counter == RX_BUFFER_SIZE)
		{
			rx_counter=0;
			rx_buffer_overflow=1;
		}
	}
}

#ifndef _DEBUG_TERMINAL_IO_
	// Get a character from the USART Receiver buffer
	#define _ALTERNATE_GETCHAR_
	
	#pragma used+

	char getchar(void)
	{
		char data;
		
		while (rx_counter==0);
		
		data=rx_buffer[rx_rd_index];
		if (++rx_rd_index == RX_BUFFER_SIZE) 
			rx_rd_index=0;
			
		#asm("cli")
		--rx_counter;
		#asm("sei")
		
		return data;
	}
	
	#pragma used-
	
#endif

// USART Transmitter buffer
#define TX_BUFFER_SIZE 												(128)
char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE < (256)
	unsigned char tx_wr_index,tx_rd_index,tx_counter;
#else
	unsigned int tx_wr_index,tx_rd_index,tx_counter;
#endif

// This flag is set on USART Transmitter buffer 
bit tx_buffer_flush;

// USART Transmitter interrupt service routine
interrupt [USART_TXC] void usart_tx_isr(void)
{
	if (tx_counter)
	{
		--tx_counter;
		UDR=tx_buffer[tx_rd_index];
		
		if (++tx_rd_index == TX_BUFFER_SIZE) 
			tx_rd_index=0;
	}
	
	tx_buffer_flush = 1;
}

#ifndef _DEBUG_TERMINAL_IO_
	// Write a character to the USART Transmitter buffer
	#define _ALTERNATE_PUTCHAR_

	#pragma used+

	void putchar(char c)
	{
		while (tx_counter == TX_BUFFER_SIZE);
		
		tx_buffer_flush = 0;
		#asm("cli")
		
		if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
		{
			tx_buffer[tx_wr_index]=c;
			
			if (++tx_wr_index == TX_BUFFER_SIZE) 
				tx_wr_index=0;
				
			++tx_counter;
		}
		else
		   UDR=c;
		   
		#asm("sei")
	}
	
	#pragma used-
	
#endif


void bsp_usart_setup(void){
	
	// USART initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	UCSRA=0x00;
	UCSRB=0xD8;
	UCSRC=0x86;
	UBRRH=0x00;
	UBRRL=0x33;
	
	// Global enable interrupts
	#asm("sei")
}

void bsp_usart_putc(char data){
	
	putchar(data);
}

char bsp_usart_getc(void){
	
	return getchar();	
}

int  bsp_usart_status(void){
	
	return rx_counter;
}

int bsp_usart_fstatus(void){
	
	return tx_buffer_flush;
}

void bsp_usart_flush(void){
	
	// Do nothing
}

int bsp_usart_write(char * data, int data_lenght){
	
	int usart_index;

	if(data_lenght > (TX_BUFFER_SIZE - tx_counter))
		return BSP_USART_WRITE_DATA_LENGHT_ERROR_CODE;
		
	for(usart_index = 0; usart_index < data_lenght; usart_index++)
		bsp_usart_putc(data[usart_index]);
		
	return BSP_NO_ERROR_CODE;	
}

int bsp_usart_read(char * data, int data_lenght){
	
	int usart_index;
	
	if(data_lenght > bsp_usart_status())
		return BSP_USART_READ_DATA_LENGHT_ERROR_CODE;
	
	for(usart_index = 0; usart_index < data_lenght; usart_index++)
		data[usart_index] = bsp_usart_getc();
		
	return BSP_NO_ERROR_CODE;
}

#endif /* __BSP_H__ */
