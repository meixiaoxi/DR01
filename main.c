#include "common.h"

extern volatile INT32U gDetectHighCnt;
extern volatile INT32U gDetectLowCnt;
extern volatile INT8U gValidDetectFlag;
INT8U overflow = 0;
INT16U tick=0;


 void capture_start()
{
	T1CRH |=((1<<7)|(1<<0)); 
}
void main()
{
	DI();		
	system_init();


	//start
	EI();
	capture_start();

	DBG("\r\nSystem start!!!\r\n");


	do{
		overflow = 0;	

		samplePwmInhandle();
		adcSampleHandle();
		sysProtectHandle();
		sysStatusHandle();
		pwmOutputHandle();

		//dbgHandle();
		
		while(overflow==0){}   //10ms

	}while(1);
	
}
