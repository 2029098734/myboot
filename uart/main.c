#include"uart.h"
#include"modem.h"
#include"timer.h"
#include"qspi.h"

int main(void)
{	
	UART_Init(UART1);
	inti_timer(TIMER0);
	inti_timer(TIMER1);
	inti_timer(TIMER2);
	inti_timer(TIMER3);
	NVIC->ISER[0] |= 0x1 << 9;
	TIMER0->LoadCount = SYSCTRL->PCLK_1MS_VAL*4000;	//设定三秒超时限制
	TIMER0->ControlReg = 0x00000003;
	NVIC->ISER[0] |= 0x1 << 10;
	TIMER1->LoadCount = SYSCTRL->PCLK_1MS_VAL*3000;	
	TIMER1->ControlReg = 0x00000003;
	NVIC->ISER[0] |= 0x1 << 11;
	TIMER2->LoadCount = SYSCTRL->PCLK_1MS_VAL*2000;	
	TIMER2->ControlReg = 0x00000003;
	NVIC->ISER[0] |= 0x1 << 12;
	TIMER3->LoadCount = SYSCTRL->PCLK_1MS_VAL*1000;
	TIMER3->ControlReg = 0x00000003;
	while(1)
	{
		if((UART1->LSR) & 0x1)
		{
			if((UART1->OFFSET_0.RBR == 0x63))
			{
				break;
			}
			while(((UART1->USR) & 0x1)){}
			UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
		} 
	}
	return 0;
}


/* if((UART0->LSR) & 0x1)
		{
			uint32_t mes = 0;
			mes= UART0->OFFSET_0.RBR;
			UART0->OFFSET_0.THR = mes + 1;
		} */

/* 	GPIOA_init();
	GPIOA->PUE = 0x0000FFFF;
	GPIOA->OEN = 0x00000000;
	GPIOA->IODR = 0x0000FF00;
	GPIOA->BSRR = 0x00000000; */