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

void bsp_delay_100us(void){
	
	delay_us(100);
}
//**********************************************************************
// BSP IO Functions
//**********************************************************************
void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin){
	
	switch(bsp_pin){
		case BSP_PIN_A0:
			DDRA.0 = dir_pin ; 
			break;
			
		case BSP_PIN_A1:
			DDRA.1 = dir_pin ; 
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
		
		case BSP_PIN_D3:
			DDRD.3 = dir_pin ; 
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


void bsp_io_toggle(BSP_PORT bsp_pin){
	/*	
	switch(bsp_pin){
		case BSP_PIN_A0:
			PORTA.0 ^= 1;			 
			break;
		
		case BSP_PIN_A1:
			PORTA.1 ^= 1;			 
			
		case BSP_PIN_A2:
			PORTA.2 ^= 1;			 
			
		case BSP_PIN_A3:
			PORTA.3 ^= 1;			 
		
		case BSP_PIN_B0:
			PORTB.0 ^= 1;
			
		case BSP_PIN_B1:
			PORTB.1 ^= 1;
			
		case BSP_PIN_B2:
			PORTB.2 ^= 1;
			
		case BSP_PIN_B3:
			PORTB.3 ^= 1;			
		
		case BSP_PIN_D3:
			PORTD.3 ^= 1;
		
		case BSP_PIN_D4:
			PORTD.4 ^= 1;
		
		case BSP_PIN_D5:
			PORTD.5 ^= 1;
		
		case BSP_PIN_D6:
			PORTD.6 ^= 1;
								
		default:
			break;			
	}		
	*/
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



// USART Receiver buffer

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
		   UDR = c;
		   
		#asm("sei")
	}
	
	#pragma used-
	
#endif


void bsp_usart_setup(void){
	
	// Global disable interrupts
	#asm("cli")
	
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
	int local_data_lenght = bsp_usart_status();
	
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

// Timer1 output compare A interrupt service routine every 1 ms
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
	// Place your code here	
	bsp_timer_update();
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
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x10;	
	
	// Global enable interrupts
	#asm("sei")	
	
	bsp_timer_update = update_function;	
}


