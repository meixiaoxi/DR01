//========================================================== 
//	
//	MC96FD316 Special Function Register assignment
//	
//==========================================================

#ifndef _MC96FD316_
#define _MC96FD316_

sfr   P0      =  0x80; // P0 Data Register
sbit  P00     =  0x80; 
sbit  P01     =  0x81; 
sbit  P02     =  0x82; 
sbit  P03     =  0x83; 
sbit  P04     =  0x84; 
sbit  P05     =  0x85; 
sfr   P0IO    =  0xA1; // P0 Direction Register
sfr   P0OD    =  0x91; // P0 Open-drain Selection Register
sfr   P0PU    =  0xAC; // P0 Pull-up Resistor Selection Register
sfr   P0FSR 	=  0xF1; // Port 0 Function Selection Register

sfr   P1      =  0x88; // P1 Data Register
sbit  P10     =  0x88; 
sbit  P11     =  0x89; 
sbit  P12     =  0x8A; 
sbit  P13     =  0x8B; 
sbit  P14     =  0x8C; 
sbit  P15     =  0x8D; 
sbit  P16     =  0x8E; 
sbit  P17     =  0x8F; 
sfr   P1IO    =  0xB1; // P1 Direction Register
sfr   P1OD    =  0x92; // P1 Open-drain Selection Register
sfr   P1PU    =  0xAD; // P1 Pull-up Resistor Selection Register
sfr   P1DB    =  0x95; // P1 Debounce Enable Register
sfr   P1FSRL	=  0xF2; // Port 1 Function Selection Low Register
sfr   P1FSRH	=  0xF3; // Port 1 Function Selection High Register

sfr   P2      =  0x90; // P2 Data Register
sbit  P20     =  0x90; 
sbit  P21     =  0x91; 
sbit  P22     =  0x92; 
sbit  P23     =  0x93; 
sbit  P24     =  0x94; 
sbit  P25     =  0x95; 
sbit  P26     =  0x96; 
sbit  P27     =  0x97; 
sfr   P2IO    =  0xB9; // P2 Direction Register
sfr   P2OD    =  0x93; // P2 Open-drain Selection Register
sfr   P2PU    =  0xAE; // P2 Pull-up Resistor Selection Register
sfr   P23DB   =  0x96; // P2/P3 Debounce Enable Register
sfr   P2FSRL	=  0xF4; // Port 2 Function Selection Low Register
sfr   P2FSRH	=  0xF5; // Port 2 Function Selection High Register

sfr   P3      =  0x98; // P3 Data Register
sbit  P30     =  0x98; 
sbit  P31     =  0x99; 
sbit  P32     =  0x9A; 
sbit  P33     =  0x9B; 
sbit  P34     =  0x9C; 
sbit  P35     =  0x9D; 
sfr   P3IO    =  0xC1; // P3 Direction Register
sfr   P3OD    =  0x94; // P3 Open-drain Selection Register
sfr   P3PU    =  0xAF; // P3 Pull-up Resistor Selection Register
sfr   P3FSR 	=  0xF6; // Port 3 Function Selection Register

// System Oscillator, Reset Control
sfr   SCCR    =  0x8A; // System Clock Control Register
sfr   OSCCR   =  0xC8; // Oscillator Control Register
sbit	XCLKE		=  0xC9;
sbit	IRCE		=  0xCA;
sfr   BITCNT  =  0x8C; // Basic Interval Timer Counter Register
sfr   BITCR   =  0x8B; // BIT Clock Control Register
sfr   RSTFR   =  0xE8; // Reset Flag Register
sbit  LVRF		=  0xEB;
sbit  OCDRF		=  0xEC;
sbit  WDTRF		=  0xED;
sbit  EXTRF		=  0xEE;
sbit  PORF		=  0xEF;
sfr   PCON    =  0x87; // Power Control Register
sfr   LVRCR   =  0xD8; // Low Voltage Reset Control Register
sbit	LVREN		=  0xD8;
sbit	LVRST		=  0xDF;
sfr   LVICR   =  0x86; // Low Voltage Indicator Control Register

//  Watch Dog Timer Control 
sfr   WDTIDR  =  0x8E; // Watch Dog Timer Identification Register
sfr   WDTCR   =  0x8D; // Watch Dog Timer Control Register

#ifndef   _ASSM_CODE_
#define   WDTC     *(volatile unsigned char xdata*) 0x505E
#define   WDTSR    *(volatile unsigned char xdata*) 0x505F
#else
WDTC        xdata     0x505E 	// Watch Dog Timer Clear Register
WDTSR       xdata     0x505F	// Watch Dog Timer Status Register
#endif  	// _ASSM_CODE_

// Interrupt Control
sfr   IE      =  0xA8; // Interrupt Enable Register 0
sbit  EA      =  0xAF;
sfr   IE1     =  0xA9; // Interrupt Enable Register 1
sfr   IE2     =  0xAA; // Interrupt Enable Register 2
sfr   IE3     =  0xAB; // Interrupt Enable Register 3
sfr   IP      =  0xB8; // Interrupt Priority Register 0
sfr   IP1     =  0xF8; // Interrupt Priority Register 1

