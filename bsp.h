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

void bsp_setup(void);

//**********************************************************************
// BSP IO Functions
//**********************************************************************

void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin);
void bsp_io_write(BSP_PORT bsp_pin, int state_pin);
void bsp_delay_ms(int mscount);


//**********************************************************************
// BSP SPI Functions
//**********************************************************************

void bsp_spi_setup(void);
void bsp_spi_send(int data);


////////////////////////////////////////////////////////////////////////


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


void bsp_delay_ms(int mscount){
    delay_ms(mscount);
}
#endif /* __BSP_H__ */
