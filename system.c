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
	P0FSR = 0x0F;		// P00 P01 P02 P03 as pwm out
 	P0    = 0x00;		// All off	
	P0IO  = 0xF;		// All output
	P0PU  = 0x00;		// No pull-up
	P0OD  = 0x00;		// All Push-pull
	
	// Port 1
	P1FSRL = 0x0B;		// P10 P11 P13 as CMP
	P1FSRH = 0x82;		// P17 as AN3 P15 as IO P14 as An0
	P1   = 0x00;
	P1IO = 0x20; 
	P1PU = 0x07;
	
	// Port 2
	P2FSRH = 0x0C;		//
	P2FSRL = 0x20;		//
	P2   = 0x00;
	P2IO = 0x00;
	P2PU = 0x00;
	P2OD = 0x00;
	
}

void	clock_init(void)
{	
	OSCCR = (5<<3)|	// IRC frequency selection   20MHz
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
	ADCCRH = 0x07;		//20MHz/4, LSB align
	ADCCRL = 0x87;

	ADCCRL = 0xC7;		//dummy start
	while((ADCCRL&0x10)==0);
}

void uart_init()
{
	P3FSR |= ((1<<3)|(1<<2));
	
	USIBD=126;   // baud 9600
	
	USICR1 = 0x06;   // 异步UART ，无奇偶 ，8位
	USICR2 = (1<<3)|(1<<1);   //  使能USI 模块、发送
	 
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
		|(0<<2)// Period Match Interrupt Occurrence Selection
		|(1<<1)				// Delay Time Insertion - disable
		|(1<<0);			// Delay Time Insertion Position
	
	T3PDR = (INT16U)(DCARRIER_SET);
	pwm_set_duty(0);
	
	T3OUTCRH= (1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<2)|(1<<1);		//A=H-Start,B=H-Start, B=Output Disable, A=Output Enable; // H-side PWM, L-side GPIO
	T3OUTCRL= 0x00;			//When disabled, output 'L'

	T3DLY = 60;		//Dead-time = 3us (60@20MHz)
	
	T3INTCR = 0x00;		//No Interrupt
	T3IFR   = 0x00;		//Interrupt all cleared
	T3ADTCR = 0x00;

	T3CRH |= 0x80;	// start PWM timer 	
}

void tick_init()
{
	T2ADR = 389;   // 10ms

	T2CRL = 0x00;  // 20Mhz/512     0.0256ms
	T2CRH = (1<<7) | (1<<0);  // 使能
}
void int_init()
{
	EIPOL1 = 0x02;  // EINT11 falling edge 
	IE1 |= (1<<5);  //  enable EINT11
	IE2 |= ((1<<3)|(1<<2)); // enable timer1/2 match
	IE3 |= (1<<1);   // cmp 012
}

void cmp_init()
{
	CMPNFCR = 0x33;
	CMPPOL = 0x05;
	CMPCR = 0x30;
}
void system_init()
{
	wdt_init();
	lvr_init();
	port_init();
	adc_init();
	clock_init(); 
	pwm_init();
	uart_init();
	int_init();
	tick_init();

	cmp_init();
	adc_init();
	
//	fault_init();			

//interrupt_init();
	
//	runIndicator(OFF);                                         
	//errIndicator(OFF);    
}
