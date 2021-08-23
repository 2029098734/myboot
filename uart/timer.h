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
#define TIMER1     			((TIM_TypeDef *) (TIMER0_BASE + 0x14))
#define TIMER2     			((TIM_TypeDef *) (TIMER0_BASE + 0x28))
#define TIMER3     			((TIM_TypeDef *) (TIMER0_BASE + 0x3c))

void delay_ms(uint32_t ms);
void inti_timer(TIM_TypeDef* timer);




#endif