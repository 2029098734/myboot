#include"sys.h"

extern  unsigned int _estack;
extern  unsigned int __text_end__;
extern  unsigned int __data_start__;
extern  unsigned int __bss_start__;
extern  unsigned int __bss_end__;
extern  unsigned int __data_end__;
extern  int main(void);

typedef void (*Handler)(void);

typedef struct{
	// void* estack;
	//Handler vector[15];
	Handler vector;
} Vectors;

void Reset_Handler(void);

Vectors cortex_vectors = {
	// &_estack,
	// {
		// [0] = Reset_Handler,
		// [1] = NMI_Handler;
		// [2] = HardFault_Handler;
		// [3] = MemManage_Handler;
		// [4] = BusFault_Handler;
		// [5] = UsageFault_Handler;
		// [10] = SVC_Handler;
		// [11] = DebugMon_Handler;
		// [13] = PendSV_Handler;
		// [14] = SysTick_Handler;
	// }
	Reset_Handler,	
};


void Reset_Handler(void)
{
	unsigned int *flash, *ram;
	flash = &__text_end__;
	ram = &__data_start__;
	if(!(flash == ram))
	{
		for(;ram < &__data_end__;)
		{
			*ram = *flash;
			flash ++;
			ram ++;
		}
	}
	
	for(ram = &__bss_start__; ram < &__bss_end__; ram ++)
	{
		*ram = 0;
	}
	SYSCTRL->FREQ_SEL |=  0x200F395A;    //PLL:5'h0F 192MHz; 
	main();
}