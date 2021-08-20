#include"uart.h"
#include"modem.h"
#include"timer.h"
#include"qspi.h"

int main(void)
{	
	__asm__ volatile("cpsid i":::"memory"); //关中断	
	__asm__ volatile("cpsid f":::"memory"); //关异常
	//初始化外设
	inti_timer();                           //外设时钟
	UART_Init(UART0);						//UART通讯
	QSPI_Init(); 
	UART_Init(UART1);
	Xmoden_Typedef message;					//用于储存文件发送时一包的数据
	uint32_t address = 0x01005000;			//flash储存发送的bin文件的起始地址
	while(1)
	{
		if((UART1->LSR) & 0x1)				//通过UART1输入命令信息
		{
			if(UART1->OFFSET_0.RBR == 0x11)  //输出flash中储存的信息
			{
				UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
				uint32_t putAddress = 0x01005000;
				while(putAddress < address)	//从初始地址至现在的写入地址
				{
					while(((UART1->USR) & 0x1)){}
					UART1->OFFSET_0.THR = *((uint8_t*) putAddress);
					putAddress += 1;
				}
			}
			if((UART1->OFFSET_0.RBR == 0x73))	//结束Xmodem传输
			{
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
				break;
			}
			if((UART1->OFFSET_0.RBR == 0x01)) //从初始写入地址开始擦除128K区域,并开始传输
			{
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
				for(int i = 0;i < 32; i++)
				{
					FLASH_EraseSector((0x01005000 + i*FLASH_SECTOR_SIZE));
				}
				
				switch(Xmoden(&message))     //开始Xmodem传输
				{
					case ACK:        //传输完成一包数据后,将该包数据进行储存,并移动储存地址
							SaveInFlash(&(message.Data[0]),address);
							address += 0x80;
							/* while(((UART1->USR) & 0x1)){}
							UART1->OFFSET_0.THR = 0x13; */
						break;
					
					case EOT:		//传输完成后,初始化message(可省略),切换储存地址address;
							/* while(((UART1->USR) & 0x1)){}
							UART1->OFFSET_0.THR = 0x21;
							message.Start = 0;
							message.Number = 0;
							message.Inverse_Number = 0;
							message.check_sum = 0;
							for(int i = 0; i < 128; i++)
							{
								message.Data[i] = 0;
							} */
							address = (address & 0xFFFFF000) + 0x1000;
						break;
					
					default:
						break;
				} 
			}
		} 
	}	
	__asm__ volatile("cpsie i":::"memory"); //开中断	
	__asm__ volatile("cpsie f":::"memory"); //开异常
	SCB->VTOR = 0x01005000;
	__asm__ volatile ("dsb");								//数据同步屏障,确保之后使用新设置的向量表
	(*(void(*) ())(*((uint32_t*)(0x01005000 + 0x4))))();    //第一个32位数据为栈顶指针,第二个为复位函数,跳转至复位函数
}
