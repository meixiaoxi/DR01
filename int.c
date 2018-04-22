 #include "common.h"

extern INTU8 gValidDetectFlag;
extern INTU16 gDetectHighCnt;
extern INTU16 gDetectLowCnt;

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
				gDetectHighCnt = T1BDR;
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x02;
				break;
		case 2:
				gDetectLowCnt = T1BDR;
				EIPOL1 &= ~(0x03);
				EIPOL1 |= 0x01;
				gValidDetectFlag = 1;
				break;
	}
}


void TIMER1_IRQHandler(void) interrupt 14 using 1
{
	// clear flag
	T1CRL &= ~(0x10);

	gValidDetectFlag = 0;
	gDetectHighCnt = 0;
	gDetectLowCnt = 0;
}