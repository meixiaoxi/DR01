#include "common.h"

extern volatile INT32U gDetectHighCnt;
extern volatile INT32U gDetectLowCnt;
extern volatile INT8U gValidDetectFlag;
INT8U overflow = 0;
INT8U tick=0;
INT8U duty = 10;
INT8U dbgCnt =0 ;
 void capture_start()
{
	T1CRH |=((1<<7)|(1<<0)); 
}

void main()
{
	INT32U dbgA,dbgB;
	DI();		
	system_init();


	//start
	EI();
	capture_start();

	DBG("\r\nSystem start!!!\r\n");


	do{
		overflow = 0;
		
		if(tick++ > 100)
		{
			DI();
			dbgA = gDetectLowCnt;
			dbgB = gDetectHighCnt;
			EI();
			
			tick = 0;
			DBG("\r\nhighcnt:\r\n");DBD32(dbgA);
			DBG("\r\nlowcnt:\r\n");DBD32(dbgB);
			duty = ((dbgB<<6)+(dbgB<<5)+(dbgB<<2))/(dbgB+dbgA);
			DBG("\r\ndbgcnt:\r\n");DBD16(duty);DBG("\r\n");
	
			pwm_set_duty(duty++);
			if(duty>=100)
				duty = 10;
		}
			
		while(overflow==0){}
		
		}while(1);
	
}
