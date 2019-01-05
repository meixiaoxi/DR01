 #include "common.h"

extern volatile INT8U gValidDetectFlag;
extern volatile INT32U gDetectHighCnt;
extern volatile INT32U gDetectLowCnt;
extern INT8U overflow;
extern volatile  INT8U gDetectOverflowCnt;
extern volatile INT32U gTempCnt;
extern volatile INT8U gSysProtectCount;
extern volatile INT8U gSysProtectStatus;
void	EINT11_IRQHandler(void)	interrupt 11	using 1 
{
	// clear flag
	EIFLAG1 &= ~(0x1);

	
	switch(gValidDetectFlag)
	{
		case 0:
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x01;
				gValidDetectFlag = VALID_DETECT_FLAG_WAIT_RISE;
				break;
		case VALID_DETECT_FLAG_WAIT_RISE:	
				gValidDetectFlag = VALID_DETECT_FLAG_WAIT_FALL;
				gDetectHighCnt = (INT32U)(T1BDR) + gTempCnt;
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x02;
				break;
		case VALID_DETECT_FLAG_WAIT_FALL:
				gDetectLowCnt = (INT32U)(T1BDR)+gTempCnt;
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x01;
				gValidDetectFlag = VALID_DETECT_FLAG_WAIT_RISE;
				break;
		default:
			EIPOL1 &= ~(0x03);
			EIPOL1 |= 0x01;
			gValidDetectFlag = VALID_DETECT_FLAG_INIT;
			break;
	}
	gDetectOverflowCnt = 0;
	gTempCnt = 0;
}


void TIMER1_IRQHandler(void) interrupt 14 using 1
{
	// clear flag
	T1CRL &= ~(0x10);

	gTempCnt+=65535;

	//if((gDetectOverflowCnt++ > 80) && (gValidDetectFlag != VALID_DETECT_FLAG_INIT))
	if(gDetectOverflowCnt++ > 80) 
	{
		gDetectHighCnt = 0;
		gDetectLowCnt = 0;
		gDetectOverflowCnt = 0;
		gTempCnt = 0;
		
		//if(gValidDetectFlag == VALID_DETECT_FLAG_WAIT_RISE)
		if(P24 == 1)
		{
			gDetectHighCnt = 1;   // duty is 100%
		}
		
		gValidDetectFlag = VALID_DETECT_FLAG_INIT;
	}
}

void TIMER2_IRQHandler(void) interrupt 15 using 1
{
	overflow = 1;

	T2CRL &= ~(0x10);
}

void CMP012_IRQHandler(void) interrupt 19 using 1
{	
	CMPFLAG = 0;
	gSysProtectCount = 0;
	if(gSysProtectStatus & SYS_PROTECT_FLAG_CURRENT)
	{
		gSysProtectStatus  &= ~(SYS_PROTECT_FLAG_CURRENT);
		CMPPOL = 0x05;
	}
	else
	{
		gSysProtectStatus  |= (SYS_PROTECT_FLAG_CURRENT);
		CMPPOL = 0x0A;
	}
}
