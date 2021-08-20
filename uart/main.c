#include"uart.h"
#include"modem.h"
#include"timer.h"
#include"qspi.h"

int main(void)
{	
	UART_Init(UART1);
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