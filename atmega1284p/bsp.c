////////////////////////////////////////////////////////////////////////
//
// File name: bsp.c
//

//**********************************************************************
// Includes
//**********************************************************************
 #include "bsp.h"
 
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
	// Mode: Normal top=0xFF
	// OC0A output: Disconnected
	// OC0B output: Disconnected
	TCCR0A=0x00;
	TCCR0B=0x00;
	TCNT0=0x00;
	OCR0A=0x00;
	OCR0B=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: Timer1 Stopped
	// Mode: Normal top=0xFFFF
	// OC1A output: Discon.
	// OC1B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer1 Overflow Interrupt: Off
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
	// Clock value: Timer2 Stopped
	// Mode: Normal top=0xFF
	// OC2A output: Disconnected
	// OC2B output: Disconnected
	ASSR=0x00;
	TCCR2A=0x00;
	TCCR2B=0x00;
	TCNT2=0x00;
	OCR2A=0x00;
	OCR2B=0x00;

	// Timer/Counter 3 initialization
	// Clock source: System Clock
	// Clock value: Timer3 Stopped
	// Mode: Normal top=0xFFFF
	// OC3A output: Discon.
	// OC3B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer3 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR3A=0x00;
	TCCR3B=0x00;
	TCNT3H=0x00;
	TCNT3L=0x00;
	ICR3H=0x00;
	ICR3L=0x00;
	OCR3AH=0x00;
	OCR3AL=0x00;
	OCR3BH=0x00;
	OCR3BL=0x00;

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// INT2: Off
	// Interrupt on any change on pins PCINT0-7: Off
	// Interrupt on any change on pins PCINT8-15: Off
	// Interrupt on any change on pins PCINT16-23: Off
	// Interrupt on any change on pins PCINT24-31: Off
	EICRA=0x00;
	EIMSK=0x00;
	PCICR=0x00;

	// Timer/Counter 0 Interrupt(s) initialization
	TIMSK0=0x00;

	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1=0x00;

	// Timer/Counter 2 Interrupt(s) initialization
	TIMSK2=0x00;

	// Timer/Counter 3 Interrupt(s) initialization
	TIMSK3=0x00;
	
	// Analog Comparator initialization
	// Analog Comparator: Off
	// Analog Comparator Input Capture by Timer/Counter 1: Off
	ACSR=0x80;
	ADCSRB=0x00;
	DIDR1=0x00;

	// ADC initialization
	// ADC disabled
	ADCSRA=0x00;
	
	// TWI initialization
	// TWI disabled
	TWCR=0x00;
}

void bsp_delay_ms(int mscount){
	
    delay_ms(mscount);
}

void bsp_delay_100us(void){
	
	delay_us(100);
}

//**********************************************************************
// BSP IO Functions
//**********************************************************************
void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin){
	
	switch(bsp_pin){
		case BSP_PIN_A0:
			DDRA.0 = dir_pin ; /*DDRA |(dir_pin << 0x00);*/
			break;
			
		case BSP_PIN_A1:
			DDRA.1 = dir_pin ; /*DDRA |(dir_pin << 0x00);*/
			break;
		case BSP_PIN_A2:
			DDRA.2 = dir_pin ; 
			break;
		
		case BSP_PIN_A3:
			DDRA.3 = dir_pin ; 
			break;
		
		case BSP_PIN_B0:
			DDRB.0 = dir_pin ; 
			break;
		
		case BSP_PIN_B1:
			DDRB.1 = dir_pin ; 
			break;
			
		case BSP_PIN_B2:
			DDRB.2 = dir_pin ; 
			break;
			
		case BSP_PIN_B3:
			DDRB.3 = dir_pin ; 
			break;
						
		case BSP_PIN_D2:
			DDRD.2 = dir_pin;
			break;
			
		case BSP_PIN_D3:
			DDRD.3 = dir_pin; 
			break;
		
		case BSP_PIN_D4:
			DDRD.4 = dir_pin ; 
			break;	
		
		case BSP_PIN_D5:
			DDRD.5 = dir_pin ; 
			break;
		
		case BSP_PIN_D6:
			DDRD.6 = dir_pin ; 
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
		
		case BSP_PIN_A1:
			PORTA.1 = state_pin;
			break;
		
		case BSP_PIN_A2:
			PORTA.2 = state_pin;
			break;
			
		case BSP_PIN_A3:
			PORTA.3 = state_pin;
			break;
		
		case BSP_PIN_B0:
			PORTB.0 = state_pin;
			break;
		
		case BSP_PIN_B1:
			PORTB.1 = state_pin;
			break;
		
		case BSP_PIN_B2:
			PORTB.2 = state_pin;
			break;
			
		case BSP_PIN_B3:
			PORTB.3 = state_pin;
			break;
		
		case BSP_PIN_D2:
			PORTD.2 = state_pin;
			break;
			
		case BSP_PIN_D3:
			PORTD.3 = state_pin;
			break;
		
		case BSP_PIN_D4:
			PORTD.4 = state_pin;
			break;
		
		case BSP_PIN_D5:
			PORTD.5 = state_pin;
			break;
		
		case BSP_PIN_D6:
			PORTD.6 = state_pin;
			break;
			
		default:
			break;			
	}		
}

