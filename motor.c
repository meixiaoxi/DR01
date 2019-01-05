#include "common.h"

volatile INT8U gValidDetectFlag = 0;
volatile INT32U gDetectHighCnt = 0;
volatile INT32U gDetectLowCnt = 0;
volatile INT32U gTempCnt = 0;
volatile INT8U gDetectOverflowCnt = 0;

//系统当前运行的状态
volatile INT8U gSysRunMode = SYS_RUN_MODE_STOP;
// 系统当前运行时常
volatile INT16U gSysRunTimeCnt = 0;
//当前系统的各保护状态
volatile INT8U gSysProtectStatus = SYS_PROTECT_FLAG_NORMAL;
// 保护状态持续的时间
volatile INT8U gSysProtectCount = 0;

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


//异常之后的尝试次数
volatile INT8U gAbnormalTryCnt = 0;

//降duty之后的观察时间
volatile INT8U gDnDutyKeepCnt = 0;
volatile INT8U gDnDutyState = 0;


extern SYSADC gSysAdc;
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
	/*
	if(currDuty != 0)
	{
		if(currDuty != resultDuty)
		{
			if(pwmKeepCnt++ >10)
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
	*/
	if(resultDuty != 0)
	{
		if(currDuty != resultDuty)
		{
			if(pwmKeepCnt++ >10)
			{
				if(currDuty > resultDuty)
					currDuty--;
				else
				{
					currDuty++;
					if(currDuty < 10)
						currDuty = 10;
				}
				//pwm_set_duty(currDuty);
				pwmKeepCnt = 0;
			}
		}
	}
	else
		currDuty = 0;
	if(gSysProtectStatus)
	{
		if(currDuty > resultDuty)
			currDuty = resultDuty;
	}
	pwm_set_duty(currDuty);
	//if(currDuty == 0)
	//	gSysRunMode = SYS_RUN_MODE_STOP;
}

void samplePwmInhandle()
{
	static INT32U dbgA=0,dbgB=0;
	INT16U dbgAdc;
	INT8U avgCnt = 8;  // 采样多次做平均

		if(gSysRunMode == SYS_RUN_MODE_STOP)
		{
			avgCnt = 3;
		}

		if(sampleInterval++ >= 10)
		{
			DI();
			dbgA += gDetectLowCnt;
			dbgB += gDetectHighCnt;
			EI();
			sampleCnt++;
			sampleInterval= 0;
		}
	
		if(sampleCnt == avgCnt)
		{
			sampleCnt = 0;
			dbgA >>=3;
			dbgB >>=3;
/*			dbgAdc = get_adc(ADC_CH_TEMP);
			DBG("\r\ntemp:");DBD16(dbgAdc);
			dbgAdc = get_adc(ADC_CH_VBUS);
			DBG(" vbus:");DBD16(dbgAdc);DBG("\r\n");
			DBG("\r\nhighcnt:\r\n");DBD32(dbgA);
			DBG("\r\nlowcnt:\r\n");DBD32(dbgB);
	*/
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
				resultDuty = 95;
			}
			else
			{
				resultDuty = 0;
			}
			
		
	//		DBG("\r\ndbgcnt:\r\n");DBD16(sampleDuty);DBG("\r\n");
	
		}	
}



void sysStatusHandle()
{
	switch(gSysRunMode)
	{
		case SYS_RUN_MODE_STOP:
			if(resultDuty != 0)
			{
				gSysRunTimeCnt = 0;
				gSysRunMode = SYS_RUN_MODE_STARTING;
				SET_OCP_TO_START_STATE();
			}
			break;
		case SYS_RUN_MODE_STARTING:
			if(gSysRunTimeCnt++ > 800)  
			{
				gSysRunTimeCnt = 0;
				gSysRunMode = SYS_RUN_MODE_NORMAL;
				gAbnormalTryCnt = 0;
				SET_OCP_TO_NORMAL_STATE();
			}
			break;
		case SYS_RUN_MODE_NORMAL:
			break;
		case SYS_RUN_MODE_IN_CURR_PROTCET:
			if(gSysRunTimeCnt++ > 800)
			{
				SET_OCP_TO_NORMAL_STATE();
			}
			break;
		case SYS_RUN_MODE_IN_TEMP_PROTECT:
			if(gSysRunTimeCnt++ > 800)
			{
				SET_OCP_TO_NORMAL_STATE();
			}
			break;
		case SYS_RUN_MODE_EMERGENCY_STOP:
			if(gSysProtectCount++ > 200)   // 2S
			{
				if(gAbnormalTryCnt >3)
					gSysRunMode = SYS_RUN_MODE_DEAD_END;
				else
				{
					gSysProtectCount = 0;
					gSysProtectStatus = 0;
					gSysRunMode = SYS_RUN_MODE_STOP;
				}
			}
			resultDuty = 0;
			break;
		case SYS_RUN_MODE_DEAD_END:
			resultDuty = 0;
			break;
	}
}

void sysProtectHandle()
{
	if(gSysRunMode == SYS_RUN_MODE_STOP || gSysRunMode == SYS_RUN_MODE_DEAD_END || gSysRunMode== SYS_RUN_MODE_EMERGENCY_STOP)
	{
		return;
	}
	// vbus  9~15V
	//if(gSysAdc.vbusAdc > 512 || gSysAdc.vbusAdc < 307)
	if(gSysAdc.vbusAdc > 512)
	{
	//	gSysRunMode = SYS_RUN_MODE_EMERGENCY_STOP;
		resultDuty = 0;
	}
	else if(gSysAdc.vbusAdc < 307)
	{
		resultDuty = 0;
	}
	// cmp protect
	else
	{
	if(gSysProtectStatus & SYS_PROTECT_FLAG_CURRENT)
	{
		if((gSysProtectCount == 0) ||(gSysProtectCount >= 20))
		{
			if(resultDuty > 20)
			{
				resultDuty -= 20;
				gSysRunMode = SYS_RUN_MODE_IN_CURR_PROTCET;
			}
			else
			{
				gSysRunMode = SYS_RUN_MODE_EMERGENCY_STOP;
				resultDuty = 0;
				gAbnormalTryCnt++;
			}

			gSysProtectCount = 1;
		}
		else
			gSysProtectCount++;
	}
//	if(gSysProtectStatus & SYS_PROTECT_FLAG_TEMP)
	{
		if(gSysAdc.tempAdc < ADC_TEMP_103)
		{
			resultDuty = 0;
			gSysProtectStatus |= SYS_PROTECT_FLAG_TEMP;
		}
		else if(gSysAdc.tempAdc <ADC_TEMP_95)
		{
			gSysProtectStatus |= SYS_PROTECT_FLAG_TEMP;
			if((gSysProtectStatus & SYS_PROTECT_FLAG_CURRENT) == 0)
			{
				if(resultDuty)
				{
					resultDuty >>=1;
				}
			}
		}
		else
		{
			gSysProtectStatus &= ~(SYS_PROTECT_FLAG_TEMP);
		}
	}
	}
	
}