sfr   EIFLAG0	=  0xC0; // External Interrupt Flag Register 0
sbit	FLAG0		=	 0xC0;
sbit	FLAG1		=	 0xC1;
sbit	FLAG2		=	 0xC2;
sbit	FLAG3		=	 0xC3;
sbit	FLAG4		=	 0xC4;
sbit	FLAG5		=	 0xC5;
sbit	FLAG6		=	 0xC6;
sbit	FLAG7		=	 0xC7;
sfr   EIPOL0L =  0xA4; // External Interrupt Polarity Low Register 0
sfr   EIPOL0H =  0xA5; // External Interrupt Polarity High Register 0
sfr   EIFLAG1 =  0xB0; // External Interrupt Flag Register 1
sbit	FLAG11	=	 0xB0;
sbit	FLAG12	=	 0xB1;
sbit	FLAG13	=	 0xB2;
sbit	T0IFR		=	 0xB5;
sfr   EIPOL1  =  0xA6; // External Interrupt Polarity Register 1

// TIMER 0 Control
sfr   T0CR    =  0x99; // Timer 0 Mode Control Register
sfr   T0CNT   =  0x9A; // Timer 0 Counter Register
sfr   T0DR    =  0x9B; // Timer 0 Data Register

// TIMER 1 Control
sfr   T1CRL   =  0xB2; // Timer 1 Control Low Register
sfr   T1CRH   =  0xB3; // Timer 1 Control HIgh Register
sfr   T1ADRL  =  0xB4; // Timer 1 A Data Low Register
sfr   T1ADRH  =  0xB5; // Timer 1 A Data High Register
sfr   T1BDRL  =  0xB6; // Timer 1 B Data Low Register
sfr   T1BDRH  =  0xB7; // Timer 1 B Data High Register
#ifndef   _ASSM_CODE_
	sfr16 T1ADR		=  0xB4;
	sfr16 T1BDR		=  0xB5;
#endif

// TIMER 2 Control
sfr   T2CRL   =  0xBA; // Timer 2 Control Low Register
sfr   T2CRH   =  0xBB; // Timer 2 Control HIgh Register
sfr   T2ADRL  =  0xBC; // Timer 2 A Data Low Register
sfr   T2ADRH  =  0xBD; // Timer 2 A Data High Register
sfr   T2BDRL  =  0xBE; // Timer 2 B Data Low Register
sfr   T2BDRH  =  0xBF; // Timer 2 B Data High Register
#ifndef   _ASSM_CODE_
	sfr16 T2ADR		=  0xBC;
	sfr16 T2BDR		=  0xBE;
#endif

// TIMER 3 Control
sfr   T3CRL    =  0xC2; // Timer 3 Control Low Register
sfr   T3CRH    =  0xC3; // Timer 3 Control HIgh Register
sfr		T3OUTCRL = 	0xC4; // Timer 3 Output Control Low Register
sfr		T3OUTCRH = 	0xC5; // Timer 3 Output Control High Register
sfr		T3PDRL	 =	0xC6; // Timer 3 Period Data Low Register
sfr		T3PDRH	 =	0xC7; // Timer 3 Period Data High Register
sfr		T3DLY		 =	0xC9; // Timer 3 PWM Output Delay Register
sfr   T3ADRL   =  0xCA; // Timer 3 A Data Low Register
sfr   T3ADRH   =  0xCB; // Timer 3 A Data High Register
sfr   T3BDRL   =  0xCC; // Timer 3 B Data Low Register
sfr   T3BDRH   =  0xCD; // Timer 3 B Data High Register
sfr   T3CDRL   =  0xCE; // Timer 3 C Data Low Register
sfr   T3CDRH   =  0xCF; // Timer 3 C Data High Register
sfr		T3INTCR	 =  0xD1; // Timer 3 Interrupt Control Register
sfr		T3IFR		 =  0xD2; // Timer 3 Interrupt Flag Register
sfr		T3ADTCR	 =	0xD3; // Timer 3 A/DC Trigger Control Register
sfr		T3ADTDR	 =	0xD4; // Timer 3 A/DC Trigger Generator Data Register
sfr		T3HIZCR	 =	0xD5; // Timer 3 High-Impedance Control Register
#ifndef   _ASSM_CODE_
	sfr16	T3OUTCR	 =  0xC4;
	sfr16	T3PDR		 =  0xC6;
	sfr16	T3ADR		 =  0xCA;
	sfr16	T3BDR		 =  0xCC;
	sfr16	T3CDR		 =  0xCE;
#endif

// BUZZER Control
sfr   BUZCR   =  0x97; // BUZZER Control Register
sfr   BUZDR   =  0x8F; // BUZZER Data Register

