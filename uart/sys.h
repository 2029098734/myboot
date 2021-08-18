#ifndef __SYS_H
#define __SYS_H

#ifndef NULL
#define NULL   ( 0 )
#endif

#define uint8_t					char
#define uint32_t					unsigned int
#define SYSCTRL_BASE               (0x4001F000UL)
//#define PCLK_1MS_VAL			   (SYSCTRL_BASE + 0x30)
#define SCB_BASE           		   (0xE000ED00UL)                    /*!< System Control Block Base Address  */

typedef struct
{
    uint32_t FREQ_SEL;
    uint32_t CG_CTRL1;
    uint32_t CG_CTRL2;
    uint32_t SOFT_RST1;
    uint32_t SOFT_RST2;
    uint32_t LOCK_R;
    uint32_t PHER_CTRL;
	uint32_t SYS_RSVD[(0x2C-0x1C) >> 2];
    uint32_t HCLK_1MS_VAL;
    uint32_t PCLK_1MS_VAL;
    uint32_t ANA_CTRL;
    uint32_t DMA_CHAN;
    uint32_t SCI0_GLF;
    uint32_t SW_RSV1;
    uint32_t SW_RSV2;
    uint32_t CARD_RSVD;
    uint32_t LDO25_CR;
	uint32_t DMA_CHAN1;
    uint32_t SYS_RSVD2[(0x100-0x54) >> 2];
    uint32_t MSR_CR1;
    uint32_t MSR_CR2;
    uint32_t USBPHY_CR1;
    uint32_t USBPHY_CR2;
    uint32_t USBPHY_CR3;
	uint32_t ISO7816_CR;
	uint32_t LDO_CR;
	uint32_t CHG_CSR;
    uint32_t SYS_RSVD3[(0x204-0x120) >> 2];
    uint32_t RSVD_POR;
    uint32_t SYS_RSVD4[(0x3EC-0x208) >> 2];
    uint32_t PM2_WK_FLAG;
    uint32_t CALIB_CSR;
    uint32_t DBG_CR;
    uint32_t CHIP_ID;
}SYSCTRL_TypeDef;

typedef struct
{
	uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
	uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
	uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
	uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
	uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
	uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
	uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
	uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
	uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
	uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
	uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
	uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
	uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
	uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
	uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
	uint32_t ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
	uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
	uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
	uint32_t RESERVED0[5];
	uint32_t CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
} SCB_Type;


#define SCB                			((SCB_Type*) SCB_BASE)   /*!< SCB configuration struct           */
#define SYSCTRL 					((SYSCTRL_TypeDef *) SYSCTRL_BASE)
//#degine PCLK_1MS 					(*(uint32_t *)PCLK_1MS_VAL)            //初始值0x00005DC0

#endif