/********************************************************************
*
*   hyperbusram.h
*
*   Description:    Manages the Octo-Spi Hyperbus PSRAM
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 02/16/24  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "hyperbusram.h"
#include "health.h"
#include "faulthandler.h"

/**
 * Register values
 */
uint16_t mIdReg0 = 0x4242;
uint16_t mIdReg1 = 0x4242;
uint16_t mCrReg0 = 0x4242;
uint16_t mCrReg1 = 0x4242;

/**
 * OctalSpi handle
 */
OSPI_HandleTypeDef * phospi = &hospi1;

/**
 * @brief Initialize the Hyperbus and confirm communications
 * @return None
 */
void HyperbusInit()
{
	// Fetch ID and CR registers
	mIdReg0 = HyperbusReadReg(ISS66WVH8M8_ID0_ADDRESS);
	mIdReg1 = HyperbusReadReg(ISS66WVH8M8_ID1_ADDRESS);
	mCrReg0 = HyperbusReadReg(ISS66WVH8M8_CR0_ADDRESS);
	mCrReg1 = HyperbusReadReg(ISS66WVH8M8_CR1_ADDRESS);

	// Check IDs to confirm comms
	if (mIdReg0 != ISS66WVH8M8_ID0_VALUE || mIdReg1 != ISS66WVH8M8_ID1_VALUE)
	{
		FaultHandler(ERR_HYPERBUS_RAM);
		return;
	}

	// Enable memory mapped mode
	if (HyperbusEnableMemoryMappedMode(phospi) != HAL_OK)
	{
		FaultHandler(ERR_HYPERBUS_RAM);
		return;
	}

	// Init completed
	HealthSubsystemGood(eSystemRam);
}

/**
 * @brief Read a hyperbus register
 * @param reg The register to read
 * @return The register value
 */
uint16_t HyperbusReadReg(uint32_t reg)
{
	OSPI_HyperbusCmdTypeDef  sCommand;
	uint16_t retval = 0x42;

	/* Initialize the read command */
	sCommand.AddressSpace = HAL_OSPI_REGISTER_ADDRESS_SPACE;
	sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address      = reg;
	sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
	sCommand.NbData       = 2U;

	/* Configure the command */
	if (HAL_OSPI_HyperbusCmd(phospi, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	/* Reception of the data */
	if (HAL_OSPI_Receive(phospi, (uint8_t *)&retval, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	return retval;
}

/**
 * @brief Enable Memory Mapped mode
 * @param Ctx Pointer to the OSPI handle
 * @return
 */
int32_t HyperbusEnableMemoryMappedMode(OSPI_HandleTypeDef *Ctx)
{
	OSPI_HyperbusCmdTypeDef  sCommand;
	OSPI_MemoryMappedTypeDef sMemMappedCfg;

	/* OctoSPI Hyperbus command configuration */
	sCommand.AddressSpace = HAL_OSPI_MEMORY_ADDRESS_SPACE;
	sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address      = 0;
	sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
	sCommand.NbData       = 1;

	if (HAL_OSPI_HyperbusCmd(Ctx, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return HAL_ERROR;
	}

	/* OctoSPI activation of memory-mapped mode */
	sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;

	if (HAL_OSPI_MemoryMapped(Ctx, &sMemMappedCfg) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}
