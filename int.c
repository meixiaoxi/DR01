 #include "common.h"

extern volatile INT8U gValidDetectFlag;
extern volatile INT32U gDetectHighCnt;
extern volatile INT32U gDetectLowCnt;
extern INT8U overflow;
extern volatile  INT8U gDetectOverflowCnt;
extern volatile INT32U gTempCnt;
extern INT8U dbgCnt;
void	EINT11_IRQHandler(void)	interrupt 11	using 1 
{
	// clear flag
	EIFLAG1 &= ~(0x1);

	
	switch(gValidDetectFlag)
	{
		case 0:
				gValidDetectFlag++;
				break;
		case 1:	
				gValidDetectFlag++;
				gDetectLowCnt = (INT32U)(T1BDR) + gTempCnt;
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x02;
				break;
		case 2:
				gDetectHighCnt = (INT32U)(T1BDR)+gTempCnt;
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x01;
				gValidDetectFlag = 1;
				break;
		default:
			gValidDetectFlag = 0;
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

	if(gDetectOverflowCnt++ > 80)
	{
		gDetectOverflowCnt = 0;
		gValidDetectFlag = 0;
		gDetectHighCnt = 0;
		gDetectLowCnt = 0;
		gTempCnt = 0;
	}
}

void TIMER2_IRQHandler(void) interrupt 15 using 1
{
	overflow = 1;

	T2CRL &= ~(0x10);
}

void CMP012_IRQHandler(void) interrupt 19 using 1
{	
	dbgCnt++;
	CMPFLAG = 0;
}
