#include "common.h"


volatile INT8U gValidDetectFlag = 0;
volatile INT32U gDetectHighCnt = 0;
volatile INT32U gDetectLowCnt = 0;
volatile INT32U gTempCnt = 0;
volatile INT8U gDetectOverflowCnt = 0;

// 采样到的最新输入PWM频率
INT8U sampleDuty = 10;    

//  根据采样频率或者系统的保护状态，综合算出的运行频率
INT8U resultDuty=0;		

//  当前运行的输出PWM频率
INT8U currDuty = 0;

// 当前频率运行持续的时间。用于缓启动
INT8U pwmKeepCnt =0 ;
INT8U sampleCnt=0;
INT8U sampleInterval=0;

void pwm_set_duty(INT16U duty)
{
	INT16U	duty16;

	duty16 = ((DCARRIER_SET + 1) / 100) * duty;
	
	//duty16   = DCARRIER_SET-duty16-1;
	
	T3ADR = duty16;
	T3BDR = duty16;
}



void pwmOutputHandle()
{
	if(currDuty != 0)
	{
		if(currDuty != resultDuty)
		{
			if(pwmKeepCnt++ >5)
			{
				if(currDuty > resultDuty)
					currDuty--;
				else
					currDuty++;
				pwm_set_duty(currDuty);
				pwmKeepCnt = 0;
			}
		}
	}
	else if(resultDuty!=0)
	{
		currDuty = 5;
		pwm_set_duty(currDuty);
		pwmKeepCnt = 0;
	}
}

void samplePwmInhandle()
{
	static INT32U dbgA=0,dbgB=0;
	INT16U dbgAdc;

		if(sampleInterval++ >= 10)
		{
			DI();
			dbgA += gDetectLowCnt;
			dbgB += gDetectHighCnt;
			EI();
			sampleCnt++;
			sampleInterval= 0;
		}
	
		if(sampleCnt == 8)
		{
			sampleCnt = 0;
			dbgA >>=3;
			dbgB >>=3;
			dbgAdc = get_adc(ADC_CH_TEMP);
			DBG("\r\ntemp:");DBD16(dbgAdc);
			dbgAdc = get_adc(ADC_CH_VBUS);
			DBG(" vbus:");DBD16(dbgAdc);DBG("\r\n");
			DBG("\r\nhighcnt:\r\n");DBD32(dbgA);
			DBG("\r\nlowcnt:\r\n");DBD32(dbgB);
			if((dbgA+dbgB) !=0)
			{
				sampleDuty = ((dbgB<<6)+(dbgB<<5)+(dbgB<<2))/(dbgB+dbgA);
			}
			else
			{
				sampleDuty = 0;
			}

			if((sampleDuty >=12) && (sampleDuty <= 85))
			{
				// y=(0.82)*x + 22
				resultDuty = (sampleDuty>>1)+(sampleDuty>>2 )+(sampleDuty>>3)+22;
			}
			else if(((sampleDuty>0) &&(sampleDuty<=5)) ||(sampleDuty >85))
			{
				resultDuty = 100;
			}
			else
			{
				resultDuty = 0;
			}
		
			DBG("\r\ndbgcnt:\r\n");DBD16(sampleDuty);DBG("\r\n");
	
		}	
}