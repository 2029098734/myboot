#include"timer.h"
#include"sys.h"

void inti_timer(void)
{
	SYSCTRL->CG_CTRL1 |= 1 << 21;
	TIMER0->ControlReg = 0x00000006;     
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