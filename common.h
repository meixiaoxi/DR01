#ifndef __COMMON_H__
#define __COMMON_H__
#include "MC96FD316.h"
typedef signed char	INT8S;
typedef signed short	INT16S;
typedef signed long	INT32S;

typedef unsigned char	INT8U;
typedef unsigned short	INT16U;
typedef unsigned long	INT32U;


#define uint8_t	unsigned char
#define uint16_t	unsigned short
#define uint32_t	unsigned long


typedef struct sysADC{
	INT16U tempAdc;
	INT16U vbusAdc;
	INT16U mainMotorAdc;
	INT16U viceMotorAdc;
	INT16U mainCurrAdc;
	INT16U viceCurrAdc;
}SYSADC;

/* Duty configuration */
#define DPWM_TIMER_FREQ     (20)         /* PWM timer frequency[MHz] */
#define DCARRIER_FREQ       (20)         /* carrier wave frequency[kHz] */
#define DSTART_DUTY         (17)         /* default duty[%] */

#define DCARRIER_SET        (1000 / DCARRIER_FREQ * DPWM_TIMER_FREQ - 1)             /* set value of carrier wave frequency */
#define DSTART_DUTY_SET     ((((DCARRIER_SET + 1) / 100) * DSTART_DUTY) - 1)         /* set value of default duty */



//-----------------------------------------------------------------------------
// Boolen
#define OFF	0
#define ON	1
#define LOW	0
#define HIGH	1

#define CW                      (0)         /* CW */
#define CCW                     (1)         /* CCW */

#define DI()                        EA = 0
#define EI()                        EA = 1

#define VALID_DETECT_FLAG_INIT	0
#define VALID_DETECT_FLAG_WAIT_FALL	1
#define VALID_DETECT_FLAG_WAIT_RISE	2


#define ADC_CH_VBUS			0	
#define ADC_CH_V_VICE_MOTOR	3
#define ADC_CH_TEMP			5
#define ADC_CH_V_MAIN_MOTOR	6
#define ADC_CH_VICE_CURR_DET	9
#define ADC_CH_MAIN_CURR_DET	10

#define SYS_RUN_MODE_STOP					0
#define SYS_RUN_MODE_STARTING				1
#define SYS_RUN_MODE_NORMAL				2
#define SYS_RUN_MODE_IN_CURR_PROTCET		3
#define SYS_RUN_MODE_IN_TEMP_PROTECT 	4
#define SYS_RUN_MODE_EMERGENCY_STOP		5
#define SYS_RUN_MODE_DEAD_END			6

#define SYS_PROTECT_FLAG_NORMAL	0
#define SYS_PROTECT_FLAG_CURRENT	0x01
#define SYS_PROTECT_FLAG_TEMP		0x02
#define SYS_PROTECT_FLAG_VBUS_UNDERVOLTTAGE	0x04

//adc
#define ADC_TEMP_103	274
#define ADC_TEMP_95	307

#define SET_OCP_TO_START_STATE() 	P15 = 0
#define SET_OCP_TO_NORMAL_STATE()	P15 = 1

void pwm_set_duty(INT16U duty);
void system_init(void);
void UARTPuts( const void *str);
void UARTPutDec16(uint16_t decnum);
void UARTPutDec32(uint32_t decnum);
uint16_t get_adc(uint8_t ad_ch);
void samplePwmInhandle();
void pwmOutputHandle();
void adcSampleHandle();
void sysProtectHandle();
void sysStatusHandle();
void dbgHandle();
#define DBG(x)	UARTPuts(x)
#define DBD16(x) UARTPutDec16(x)
#define DBD32(x) UARTPutDec32(x)
#endif
