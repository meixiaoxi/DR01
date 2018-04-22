#include "common.h"


INTU8 gValidDetectFlag = 0;
INTU16 gDetectHighCnt = 0;
INTU16 gDetectLowCnt = 0;


void pwm_set_duty(INTU16 duty)
{
	INTU16	duty16;
	
	duty16   = DCARRIER_SET-duty;
	
	T3ADR = duty16;
	T3BDR = duty16;
	T3CDR = duty16;
}
