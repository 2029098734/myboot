#include"qspi.h"
#include"sys.h"


void QSPI_Init(void)
{ 
	SYSCTRL->CG_CTRL2 |= 1<<29;
	SYSCTRL->LOCK_R &= ~(1<<29 & 0xF0000000);
	SYSCTRL->SOFT_RST2 |= 1<<29;
	SYSCTRL->LOCK_R |= (1<<29 & 0xF0000000);
	QSPI->DEVICE_PARA = ((QSPI->DEVICE_PARA & ~0xFF) | 0x406B);
    QSPI->DEVICE_PARA = (QSPI->DEVICE_PARA & 0xFFFF) | ((96000000*2/1000000) << 16);  
}

uint8_t FLASH_EraseSector(uint32_t sectorAddress)
{
	CACHE_CleanAll(CACHE);
	return ROM_QSPI_EraseSector(NULL, sectorAddress);
}

void CACHE_CleanAll(CACHE_TypeDef *Cache)
{
	while (Cache->CACHE_CS & 0x20000000);
	Cache->CACHE_REF = 0x40000000;
	Cache->CACHE_REF |= 0x80000000;
	while ((Cache->CACHE_REF & 0x80000000));	
}

uint8_t FLASH_ProgramPage(uint32_t addr, uint32_t size, uint8_t *buffer)
{
/* 	QSPI_CommandTypeDef cmdType;
    
    cmdType.Instruction = 0x32;
    cmdType.BusMode = QSPI_BUSMODE_114;	      
    cmdType.CmdFormat = 0x0D;      */
	
    return ROM_QSPI_ProgramPage(NULL, NULL, addr, size, buffer);
}



uint32_t SaveInFlash(uint8_t* data)
{
	static uint32_t address = 0x01005000;
	CACHE_CleanAll(CACHE);
	FLASH_ProgramPage(address, 128, data);
	address += X25Q_PAGE_SIZE/2; 
	return address;
}



