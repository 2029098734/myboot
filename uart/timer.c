#include"timer.h"
#include"sys.h"

void inti_timer(TIM_TypeDef* timer)
{
	SYSCTRL->CG_CTRL1 |= 1 << 21;
	if(timer == TIMER0)
	{
		TIMER0->ControlReg = 0x00000006;  //不使能timer,用户模式.中断屏蔽,pwm模式关
	} 
	if(timer == TIMER1)
	{
		TIMER1->ControlReg = 0x00000006;  
	}
	if(timer == TIMER2)
	{
		TIMER2->ControlReg = 0x00000006;  
	}
	if(timer == TIMER3)
	{
		TIMER3->ControlReg = 0x00000006;  
	}
	    
}

void delay_ms(uint32_t ms)
{
	for(;ms>0;ms--)
	{	
		TIMER0->LoadCount = SYSCTRL->PCLK_1MS_VAL+100;
		TIMER0->ControlReg |= 0x00000001; 
		while(TIMER0->CurrentValue >100){};
		TIMER0->ControlReg = 0x00000006; 
	}
}