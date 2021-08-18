#ifndef __GSPI_H
#define __GSPI_H

#include"sys.h"

#define FLASH_START_ADDR 	   				 (0x1010000U)
#define FLASH_SECTOR_SIZE 	   				 (0x1000)
#define CACHE_BASE 	    					 (0x40080000)
#define DMA_BASE 	    					 (0x40000800)
#define X25Q_PAGE_SIZE				         (0x100)   


typedef struct
{
    uint32_t SAR_L;
    uint32_t SAR_H;
    uint32_t DAR_L;
    uint32_t DAR_H;
    uint32_t LLP_L;
    uint32_t LLP_H;
    uint32_t CTL_L;
    uint32_t CTL_H;
    uint32_t SSTAT_L;
    uint32_t SSTAT_H;
    uint32_t DSTAT_L;
    uint32_t DSTAT_H;
    uint32_t SSTATAR_L;
    uint32_t SSTATAR_H;
    uint32_t DSTATAR_L;
    uint32_t DSTATAR_H;
    uint32_t CFG_L;
    uint32_t CFG_H;
    uint32_t SGR_L;
    uint32_t SGR_H;
    uint32_t DSR_L;
    uint32_t DSR_H;
} DMA_TypeDef;


typedef enum
{
	QSPI_BUSMODE_111 = 0x00,	//CMD-ADDR-DATA = 1-1-1
	QSPI_BUSMODE_114 = 0x01,	//CMD-ADDR-DATA = 1-1-4
	QSPI_BUSMODE_144 = 0x02,	//CMD-ADDR-DATA = 1-4-4
	QSPI_BUSMODE_444 = 0x03,	//CMD-ADDR-DATA = 4-4-4
}QSPI_BusModeTypeDef;


typedef enum
{
	QSPI_CMDFORMAT_CMD8							= 0x00,
	QSPI_CMDFORMAT_CMD8_RREG8					= 0x01,
	QSPI_CMDFORMAT_CMD8_RREG16					= 0x02,
	QSPI_CMDFORMAT_CMD8_RREG24					= 0x03,
	QSPI_CMDFORMAT_CMD8_DMY24_WREG8			    = 0x04,
	QSPI_CMDFORMAT_CMD8_ADDR24_RREG8			= 0x05,
	QSPI_CMDFORMAT_CMD8_ADDR24_RREG16			= 0x06,
	QSPI_CMDFORMAT_CMD8_WREG8					= 0x07,
	QSPI_CMDFORMAT_CMD8_WREG16					= 0x08,
	QSPI_CMDFORMAT_CMD8_ADDR24					= 0x09,
	QSPI_CMDFORMAT_CMD8_ADDR24_RDAT			    = 0x0A,
	QSPI_CMDFORMAT_CMD8_ADDR24_DMY_RDAT		    = 0x0B,
	QSPI_CMDFORMAT_CMD8_ADDR24_M8_DMY_RDAT   	= 0x0C,
	QSPI_CMDFORMAT_CMD8_ADDR24_PDAT			    = 0x0D
}QSPI_CmdFormatTypeDef;

typedef struct
{
    uint32_t FCU_CMD;
    uint32_t ADDRES;
    uint32_t BYTE_NUM;
    uint32_t WR_FIFO;
    uint32_t RD_FIFO;
    uint32_t DEVICE_PARA;
    uint32_t REG_WDATA;
    uint32_t REG_RDATA;
    uint32_t INT_MASK;
    uint32_t INT_UMASK;
    uint32_t INT_MASK_STATUS;
    uint32_t INT_STATUS;
    uint32_t INT_RAWSTATUS;
    uint32_t INT_CLEAR;
    uint32_t CACHE_INTF_CMD;
    uint32_t DMA_CNTL;
    uint32_t FIFO_CNTL;
} QSPI_TypeDef;

typedef struct
{
    uint32_t CACHE_I0;
    uint32_t CACHE_I1;
    uint32_t CACHE_I2;
    uint32_t CACHE_I3;
    uint32_t CACHE_K0;
    uint32_t CACHE_K1;
    uint32_t CACHE_K2;
    uint32_t CACHE_K3;
    uint32_t CACHE_CS;
    uint32_t CACHE_REF;
    uint32_t CACHE_RSVD0[(0x40-0x28) >> 2];
    uint32_t CACHE_CONFIG;
	uint32_t CACHE_RSVD1[(0x74-0x44) >> 2];
    uint32_t CACHE_SADDR;
    uint32_t CACHE_EADDR;		
} CACHE_TypeDef;

typedef struct
{
	uint8_t Instruction;       
	QSPI_BusModeTypeDef BusMode;
	QSPI_CmdFormatTypeDef CmdFormat;
	
}QSPI_CommandTypeDef;


#define ROM_QSPI_Init                        (*((void (*)(QSPI_InitTypeDef *))(*(uint32_t *)0x8010)))
#define ROM_QSPI_ReadID                      (*((uint32_t (*)(QSPI_CommandTypeDef *))(*(uint32_t *)0x8014)))
#define ROM_QSPI_WriteParam                  (*((uint8_t (*)(QSPI_CommandTypeDef *, uint16_t))(*(uint32_t *)0x8018)))
#define ROM_QSPI_EraseSector                 (*((uint8_t (*)(QSPI_CommandTypeDef *, uint32_t))(*(uint32_t *)0x801C)))
#define ROM_QSPI_ProgramPage                 (*((uint8_t (*)(QSPI_CommandTypeDef *, DMA_TypeDef *, uint32_t, uint32_t, uint8_t *))(*(uint32_t *)0x8024)))
#define ROM_QSPI_ReleaseDeepPowerDown        (*((uint8_t (*)(QSPI_CommandTypeDef *))(*(uint32_t *)0x802C)))
#define ROM_QSPI_StatusReg                   (*((uint16_t (*)(QSPI_CommandTypeDef *))(*(uint32_t *)0x8034)))


#define DMA                                     ((DMA_MODULE_TypeDef *)DMA_BASE)
#define DMA_Channel_0                           ((DMA_TypeDef *)DMA_BASE)
#define DMA_Channel_1                           ((DMA_TypeDef *)(DMA_BASE + 0x58))
#define DMA_Channel_2                           ((DMA_TypeDef *)(DMA_BASE + 0x58*2))
#define DMA_Channel_3                           ((DMA_TypeDef *)(DMA_BASE + 0x58*3))
#define DMA_Channel_4                           ((DMA_TypeDef *)(DMA_BASE + 0x58*4))
#define DMA_Channel_5                           ((DMA_TypeDef *)(DMA_BASE + 0x58*5))
#define DMA_Channel_6                           ((DMA_TypeDef *)(DMA_BASE + 0x58*6))
#define DMA_Channel_7                           ((DMA_TypeDef *)(DMA_BASE + 0x58*7))


#define QSPI                                    ((QSPI_TypeDef *) 0x400A2000UL)
#define CACHE                                   ((CACHE_TypeDef *)CACHE_BASE)

void QSPI_Init(void);
uint8_t FLASH_EraseSector(uint32_t sectorAddress);
void CACHE_CleanAll(CACHE_TypeDef *Cache);
uint8_t FLASH_ProgramPage(uint32_t addr, uint32_t size, uint8_t *buffer);
uint32_t SaveInFlash(uint8_t* data);

#endif