// ADC Contol
sfr   ADCCRL  =  0x9C; // A/D Converter Control Low Register
sfr   ADCCRH  =  0x9D; // A/D Converter Control High Register
sfr   ADCDRL  =  0x9E; // A/D Converter Data Low Register
sfr   ADCDRH  =  0x9F; // A/D Converter Data High Register

// (UART + SPI + I2C) Control
sfr   USICR1 	=  0xD9; // USI0 Control Register 1
sfr   USICR2 	=  0xDA; // USI0 Control Register 2
sfr   USICR3 	=  0xDB; // USI0 Control Register 3
sfr   USICR4 	=  0xDC; // USI0 Control Register 4
sfr   USISAR 	=  0xDD; // USI0 Slave Address Register
sfr   USIST1 	=  0xE1; // USI0 Status Register 1
sfr   USIST2 	=  0xE2; // USI0 Status Register 2
sfr   USIBD  	=  0xE3; // USI0 Baud Rate Generation Register
sfr   USISDHR	=  0xE4; // USI0 SDA Hold Time Register
sfr   USIDR  	=  0xE5; // USI0 Data Register
sfr   USISCLR =  0xE6; // USI0 SCL Low Period Register
sfr   USISCHR =  0xE7; // USI0 SCL High Period Register

// Comparator and OP-Amp Control
sfr		CMPFLAG	=  0xA0; // Comparator Flag Register
sbit	CMP0IFR =  0xA0;
sbit	CMP1IFR =  0xA1;
sbit	CMP2IFR =  0xA2;
sbit	CMP3IFR =  0xA3;
sfr		CMPPOL	=	 0xE9; // Comparator Interrupt Polarity Register
sfr		CMPCR		=  0xEA; // Comparator Control Register
sfr		CMPNFCR	=	 0xEC; // Comparator Noise Filter Control Register
sfr		AMPCR		=	 0xEB; // Operational Amplifier Control Register

// Calculator Control
sfr		CALCR		=	 0xED; // Calculator Control Register
sfr		CALPTR	=	 0xEE; // Calculator Address Pointer
sfr		CALDR		=	 0xEF; // Calculator Data Register

// Flash Memory Control
sfr   FSADRH  =  0xFA; // Flash Sector Address High Register
sfr   FSADRM  =  0xFB; // Flash Sector Address Middle Register
sfr   FSADRL  =  0xFC; // Flash Sector Address Low Register
sfr   FIDR    =  0xFD; // Flash Identification Register
sfr   FMCR    =  0xFE; // Flash Mode Control Register

// CRC Control
sfr		FCDIN		=	 0xDF;
#ifndef   _ASSM_CODE_
#define   FCSARH   *(volatile unsigned char xdata*) 0x5050
#define   FCEARH   *(volatile unsigned char xdata*) 0x5051
#define   FCSARM   *(volatile unsigned char xdata*) 0x5052
#define   FCEARM   *(volatile unsigned char xdata*) 0x5053
#define   FCSARL   *(volatile unsigned char xdata*) 0x5054
#define   FCEARL   *(volatile unsigned char xdata*) 0x5055
#define   FCCR     *(volatile unsigned char xdata*) 0x5056
#define   FCDRH    *(volatile unsigned char xdata*) 0x5057
#define   FCDRL    *(volatile unsigned char xdata*) 0x5058
#else
FCSARH      xdata     0x5050 	// CRC Start Address High Register
FCEARH      xdata     0x5051	// CRC End Address High Register
FCSARM      xdata     0x5052 	// CRC Start Address Mid Register
FCEARM      xdata     0x5053  // CRC End Address Mid Register
FCSARL      xdata     0x5054 	// CRC Start Address Low Register
FCEARL      xdata     0x5055  // CRC End Address Low Register
FCCR        xdata     0x5056	// CRC Control Register
FCDRH       xdata     0x5057  // CRC Result Data High Register
FCDRL       xdata     0x5058	// CRC Result Data Low Register
#endif  	// _ASSM_CODE_

sfr   ACC     =  0xE0; 
sfr   B       =  0xF0; 
sfr   PSW     =  0xD0;
/*
sfr   CY      =  0xD7; // carry 
sfr   AC      =  0xD6; // aux carry
sfr   F0      =  0xD5; // user difinable flag0
sfr   RS1     =  0xD4; // register bank select
sfr   RS0     =  0xD3; //
sfr   OV      =  0xD2; // overflow
sfr   F1      =  0xD1; // user difinable flag1
sfr   P       =  0xD0; // parity
*/
sfr   SP      =  0x81;
sfr   DPL     =  0x82;
sfr   DPH     =  0x83;
sfr   DPL1    =  0x84;
sfr   DPH1    =  0x85;
sfr   EO      =  0xA2; // EXTENDED OPERATION REGISTER
#ifndef   _ASSM_CODE_
	sfr16	DPTR	  =  0x82;
	sfr16	DPTR1	  =  0x84;
#endif

#endif	//_MC96FD316_
