#include"modem.h"
#include"uart.h"
#include"timer.h"
#include"qspi.h"

/*Xmodem协议流程如下
 ------------------------------------------------------------------------------
|               SENDER                |          |          RECIEVER         |
|                                     |  <---    |  NAK                      |
|                                     |          |  Time out after 3 second  |
|                                     |  <---    |  NAK                      |
| SOH|0x01|0xFE|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  NAK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x03|0xFC|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
|                                     |  <---    |  ACK                      |
| EOT                                 |  --->    |                           |
|                                     |  <---    |  ACK                      |
------------------------------------------------------------------------------ 
*/

void send(uint8_t oneBit)
{
	UART0->OFFSET_0.THR = oneBit;
}

//接收一包的数据,一包数据大小为132字节
uint8_t Receive(uint8_t* message)
{
	uint8_t i = 0;
	TIMER0->LoadCount = SYSCTRL->PCLK_1MS_VAL*3000 + 100;	//设定三秒超时限制
	TIMER0->ControlReg |= 0x00000001;
	while(i<132)
	{
		if((UART0->LSR) & 0x1)						//运算时钟频率大于UART传输频率,需要等待数据传输
		{
			*(message+i) = UART0->OFFSET_0.RBR;
			i++;
		}
		else if((i == 1) && (*(message) == EOT)) 	//发送方发送完成会发送EOT进行确认    
		{
			return EOT;
		}
		else if(TIMER0->CurrentValue <= 100)		//超时
		{
			break;
		}
	}
	TIMER0->ControlReg = 0x00000006;
	if(i == 132)
	{
		i = 0;
		return ACK;	
	}
	else if( i != 0)
	{
		return NAK;  								//传输发生错误未完整传输
	} 
	return SOH;										//未有数据传输
}

//对传输完成的数据进行校验
uint8_t Check(Xmoden_Typedef* message,uint8_t* number)
{
	if(message->Start != SOH)     					//包头
	{
		(*number) --;
		return NAK;
	}
	if(((message->Number) ^ (message->Inverse_Number)) != 0xFF || (message->Number) != (*number))	//包名
	{
		(*number) --;
		return NAK;
	}	
	//累加和校验
	uint8_t sum = 0;								 
	for(int i = 0;i<=127;i++)
	{
		sum += message->Data[i];
	}
	if(sum != message->check_sum)
	{
		(*number) --;
		return NAK;
	}
	return ACK;
}

//Xmodem传输函数,message:储存信息,flag:当前发送状态(NAK:开始传输或重新发送),times:对当前发送包的错误次数进行计数,大于三次则停止发送
uint8_t Xmoden(Xmoden_Typedef* message)
{
		static uint8_t flag = NAK;
		static uint8_t number = 0;
		static uint8_t times = 0;
		switch(flag)			//判断当前发送状态对times进行处理
		{
			case NAK:
				times ++;
				if(times > 3)
				{
					while(((UART0->USR) & 0x1)){}
					send(CAN);
					return CAN;
				}
				break;

			case ACK:
				times = 1;
				break;

			default:		//发送状态出错
				while(((UART0->USR) & 0x1)){}
				send(CAN);
				return CAN;
		}

		while(((UART0->USR) & 0x1)){}
		send(flag);
		switch(Receive(&(message->Start)))
		{
			case ACK:     //完整接收132字节数据
				number ++;
				flag =  Check(message,&number);	//根据校验结果得出下一发送状态
				return flag;

			case NAK:		//未完整接收132字节数据
				flag = 	NAK;
				return NAK;

			case SOH:		//未接收有数据,未开始传输时的状态
				times = 0;
				number = 0;
				flag = NAK;
				return SOH;

			case EOT:		//传输结束
				flag = NAK;
				times = 0;
				number = 0;
				flag = NAK;
				while(((UART0->USR) & 0x1)){}
				send(ACK);
				return EOT;

			default:		//传输出错,出现未定义值
				while(((UART0->USR) & 0x1)){}
				send(CAN);
				return CAN;
		}
	return 0;              //已完整传输完成一个文件
}