/*void bsp_io_toggle(BSP_PORT bsp_pin){
		
	switch(bsp_pin){
		case BSP_PIN_A0:
			PORTA.0 ^= 1;			 
			break;
		
		case BSP_PIN_A1:
			PORTA.1 ^= 1;			 
						
		default:
			break;			
	}		
	
}*/

//**********************************************************************
// BSP SPI Functions
//**********************************************************************

void bsp_spi_setup(void){
		
	// SPI initialization
	// SPI Type: Master
	// SPI Clock Rate: 2000.000 kHz
	// SPI Clock Phase: Cycle Start
	// SPI Clock Polarity: Low
	// SPI Data Order: MSB First
	SPCR=0x52;
	SPSR=0x00;    
}

void bsp_spi_send(int data){

	spi(data);
}


//**********************************************************************
// BSP USART Functions
//**********************************************************************

BSP_USART_UPDATE_FUNCTION bsp_usart_update;

// USART0 Receiver buffer

char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0 <= 256
unsigned char rx_wr_index0 = 0;
unsigned char rx_rd_index0 = 0;
unsigned char rx_counter0 = 0;
#else
unsigned int rx_wr_index0 = 0;
unsigned int rx_rd_index0 = 0;
unsigned int rx_counter0 = 0;
#endif

// This flag is set on USART0 Receiver buffer overflow
bit rx_buffer_overflow0 = 0;

// USART0 Receiver interrupt service routine
interrupt [USART0_RXC] void usart0_rx_isr(void)
{
	
		
	char status,data; 
    
       
	status=UCSR0A;
	data=UDR0;
	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	{
		rx_buffer0[rx_wr_index0++]=data;
		
		#if RX_BUFFER_SIZE0 == 256
		
			// special case for receiver buffer size=256
			if (++rx_counter0 == 0) 
				rx_buffer_overflow0=1;
		#else
			
			if (rx_wr_index0 == RX_BUFFER_SIZE0) 
				rx_wr_index0=0;
				
			if (++rx_counter0 == RX_BUFFER_SIZE0)
			{
				rx_counter0=0;
				rx_buffer_overflow0=1;
			}
			
		#endif
   }
   
   
}

#ifndef _DEBUG_TERMINAL_IO_
	// Get a character from the USART0 Receiver buffer
	#define _ALTERNATE_GETCHAR_

	#pragma used+

	char getchar(void)
	{
		char data;

		while (rx_counter0==0){
			bsp_io_write(BSP_PIN_A2, HIGH);
		}

		data=rx_buffer0[rx_rd_index0++];

		#if RX_BUFFER_SIZE0 != 256

			if (rx_rd_index0 == RX_BUFFER_SIZE0) 
				rx_rd_index0=0;
		#endif
		
		#asm("cli")
		
			--rx_counter0;
			
		#asm("sei")
		
		return data;
	}
	#pragma used-
	
#endif

// This flag is set on USART Transmitter buffer 
bit tx_buffer_flush = 0;

// USART0 Transmitter buffer

char tx_buffer0[TX_BUFFER_SIZE0];

