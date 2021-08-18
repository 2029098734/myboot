#ifndef __TIMER_H
#define __TIMER_H

#include"sys.h"

#define TIMER0_BASE			(0x40013000UL)

typedef struct
{
    uint32_t LoadCount;
    uint32_t CurrentValue;
    uint32_t ControlReg;
    uint32_t EOI;
    uint32_t IntStatus;
} TIM_TypeDef;





#define TIMER0     			((TIM_TypeDef *) TIMER0_BASE)

void delay_ms(uint32_t ms);
void inti_timer(void);




#endif