/********************************************************************
*
*   flashspi.h
*
*   Description:    Provides commuications and access to a S25FL128
*   				serial flash.
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 04/14/26  | Brian Compter     | Created.
*
********************************************************************/

#ifndef INC_FLASHSPI_H_
#define INC_FLASHSPI_H_

/**
 * Chip select and reset Ports and pins
 */
#define CS_PORT        GPIOB
#define CS_PIN         GPIO_PIN_9
#define RST_PORT       GPIOD
#define RST_PIN        GPIO_PIN_5

/**
 * Commands
 */
#define READ_STATUS_1					0x05
#define READ_STATUS_2					0x07
#define READ_DEV_ID						0x9F
#define READ_CONF_REG_1					0x35
#define READ_CONF_REG_2					0x15
#define READ_CONF_REG_3					0x33

#define READ_ANY_REG					0x65

#define WRITE_ENABLE					0x06
#define WRITE_DISABLE					0x04

#define CLEAR_STATUS_REG				0x30
#define ENTER_FOUR_BYTE_ADDRESS_MODE	0xB7

#define READ_RAM						0x03

#define PAGE_PROGRAM					0x02

#define ERASE_SECTOR					0x20
#define ERASE_HALF_BLOCK				0x52
#define ERASE_BLOCK						0xD8

/**
 * Page size in bytes
 * The size allowed to program
 */
#define SPIFLASH_PAGE_SIZE (256)

/**
 * Expected DevId/Manufacturing ID values
 */
#define FLASH_DEV_ID_BYTE0	(0x01)
#define FLASH_DEV_ID_BYTE1	(0x60)
#define FLASH_DEV_ID_BYTE2	(0x18)

#define SPIFLASH_DEVID_SIZE (3)

/**
 * Manufacturer and device id
 */
typedef struct
{
	uint8_t manufacturerId;
	uint8_t interfaceType;
	uint8_t density;
} sDeviceId;

/**
 * Functions
 */
void FlashSpiInit(void);

uint8_t SpiFlashSendCommand(uint8_t * cmd);

uint8_t SpiFlashReadStatus1(uint8_t * val);
uint8_t SpiFlashReadStatus2(uint8_t * val);

uint8_t SpiFlashReadConfig1(uint8_t * val);
uint8_t SpiFlashReadConfig2(uint8_t * val);
uint8_t SpiFlashReadConfig3(uint8_t * val);

uint8_t SpiFlashReadDeviceId(sDeviceId * devId);
uint8_t SpiFlashReadAnyRegister(uint32_t reg, uint8_t * val);
uint8_t SpiFlashWriteAnyRegister24(uint32_t reg, uint8_t val);
uint8_t SpiFlashWriteAnyRegister(uint32_t reg, uint8_t val);
uint8_t SpiFlashSetWriteEnable(void);
uint8_t SpiFlashClearWriteEnable(void);
void SpiFlashReset(void);

void FlashSpiTest(void);

uint8_t SpiFlashReadArray(uint32_t addr, uint8_t * data, uint16_t size);
uint8_t SpiFlashProgramPage(uint32_t addr, uint8_t * data, uint16_t size);
uint8_t SpiFlashEraseSector(uint32_t addr);
uint8_t SpiFlashEraseHalfBlock(uint32_t addr);
uint8_t SpiFlashEraseBlock(uint32_t addr);
uint8_t SpiFlashEraseChip();

#endif /* INC_FLASHSPI_H_ */
