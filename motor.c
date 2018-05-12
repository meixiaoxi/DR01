#include "common.h"


volatile INT8U gValidDetectFlag = 0;
volatile INT32U gDetectHighCnt = 0;
volatile INT32U gDetectLowCnt = 0;
volatile INT32U gTempCnt = 0;
volatile INT8U gDetectOverflowCnt = 0;

void pwm_set_duty(INT16U duty)
{
	INT16U	duty16;

	duty16 = ((DCARRIER_SET + 1) / 100) * duty;
	
	duty16   = DCARRIER_SET-duty16-1;
	
	T3ADR = duty16;
	T3BDR = duty16;
}
