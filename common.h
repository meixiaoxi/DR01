#ifndef __COMMON_H__
#define __COMMON_H__
#include "MC96FD316.h"
typedef signed char	INTS8;
typedef signed short	INTS16;
typedef signed long	INTS32;

typedef unsigned char	INTU8;
typedef unsigned short	INTU16;
typedef unsigned long	INTU32;


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


void system_init(void);
#endif
