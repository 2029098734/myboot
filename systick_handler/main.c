#include"uart.h"
#include"modem.h"
#include"timer.h"
#include"qspi.h"

int main(void)
{	
	SysTick->LOAD = (0x00FFFFFF & 0x927C00);
	SysTick->CTRL = 0x00000007; //使能系统时钟,使能中断,使用内部处理器时钟源
	UART_Init(UART1);
	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0x12;
	while(1)
	{
		if((UART1->LSR) & 0x1)
		{

			if((UART1->OFFSET_0.RBR == 0x73))
			{
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
				(*(void(*) ())(*((uint32_t*)(0x01006000))))();			//bin文件顶部为RESET,没有中断向量表(相当于函数调用)
			}
			UART1->OFFSET_0.THR = 0x00;
		} 
	}
	
}

void SysTick_Handler(void)
{
	static uint8_t timer_number = 20;
	if(timer_number > 0)
	{
		timer_number--;
	}
	else
	{
		while(((UART1->USR) & 0x1)){}
		UART1->OFFSET_0.THR = 0x10;
		timer_number = 20;
	}
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