#if TX_BUFFER_SIZE0 <= 256
unsigned char tx_wr_index0 = 0;
unsigned char tx_rd_index0 = 0;
unsigned char tx_counter0 = 0;
#else
unsigned int tx_wr_index0 =0;
unsigned int tx_rd_index0 = 0;
unsigned int tx_counter0 = 0;
#endif

// USART0 Transmitter interrupt service routine
interrupt [USART0_TXC] void usart0_tx_isr(void)
{
	
	if (tx_counter0)
	{
		--tx_counter0;
		UDR0=tx_buffer0[tx_rd_index0++];
	
	#if TX_BUFFER_SIZE0 != 256
	if (tx_rd_index0 == TX_BUFFER_SIZE0) 
		tx_rd_index0=0;
	#endif
	}
	
	else{
		tx_buffer_flush = 1;		
		
		//if(bsp_usart_update != NULL)
			bsp_usart_update();
	}
	
		
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART0 Transmitter buffer
#define _ALTERNATE_PUTCHAR_

#pragma used+

	void putchar(char c)
	{
		while (tx_counter0 == TX_BUFFER_SIZE0){
			bsp_io_write(BSP_PIN_A2, HIGH);
		}
		
		tx_buffer_flush = 0;
		
		#asm("cli")

		if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
		{
			tx_buffer0[tx_wr_index0++]=c;
			
			#if TX_BUFFER_SIZE0 != 256
			
			if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
			
			#endif
			++tx_counter0;
		}
		else
			UDR0=c;
			
		#asm("sei")
	}
#pragma used-

#endif

void bsp_usart_setup(BSP_USART_UPDATE_FUNCTION update_function){
	
	// Global disable interrupts
	#asm("cli")
	
	// USART0 initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART0 Receiver: On
	// USART0 Transmitter: On
	// USART0 Mode: Asynchronous
	// USART0 Baud Rate: 9600
	UCSR0A=0x00;
	UCSR0B=0xD8;
	UCSR0C=0x06;
	UBRR0H=0x00;
	UBRR0L=0x33;

	// USART1 initialization
	// USART1 disabled
	UCSR1B=0x00;
	
	bsp_usart_update = update_function;
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
	
	return rx_counter0;
}

int bsp_usart_fstatus(void){
	
	return tx_buffer_flush;
}

void bsp_usart_flush(void){
	
	// Do nothing
}

int bsp_usart_write(char * data, int data_lenght){
	
	int usart_index;

	if(data_lenght > (TX_BUFFER_SIZE0 - tx_counter0))
		return BSP_USART_WRITE_DATA_LENGHT_ERROR_CODE;
		
	for(usart_index = 0; usart_index < data_lenght; usart_index++)
		bsp_usart_putc(data[usart_index]);
		
	return BSP_NO_ERROR_CODE;	
}

int bsp_usart_read(char * data, int data_lenght){
	
	int usart_index;
	volatile int local_data_lenght = bsp_usart_status();
	
	if(local_data_lenght > 0){
	
		if(local_data_lenght > data_lenght)
			local_data_lenght = data_lenght;
			
		for(usart_index = 0; usart_index < local_data_lenght; usart_index++)
			data[usart_index] = bsp_usart_getc();
			
		return local_data_lenght;
	} 
	
	return 0;
}

//**********************************************************************
// BSP TIMER 16 bits Functions
//**********************************************************************
BSP_TIMER_UPDATE_FUNCTION bsp_timer_update;

// Timer1 output compare A interrupt service routine every 100 ms
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
	// Global disable interrupts
	//#asm("cli")
	// Place your code here	
	bsp_timer_update();
	// Global enable interrupts
	//#asm("sei")	
}

// API
void bsp_timer_setup(BSP_TIMER_UPDATE_FUNCTION update_function){
	
	// Global disable interrupts
	#asm("cli")
		
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 125.000 kHz
	// Mode: CTC top=OCR1A
	// OC1A output: Discon.
	// OC1B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: On
	// Compare B Match Interrupt: Off
	TCCR1A=0x00;
	TCCR1B=0x0B;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x7D;
	OCR1BH=0x00;
	OCR1BL=0x00;
	
	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1=0x02;
	
	// Global enable interrupts
	#asm("sei")	
	
	bsp_timer_update = update_function;	
}

