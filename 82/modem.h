#ifndef __MODEM_H
#define __MODEM_H

#include"sys.h"

#define uint8_t					char
#define SOH                     ((uint8_t)0x01)   
#define STX                     ((uint8_t)0x02)   
#define EOT                     ((uint8_t)0x04)   
#define ACK                     ((uint8_t)0x06)   
#define NAK                     ((uint8_t)0x15)   
#define CAN                     ((uint8_t)0x18)  
#define CRC16                   ((uint8_t)0x43)   

typedef struct
{
	uint8_t Start;
	uint8_t Number;
	uint8_t Inverse_Number;
	uint8_t Data[128];
	uint8_t check_sum;
}Xmoden_Typedef;
void send(uint8_t oneBit);
uint8_t Check(Xmoden_Typedef* message,uint8_t* number);
uint8_t Xmoden(Xmoden_Typedef* message);


#endif