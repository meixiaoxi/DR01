#include <intrins.h>
#include "MC96FD316.h"
#include "common.h"

void	wdt_init(void)
{
	WDTIDR = 0x59;			// Write to ID register
	WDTCR = (0<<7)|			// WDTEN(0/1): Disable/Enable WDT Operation/WDTRC
			(0<<6)|			// WDTRTI(0/1): Disable/Enable 3/4 Interval Interrupt
			(0<<5)|			// WDTPDON(0/1): "WDTRC Run"/"WDTCR Stop" in Stop/Idle Mode
			(0<<3)|			// WINDOW[1:0]: if 0/1/2/3, 50%/75%/100%/"Not used" window
			(0<<0);     	// WDOVF[2:0]: if 0/1/2/3/4/5/6/7, 2**(6/7/8/9/11/13/14/16)/fWDT overflow time
}

void	lvr_init(void)
{	
	LVRCR = (0<<7)|				// LVRST(0/1): "Not effect"/"Enable at stop release"
			(0<<1)|				// LVRVS[3:0]: 1.6V, if 0/1/2.../13, select one of 13-level
			(0<<0);             // LVREN(0/1): Enable/Disable LVR
}

void	port_init(void)
{	
	// Port 0
	P0FSR = 0x00;		// GPIO
	P0    = 0x00;		// All off	
	P0IO  = 0x3F;		// All output
	P0PU  = 0x00;		// No pull-up
	P0OD  = 0x00;		// All Push-pull
	
	// Port 1
	P1FSRH = 0x55;		// P17=CMP3+,P16=OPOUT,P15=OP-,P14=OP+
	P1FSRL = 0x08;			// P13:CMP012-, P[2:0]:gpio 	
	P1   = 0x00;
	P1IO = 0x00;				// All input 
	P1PU = 0x07;
	
	// Port 2
	P2FSRH = 0x01;		// P27,P26,P25=GPIO,P24=Vbus AN8
	P2FSRL = 0x85;		// P23=AN7,P22=CMD input,P21=CMP1OUT,P20=CMP2OUT
	P2   = 0x00;
	P2IO = 0x00;
	P2PU = 0x00;
	P2OD = 0x00;

	// Port 3
	P3FSR = (0<<4)|		// 0/1: P34/SCK
			(0<<3)|		// 0/1: P33/"RXD/SCL/MISO"
			(0<<2)|		// 0/1: P32/"TXD/SDA/MOSI"
			(0<<1)|		// 0/1: P31/XOUT
			(0<<0);		// 0/1: P30/XIN
	P3IO = 0x31;
	P3PU = 0x00;
	P3OD = 0x00;
	P3   = 0x31;
}

void	clock_init(void)
{	
	OSCCR = (5<<3)|	// IRC frequency selection
			(0<<2)|				// IRCE(0/1): Enable/Disable IRC
			(0<<1);				// XCLKE(0/1): Disable/Enable X-tal
}
/*
void	tick_init(void)
{
	// Timer 0 initialize
	T0CR = 0x8D;	//enable, fx/2048 -->0.1024ms
	T0DR = 9;			//tick per 1.024ms

	_tick = 0;
	_tick_lock = 0;
}
*/

void	adc_init(void)
{
	//ADC Conversion time = 4.5us with 23 clocks at >4.0V
	ADCCRH = 0x02;		//20MHz/4, MSB align
	ADCCRL = 0x87;

	ADCCRL = 0xC7;		//dummy start
	while((ADCCRL&0x10)==0);
}

void uart_init()
{
	USICR1 = 0x06;
	
}

void pwm_init()
{
	//PWM in
	T1ADRH = 0xFF;
	T1ADRL = 0xFF;

	T1CRL = 0xD6;
	T1CRH = 0x10;

	//pwm out
	T3CRH = (0<<7)		// T3 disable
		|(0<<6)				// 0:6-ch mode, 1: force A dmoe
		|(7<<3)				// 7:fx/1
		|(0<<1)				// 0: interval, 2: B2B
		|(1<<0);			// counter clear 
	T3CRL = (1<<6)		// period match
		|(0<<2)				// Period Match Interrupt Occurrence Selection
		|(1<<1)				// Delay Time Insertion - disable
		|(1<<0);			// Delay Time Insertion Position

	T3PDR = (INTU16)(DCARRIER_SET);

	T3OUTCRH= 0x80;		//A=L-Start,B=H-Start, B=Output Disable, A=Output Enable; // H-side PWM, L-side GPIO
	T3OUTCRL= 0x00;			//When disabled, output 'L'
	P0FSR = 0x3f;				// set pwm out	

	T3DLY = 60;		//Dead-time = 3us (60@20MHz)
	
	T3INTCR = 0x00;		//No Interrupt
	T3IFR   = 0x00;		//Interrupt all cleared
	T3ADTCR = 0x00;
}


void int_init()
{
	EIPOL1 = 0x01;  // EINT11 rising edge 
	IE1 |= (1<<5);  //  enable EINT11
	IE2 |= (1<<2); // enable timer1 match
}

void system_init()
{
	wdt_init();
	lvr_init();
	port_init();	
	clock_init(); 
	pwm_init();
	uart_init();
	int_init();
	
//	fault_init();			
//	tick_init();
//interrupt_init();
//adc_init();
	
//	runIndicator(OFF);                                         
	//errIndicator(OFF);    
}
