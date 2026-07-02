/********************************************************************
*
*   flashspi.c
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

#include "main.h"
#include "flashspi.h"
#include "spi.h"

/**
 * @brief Initialize the S25FL128 device for use and check communication
 * @return None
 */
void FlashSpiInit()
{
	// Reset the chip so we know where we are startinf from
	SpiFlashReset();


	SpiDeSelect(&sSpiFlash);

	HAL_Delay(50);

	// Clear status
	SpiFlashSendCommand(CLEAR_STATUS_REG);

	// Enter four byte address mode
	SpiFlashSendCommand(ENTER_FOUR_BYTE_ADDRESS_MODE);
}

/**
 * @brief Send a one byte command to the spi flash
 * @param cmd The command to send
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashSendCommand(uint8_t * cmd)
{
	SpiSelect(&sSpiFlash);
	SpiWrite(&sSpiFlash, cmd, 1);
	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 * @brief Read Status Register 1
 * @param val Pointer to where to place the read data
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashReadStatus1(uint8_t * val)
{
	uint8_t cmd = READ_STATUS_1;
	SpiSelect(&sSpiFlash);

	SpiWrite(&sSpiFlash, &cmd, 1);
	SpiRead(&sSpiFlash, val, 1);

	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 * @brief Read Status Register 2
 * @param val Pointer to where to place the read data
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashReadStatus2(uint8_t * val)
{
	uint8_t cmd = READ_STATUS_2;
	SpiSelect(&sSpiFlash);

	SpiWrite(&sSpiFlash, &cmd, 1);
	SpiRead(&sSpiFlash, val, 1);

	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 * @brief Read configuration register 1
 * @param val Pointer to where to place the read data
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashReadConfig1(uint8_t * val)
{
	uint8_t cmd = READ_CONF_REG_1;
	SpiSelect(&sSpiFlash);

	SpiWrite(&sSpiFlash, &cmd, 1);
	SpiRead(&sSpiFlash, val, 1);

	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 * @brief Read configuration register 2
 * @param val Pointer to where to place the read data
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashReadConfig2(uint8_t * val)
{
	uint8_t cmd = READ_CONF_REG_2;
	SpiSelect(&sSpiFlash);

	SpiWrite(&sSpiFlash, &cmd, 1);
	SpiRead(&sSpiFlash, val, 1);

	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 * @brief Read configuration register 3
 * @param val Pointer to where to place the read data
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashReadConfig3(uint8_t * val)
{
	uint8_t cmd = READ_CONF_REG_3;
	SpiSelect(&sSpiFlash);

	SpiWrite(&sSpiFlash, &cmd, 1);
	SpiRead(&sSpiFlash, val, 1);

	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 * @brief Read the device id from the flash chip
 * @param devId Pointer to the device id
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t SpiFlashReadDeviceId(sDeviceId * devId)
{
	uint8_t cmd = READ_DEV_ID;
	SpiSelect(&sSpiFlash);

	SpiWrite(&sSpiFlash, &cmd, 1);
	SpiRead(&sSpiFlash, (uint8_t*)devId, SPIFLASH_DEVID_SIZE);

	SpiDeSelect(&sSpiFlash);

	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashReadAnyRegister(uint32_t reg, uint8_t * val)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashWriteAnyRegister24(uint32_t reg, uint8_t val)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashWriteAnyRegister(uint32_t reg, uint8_t val)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashSetWriteEnable()
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashClearWriteEnable()
{
	return HAL_OK;
}

/**
 * @brief Reset the flash chip
 * @return None
 */
void SpiFlashReset()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(10);
}

/**
 *
 */
uint8_t SpiFlashReadArray(uint32_t addr, uint8_t * data, uint16_t size)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashProgramPage(uint32_t addr, uint8_t * data, uint16_t size)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashEraseSector(uint32_t addr)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashEraseHalfBlock(uint32_t addr)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashEraseBlock(uint32_t addr)
{
	return HAL_OK;
}

/**
 *
 */
uint8_t SpiFlashEraseChip()
{
	return HAL_OK;
}

/**
 *
 */
void FlashSpiTest()
{
	FlashSpiInit();

	HAL_Delay(500);


	uint8_t status1, status2;
	uint8_t config1, config2, config3;
	sDeviceId devId;
	SpiFlashReadStatus1(&status1);
	SpiFlashReadStatus2(&status2);
	SpiFlashReadDeviceId(&devId);

	SpiFlashReadConfig1(&config1);
	SpiFlashReadConfig2(&config2);
	SpiFlashReadConfig3(&config3);

	HAL_Delay(500);

}
