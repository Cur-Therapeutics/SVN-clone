/********************************************************************
*
*   ospiflash.h
*
*   Description:    Manages the Octo-Spi Flash
*
*   Copyright NextPhase Medical, Inc. 2023 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 02/12/24  | Brian Compter     | Created.
*
********************************************************************/

#ifndef INC_OSPIFLASH_H_
#define INC_OSPIFLASH_H_

/**
 * Octospi flash state
 */
typedef enum
{
	FLASH_STATE_LEGACY,
	FLASH_STATE_OCTAL
} eOctoSpiFlashState;

/**
 * Flash sector size
 */
#define FLASH_SECTOR_SIZE			262144	// 2^18
#define OSPI_FLASH_PAGE_SIZE		256		// Max write size
#define FLASH_IMAGE_START_ADDRESS	(0)		// Start of Flash images

/**
 * Volatile Register Addresses
 */
#define OCTOSPIFLASH_REG_STATUS1	(0x00800000)
#define OCTOSPIFLASH_REG_STATUS2	(0x00800001)
#define OCTOSPIFLASH_REG_CFR1X		(0x00800002)
#define OCTOSPIFLASH_REG_CFR2X		(0x00800003)
#define OCTOSPIFLASH_REG_CFR3X		(0x00800004)
#define OCTOSPIFLASH_REG_CFR4X		(0x00800005)
#define OCTOSPIFLASH_REG_CFR5X		(0x00800006)

/**
 * Non-Volatile Register Addresses
 */
#define OCTOSPIFLASH_NV_REG_CFR1X	(0x00000002)
#define OCTOSPIFLASH_NV_REG_CFR2X	(0x00000003)
#define OCTOSPIFLASH_NV_REG_CFR3X	(0x00000004)
#define OCTOSPIFLASH_NV_REG_CFR4X	(0x00000005)
#define OCTOSPIFLASH_NV_REG_CFR5X	(0x00000006)

/**
 * OctoSpi Flash Manufacturer, device and unique IDs
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t manufactureId;
	uint8_t memInterface;
	uint8_t density;
	uint8_t idLen;
	uint8_t config;
	uint8_t family;
	uint64_t uniqueId;
} sFlashIds;

/**
 * Known good ID values
 */
#define FLASH_MANUFACTURE_ID	0x34
#define FLASH_FAMILY_ID			0x90

/**
 * Configuration register values
 */
#define FLASH_CFG1_TB4KBS		(0x04)
#define FLASH_CFG2_32ADDR_MODE	(0x80)
#define FLASH_CFG5_OCTAL_MODE	(0x41)


/**
 * OSPI Flash Code from AN5050
 */
/* Flash commands */
#define OCTAL_IO_DTR_READ_CMD 		0xEE11
#define OCTAL_IO_READ_CMD 			0xEC13
#define OCTAL_PAGE_PROG_CMD 		0x12ED
#define OCTAL_READ_STATUS_REG_CMD 	0x05FA
#define OCTAL_SECTOR_ERASE_CMD 		0x21DE
#define OCTAL_WRITE_ENABLE_CMD 		0x06F9
#define READ_STATUS_REG_CMD 		0x05
#define READ_STATUS2_REG_CMD 		0x07
#define READ_ANY_REGISTER			0x65
#define WRITE_ANY_REGISTER			0x71
#define WRITE_CFG_REG_2_CMD 		0x72
#define WRITE_ENABLE_CMD 			0x06
#define WRITE_DISABLE_CMD 			0x04
#define READ_DEVICE_ID				0x9F
#define READ_UNIQUE_ID				0x4C
#define ERASE_4K_SECTOR				0x21
#define ERASE_256K_SECTOR			0xDC
#define ERASE_CHIP					0x60
#define FLASH_READ_CMD				0x03
#define FLASH_WRITE_PAGE_CMD		0x12
#define FLASH_CLEAR_PROG_AND_ERRS	0x82
#define FLASH_RESET_ENABLE			0x66
#define FLASH_RESET_DEVICE			0x99

/* Dummy clocks cycles */
#define DUMMY_CLOCK_CYCLES_READ 	6
#define DUMMY_CLOCK_CYCLES_READ_REG 4

/* Auto-polling values */
#define WRITE_ENABLE_MATCH_VALUE 	0x02
#define WRITE_ENABLE_MASK_VALUE 	0x02
#define MEMORY_READY_MATCH_VALUE 	0x00
#define MEMORY_READY_MASK_VALUE 	0x01
#define AUTO_POLLING_INTERVAL 		0x10

/* Memory registers address */
#define CONFIG_REG2_ADDR1 			0x0000000
#define CR2_STR_OPI_ENABLE 			0x01
#define CR2_DTR_OPI_ENABLE 			0x02
#define CONFIG_REG2_ADDR3 			0x00000300
#define CR2_DUMMY_CYCLES_66MHZ 		0x07
/* Exported macro ------------------------------------------------------*/
#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__)/sizeof(*(__BUFFER__)))

/**
 * Functions, independent of flash operating mode
 */
void FlashInit(void);
void FlashReset(void);
void FlashGetIds(sFlashIds * ids);
eOctoSpiFlashState FlashGetState(void);

/**
 * Legacy 1S-1S-1S Functions
 */
void LegacyFlashReadJedec(void);
void LegacyFlashReadId(void);
uint8_t LegacyFlashReadSr1(void);
uint8_t LegacyFlashReadSr2(void);
uint8_t LegacyFlashReset(void);
void LegacyFlashWriteEnable(void);
void LegacyFlashWriteDisable(void);
uint8_t LegacyFlashWriteAnyRegister24(uint32_t reg, uint8_t val);
uint8_t LegacyFlashWriteAnyRegister(uint32_t reg, uint8_t val);
uint8_t LegacyFlashReadAnyRegister24(uint32_t reg, uint8_t * val, uint32_t dummyCycles);
uint8_t LegacyFlashReadAnyRegister(uint32_t reg, uint8_t * val, uint32_t dummyCycles);

/**
 * Octal 8S-8S-8S Functions
 */
void OctalFlashReadId(void);
uint8_t OctalFlashReadSr1(void);
uint8_t OctalFlashReadSr2(void);
uint8_t OctalFlashReset(void);
uint8_t OctalFlashReadAnyRegister(uint32_t reg, uint8_t * val, uint32_t dummyCycles);
uint8_t OctalFlashWriteAnyRegister(uint32_t reg, uint8_t val);
void OctalWriteEnable(void);

/**
 * To be sorted...
 */
void FlashClearProgramAndErrors(void);
void FlashRead(uint32_t addr, uint8_t * data, uint32_t count);
uint8_t FlashWrite(uint32_t addr, uint8_t * data, uint32_t count);

void OctalDTR_MemoryCfg(void);
void FlashSectorErase(uint32_t addr);
void FlashSectorEraseBase(uint32_t addr);
void FlashMassErase();
void OctalDTR_MemoryWrite(uint8_t *pData, uint32_t size);
void AutoPollingWIP(void);
void OctalPollingWEL(void);
void OctalPollingWIP(void);
uint8_t OctalSpiFlashErase4KSector(uint32_t addr);
uint8_t OctalSpiFlashErase256KSector(uint32_t addr);

/**
 * Externs
 */
extern OSPI_HandleTypeDef hospi2;

#endif /* INC_OSPIFLASH_H_ */
