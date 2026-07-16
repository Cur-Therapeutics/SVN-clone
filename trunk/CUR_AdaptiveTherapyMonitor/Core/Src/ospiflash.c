/********************************************************************
*
*   ospiflash.c
*
*   Description:    Manages the Octo-Spi Flash
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 02/12/24  | Brian Compter     | Created.
*
********************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "ospiflash.h"
#include "string.h"
#include "health.h"
#include "faulthandler.h"

/**
 * Octal flash state
 */
eOctoSpiFlashState mFlashState = FLASH_STATE_LEGACY;

/**
 * Flash Ids used in commands
 */
sFlashIds mFlashIds;

/**
 * JEDEC Header
 */
uint8_t jedec [32];

/**
 * Our flash handle
 */
OSPI_HandleTypeDef * phospiflash = &hospi2;

/**
 * Timeout
 */
#define OCTOSPIFLASH_TIMEOUT_MS		(1000)

/**
 * Error counters
 */
uint32_t mOspiErrors 		= 0;
uint32_t mOspiAbort 		= 0;
uint32_t mOspiFifoThreshold = 0;
uint32_t mOspiCmdCplt 		= 0;
uint32_t mOspiRxCplt 		= 0;
uint32_t mOspiTxCplt 		= 0;
uint32_t mOspiRxHalfCplt 	= 0;
uint32_t mOspiTxHalfCplt 	= 0;
uint32_t mOspiStatusMatch 	= 0;
uint32_t mOspiTimeOut 		= 0;

/**
 * Used to hold operation status
 */
HAL_StatusTypeDef HAL_status1;
HAL_StatusTypeDef HAL_status2;

/**
 * Internal functions
 */
static uint8_t _FlashWrite(uint32_t addr, uint8_t * data, uint32_t count);

/**
 * @brief Initialize the octal flash interface for use, retrieve Ids to confirm communications
 * @return None
 */
void FlashInit()
{
	// Small delay to make sure we are up and ready
	HAL_Delay(50);

	// Reset Flash chip so we start at a known state
	FlashReset();
	FlashClearProgramAndErrors();

	LegacyFlashReadJedec();
	LegacyFlashReadId();

	uint8_t cfr1x = 0;
	uint8_t cfr2x = 0;
	uint8_t cfr3x = 0;
	uint8_t cfr4x = 0;
	uint8_t cfr5x = 0;

	// Read Configuration registers
    LegacyFlashReadAnyRegister24(OCTOSPIFLASH_REG_CFR1X, &cfr1x, 0);
    LegacyFlashReadAnyRegister24(OCTOSPIFLASH_REG_CFR2X, &cfr2x, 0);
    LegacyFlashReadAnyRegister24(OCTOSPIFLASH_REG_CFR3X, &cfr3x, 0);
    LegacyFlashReadAnyRegister24(OCTOSPIFLASH_REG_CFR4X, &cfr4x, 0);
    LegacyFlashReadAnyRegister24(OCTOSPIFLASH_REG_CFR5X, &cfr5x, 0);

    // Enable 32 bit addressing
	LegacyFlashWriteAnyRegister24(OCTOSPIFLASH_REG_CFR2X, FLASH_CFG2_32ADDR_MODE);

	LegacyFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR1X, &cfr1x, 0);
	LegacyFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR2X, &cfr2x, 0);
	LegacyFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR3X, &cfr3x, 0);
	LegacyFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR4X, &cfr4x, 0);
	LegacyFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR5X, &cfr5x, 0);

	// Switch to Octal mode
	LegacyFlashWriteAnyRegister(OCTOSPIFLASH_REG_CFR5X, FLASH_CFG5_OCTAL_MODE);
	mFlashState = FLASH_STATE_OCTAL;

	// Re-read IDs and configuration registers to verify communications
	OctalFlashReadId();
	OctalFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR1X, &cfr1x, 3);
	OctalFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR2X, &cfr2x, 3);
	OctalFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR3X, &cfr3x, 3);
	OctalFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR4X, &cfr4x, 3);
	OctalFlashReadAnyRegister(OCTOSPIFLASH_REG_CFR5X, &cfr5x, 3);

	// Verify Flash ids
	if (mFlashIds.manufactureId != FLASH_MANUFACTURE_ID || mFlashIds.family != FLASH_FAMILY_ID)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}

	// Init completed
	HealthSubsystemGood(eSystemFlash);
}

/**
 * @brief Reset the chip to factory settings, no matter what mode it is in
 * @return None
 */
void FlashReset()
{
	OctalFlashReset();
	LegacyFlashReset();
	mFlashState = FLASH_STATE_LEGACY;
}

/**
 * @brief Copy the last read flash ids to the provided pointer
 * @param ids Pointer to place the data
 * @return None
 */
void FlashGetIds(sFlashIds * ids)
{
	memcpy(ids, (uint8_t*)&mFlashIds, sizeof(mFlashIds));
}

/**
 * @brief Get the current flash state
 * @return The flash state
 */
eOctoSpiFlashState FlashGetState()
{
	return mFlashState;
}

/**
 * @brief Read JEDEC header information
 * @return None
 */
void LegacyFlashReadJedec()
{
	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = 0x5A;

	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 8;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
	if (HAL_OSPI_Receive(phospiflash, jedec, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
}

/**
 * @brief Read the flash IDs and store them locally in legacy 1S-1S-1S mode
 * @return None, output are placed in member variables
 */
void LegacyFlashReadId()
{
	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = 0x9F;

	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 6;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
	if (HAL_OSPI_Receive(phospiflash, (uint8_t*)&mFlashIds, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}

	sCommand.Instruction = READ_UNIQUE_ID;
	sCommand.NbData = 8;
	sCommand.DummyCycles = 31;
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
	if (HAL_OSPI_Receive(phospiflash, (uint8_t*)&mFlashIds.uniqueId, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
}

/**
 * @brief Read status register 1 in legacy 1S-1S-1S mode
 * @return Status register 1 value
 */
uint8_t LegacyFlashReadSr1()
{
	// Read Status Register
	uint8_t statusReg;

	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_8_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	HAL_status1 = HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status1 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	HAL_status1 = HAL_OSPI_Receive(phospiflash, &statusReg, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status1 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	return statusReg;
}

/**
 * @brief Read status register 2 in legacy 1S-1S-1S mode
 * @return Status register 2 value
 */
uint8_t LegacyFlashReadSr2()
{
	// Read Status Register
	uint8_t statusReg;

	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = READ_STATUS2_REG_CMD;
	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_8_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	HAL_status2 = HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status2 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	HAL_status2 = HAL_OSPI_Receive(phospiflash, &statusReg, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status2 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	return statusReg;
}

/**
 * @brief Reset the chip to default settings
 * @return None
 */
uint8_t LegacyFlashReset()
{
	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
	cmd.InstructionSize   = HAL_OSPI_INSTRUCTION_8_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.AddressMode        = HAL_OSPI_ADDRESS_NONE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_NONE;
	cmd.Instruction        = FLASH_RESET_ENABLE;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}

	cmd.Instruction        = FLASH_RESET_DEVICE;
	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}

	// Small delay to let things settle after the reset
	HAL_Delay(50);

	return HAL_OK;
}

/**
 * @brief Set write enable
 * @return None
 */
void LegacyFlashWriteEnable()
{
	OSPI_RegularCmdTypeDef sCommand;
	/* Initialize the Write Enable cmd in single SPI mode */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = WRITE_ENABLE_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	/* Send Write Enable command in single SPI mode */
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return;
	}
}

/**
 * @brief Disable write enable
 * @return None
 */
void LegacyFlashWriteDisable()
{
	OSPI_RegularCmdTypeDef sCommand;
	/* Initialize the Write Enable cmd in single SPI mode */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = WRITE_DISABLE_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	/* Send Write Enable command in single SPI mode */
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return;
	}
}

/**
 * @brief Write any register in legacy 1S-1S-1S 24 bit address mode
 * @return HAL_OK on command success, HAL_ERROR otherwise
 */
uint8_t LegacyFlashWriteAnyRegister24(uint32_t reg, uint8_t val)
{
	// Write enable
	LegacyFlashWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
	cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.AddressMode        = HAL_OSPI_ADDRESS_1_LINE;
	cmd.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
	cmd.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_1_LINE;
	cmd.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
	cmd.NbData         	   = 1;
	cmd.Instruction        = WRITE_ANY_REGISTER;
	cmd.Address            = reg;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}
	if (HAL_OSPI_Transmit(phospiflash, &val, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 * @brief Write any register in legacy 1S-1S-1S 32 bit address mode
 * @return HAL_OK on command success, HAL_ERROR otherwise
 */
uint8_t LegacyFlashWriteAnyRegister(uint32_t reg, uint8_t val)
{
	// Write enable
	LegacyFlashWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
	cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.AddressMode        = HAL_OSPI_ADDRESS_1_LINE;
	cmd.AddressSize        = HAL_OSPI_ADDRESS_32_BITS;
	cmd.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_1_LINE;
	cmd.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
	cmd.NbData         	   = 1;
	cmd.Instruction        = WRITE_ANY_REGISTER;
	cmd.Address            = reg;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}
	if (HAL_OSPI_Transmit(phospiflash, &val, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 * @brief Read any register in legacy 1S-1S-1S mode with 24 bit address
 * @param reg The register to read
 * @param val Pointer to the location to place the data
 * @param dummyCycles Dummy cycles per the configuration of the
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t LegacyFlashReadAnyRegister24(uint32_t reg, uint8_t * val, uint32_t dummyCycles)
{
	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType       = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode     = HAL_OSPI_INSTRUCTION_1_LINE;
	cmd.InstructionDtrMode  = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.InstructionSize    	= HAL_OSPI_INSTRUCTION_8_BITS;
	cmd.Instruction         = READ_ANY_REGISTER;

	cmd.AddressMode         = HAL_OSPI_ADDRESS_1_LINE;
	cmd.AddressDtrMode      = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AddressSize        	= HAL_OSPI_ADDRESS_24_BITS;
	cmd.Address             = reg;

	cmd.DummyCycles         = dummyCycles;

	cmd.DataMode            = HAL_OSPI_DATA_1_LINE;
	cmd.DataDtrMode         = HAL_OSPI_DATA_DTR_DISABLE;
	cmd.NbData          	= 1;
	cmd.DQSMode 		    = HAL_OSPI_DQS_DISABLE;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	uint8_t buf[2] = {0};
	if (HAL_OSPI_Receive(phospiflash, buf, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	*val = buf[0];

	return HAL_OK;
}

/**
 * @brief Read any register in legacy 1S-1S-1S mode
 * @param reg The register to read
 * @param val Pointer to the location to place the data
 * @param dummyCycles Dummy cycles per the configuration of the
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t LegacyFlashReadAnyRegister(uint32_t reg, uint8_t * val, uint32_t dummyCycles)
{
	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType       = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode     = HAL_OSPI_INSTRUCTION_1_LINE;
	cmd.InstructionDtrMode  = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.InstructionSize    	= HAL_OSPI_INSTRUCTION_8_BITS;
	cmd.Instruction         = 0x65;
	cmd.AddressMode         = HAL_OSPI_ADDRESS_1_LINE;
	cmd.AddressDtrMode      = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AddressSize        	= HAL_OSPI_ADDRESS_32_BITS;
	cmd.Address             = reg;
	cmd.DummyCycles         = dummyCycles;
	cmd.DataMode            = HAL_OSPI_DATA_1_LINE;
	cmd.DataDtrMode         = HAL_OSPI_DATA_DTR_DISABLE;
	cmd.NbData          	= 1;
	cmd.DQSMode 		    = HAL_OSPI_DQS_DISABLE;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	uint8_t buf[2] = {0};
	if (HAL_OSPI_Receive(phospiflash, buf, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	*val = buf[0];

	return HAL_OK;
}

/**
 * @brief Read the flash IDs and store them locally in octal 8S-8S-8S mode
 * @return None
 */
void OctalFlashReadId()
{
	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;

	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = 0x9F9F;

	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;

	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 6;

	sCommand.DummyCycles = 3;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
	if (HAL_OSPI_Receive(phospiflash, (uint8_t*)&mFlashIds, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}

	sCommand.Instruction = 0x4C4C;
	sCommand.NbData = 8;
	sCommand.DummyCycles = 31;
	if (HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
	if (HAL_OSPI_Receive(phospiflash, (uint8_t*)&mFlashIds.uniqueId, OCTOSPIFLASH_TIMEOUT_MS) !=	HAL_OK)
	{
		FaultHandler(ERR_FLASH_INIT);
		return;
	}
}

/**
 * @brief Reset the chip to factory settings
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t OctalFlashReset()
{
	OSPI_RegularCmdTypeDef cmd = {0};

	// Software Reset Enable
	cmd.OperationType       = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.FlashId             = HAL_OSPI_FLASH_ID_1;
	cmd.InstructionMode     = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionDtrMode  = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.InstructionSize     = HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.Instruction         = 0x6666;   // Software Reset Enable
	cmd.AddressMode         = HAL_OSPI_ADDRESS_NONE;
	cmd.AlternateBytesMode  = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DataMode            = HAL_OSPI_DATA_NONE;
	cmd.DummyCycles         = 0;
	cmd.DQSMode             = HAL_OSPI_DQS_DISABLE;
	cmd.SIOOMode            = HAL_OSPI_SIOO_INST_EVERY_CMD;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}

	// Software Reset
	cmd.Instruction         = 0x9999;   // Software Reset
	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}

	// Small delay to let things settle after the reset
	HAL_Delay(50);

	return HAL_OK;
}

/**
 * @brief Read any register in octal 8S-8S-8S mode
 * @param reg The register to read
 * @param val Pointer to the location to place the data
 * @param dummyCycles Dummy cycles per the configuration of the
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t OctalFlashReadAnyRegister(uint32_t reg, uint8_t * val, uint32_t dummyCycles)
{
	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType       = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode     = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionDtrMode  = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.InstructionSize    	= HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.Instruction         = 0x6565;

	cmd.AddressMode         = HAL_OSPI_ADDRESS_8_LINES;
	cmd.AddressDtrMode      = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AddressSize        	= HAL_OSPI_ADDRESS_32_BITS;
	cmd.Address             = reg;

	cmd.DummyCycles         = dummyCycles;

	cmd.DataMode            = HAL_OSPI_DATA_8_LINES;
	cmd.DataDtrMode         = HAL_OSPI_DATA_DTR_DISABLE;
	cmd.NbData          	= 1;
	cmd.DQSMode 		    = HAL_OSPI_DQS_DISABLE;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	uint8_t buf[2] = {0};
	if (HAL_OSPI_Receive(phospiflash, buf, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	*val = buf[0];

	return HAL_OK;
}

/**
 * @brief Octal mode write any register
 * @param reg The register to write to
 * @param val The value to write
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint8_t OctalFlashWriteAnyRegister(uint32_t reg, uint8_t val)
{
	// Set write enable
	OctalWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType	   = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.AddressMode        = HAL_OSPI_ADDRESS_8_LINES;
	cmd.AddressSize        = HAL_OSPI_ADDRESS_32_BITS;
	cmd.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_8_LINES;
	cmd.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
	cmd.NbData        	   = 1;
	cmd.Instruction        = 0x7171;
	cmd.Address            = reg;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}
	uint8_t buf[2] = {val, val};
	if (HAL_OSPI_Transmit(phospiflash, buf, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 * @brief Read status register 1
 * @return Status register 1 value
 */
uint8_t OctalFlashReadSr1()
{
	// Read Status Register
	uint8_t statusReg;

	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = 0x0505;

	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;

	sCommand.DummyCycles = 5;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	HAL_status1 = HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status1 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	HAL_status1 = HAL_OSPI_Receive(phospiflash, &statusReg, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status1 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	return statusReg;
}

/**
 * @brief Read status register 2
 * @return Status register 2 value
 */
uint8_t OctalFlashReadSr2()
{
	// Read Status Register
	uint8_t statusReg;

	/* Configure command */
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = 0x0707;

	sCommand.Address = 0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;

	sCommand.DummyCycles = 5;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	HAL_status1 = HAL_OSPI_Command(phospiflash, &sCommand, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status1 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	HAL_status1 = HAL_OSPI_Receive(phospiflash, &statusReg, OCTOSPIFLASH_TIMEOUT_MS);
	if (HAL_status1 != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return HAL_ERROR;
	}
	return statusReg;
}

/**
 * @brief Enable write operations
 * @return None
 */
void OctalWriteEnable()
{
	OSPI_RegularCmdTypeDef  sCommand;

	/* Enable write operations ------------------------------------------ */
	sCommand.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId            = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction        = 0x0606;
	sCommand.InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize    = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode        = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode           = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles        = 0;
	sCommand.DQSMode            = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

	if (HAL_OSPI_Command(phospiflash, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		FaultHandler(ERR_FLASH_TIMEOUT);
		return;
	}
}

/**
 * @brief Erase a 4K sector at the provided address
 * Sector addresses and sizes (4K/256K) are dependent on register settings!
 */
uint8_t OctalSpiFlashErase4KSector(uint32_t addr)
{
	// Set write enable
	OctalWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.Instruction        = 0x2121;

	cmd.AddressMode        = HAL_OSPI_ADDRESS_8_LINES;
	cmd.AddressSize        = HAL_OSPI_ADDRESS_32_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_NONE;
	cmd.Address            = addr;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		mOspiErrors++;
		return HAL_ERROR;
	}

	// Check status
	uint8_t status = OctalFlashReadSr1();
	while (status == 0x03)
	{
		HAL_Delay(10);
		status = OctalFlashReadSr1();
	}

	return HAL_OK;
}

/**
 * @brief Erase a 256K sector at the provided address
 * Sector addresses and sizes (4K/256K) are dependent on register settings!
 */
uint8_t OctalSpiFlashErase256KSector(uint32_t addr)
{
	// Set write enable
	OctalWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionSize   = HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.Instruction        = 0xDCDC;

	cmd.AddressMode        = HAL_OSPI_ADDRESS_8_LINES;
	cmd.AddressSize       = HAL_OSPI_ADDRESS_32_BITS;
	cmd.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_NONE;
	cmd.Address            = addr;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		mOspiErrors++;
		FaultHandler(ERR_FLASH_ERASE);
		return HAL_ERROR;
	}

	// Check status
	uint8_t status = OctalFlashReadSr1();
	while (status == 0x03)
	{
		HAL_Delay(10);
		status = OctalFlashReadSr1();
	}

	return HAL_OK;
}

/**
 * @brief Erase a 4K sector at the provided address
 * Sector addresses and sizes (4K/256K) are dependent on register settings!
 */
uint8_t OctalSpiFlashErase4KSectorIT(uint32_t addr)
{
	// Set write enable
	OctalWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.Instruction        = 0x2121;

	cmd.AddressMode        = HAL_OSPI_ADDRESS_8_LINES;
	cmd.AddressSize        = HAL_OSPI_ADDRESS_32_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_NONE;
	cmd.Address            = addr;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		mOspiErrors++;
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 * @brief Erase a 256K sector at the provided address
 * Sector addresses and sizes (4K/256K) are dependent on register settings!
 */
uint8_t OctalSpiFlashErase256KSectorIT(uint32_t addr)
{
	// Set write enable
	OctalWriteEnable();

	OSPI_RegularCmdTypeDef cmd = {0};

	cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
	cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
	cmd.InstructionSize   = HAL_OSPI_INSTRUCTION_16_BITS;
	cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	cmd.Instruction        = 0xDCDC;

	cmd.AddressMode        = HAL_OSPI_ADDRESS_8_LINES;
	cmd.AddressSize       = HAL_OSPI_ADDRESS_32_BITS;
	cmd.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
	cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	cmd.DummyCycles        = 0;
	cmd.DataMode           = HAL_OSPI_DATA_NONE;
	cmd.Address            = addr;

	if (HAL_OSPI_Command(phospiflash, &cmd, OCTOSPIFLASH_TIMEOUT_MS) != HAL_OK)
	{
		mOspiErrors++;
		FaultHandler(ERR_FLASH_ERASE);
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 * @brief Read data from the flash
 * @param addr The address to read
 * @param data Location to place the read data
 * @param count The number of bytes to read
 * @return None
 */
void FlashRead(uint32_t addr, uint8_t * data, uint32_t count)
{
	OSPI_RegularCmdTypeDef sCommand;
	// Initialize Indirect write mode to read from memory
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = 0xECEC;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;

	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = count;
	sCommand.DummyCycles = 5;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address = addr;

	// Send Sector read cmd
	if (HAL_OSPI_Command(phospiflash, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) !=	HAL_OK)
	{
		Error_Handler();
	}

	// Read data
	if (HAL_OSPI_Receive(phospiflash, data, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
}

/*
 * @brief Write to flash
 * @note Flash writes are limited to 256 byte pages, this function will handle any size write by breaking it into multiple pages
 * @note Flash address must be successfully erased prior to writing, use caution at sector boundaries
 * @return 0 for success, 1 for failure
 */
uint8_t FlashWrite(uint32_t flashAddress, uint8_t * data, uint32_t size)
{
	// Verify data and size
    if (data == NULL || size == 0)
    {
        return 1;
    }

    uint8_t * p = (uint8_t *) data;
    uintptr_t dst = (uintptr_t)flashAddress;

    while (size > 0)
    {
        size_t chunk = (size > OSPI_FLASH_PAGE_SIZE) ? OSPI_FLASH_PAGE_SIZE : size;

        if (_FlashWrite((uint32_t)dst, p, chunk) != 0)
        {
        	FaultHandler(ERR_FLASH_WRITE);
            return 1;
        }

        p    += chunk;
        dst  += chunk;
        size -= chunk;
    }

    return 0;
}

/**
 * @brief Write data to flash
 * @param addr The starting address to write to
 * @param data The data to write
 * @param count The number of bytes to write
 */
static uint8_t _FlashWrite(uint32_t addr, uint8_t * data, uint32_t count)
{
	uint8_t retval = 0;

	// Check page size
	if (count > OSPI_FLASH_PAGE_SIZE)
	{
		// Can't write more than one page at a time
		Error_Handler();
		return 1;
	}

	OctalWriteEnable();

	// Initialize Indirect write mode to write to memory
	OSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = 0x1212;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;

	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = count;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address = addr;

	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

	// Send Sector write cmd
	HAL_StatusTypeDef HAL_status = HAL_OSPI_Command(phospiflash, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE);
	if (HAL_status != HAL_OK)
	{
		retval = HAL_ERROR;
		Error_Handler();
	}

	// Write data
	HAL_status = HAL_OSPI_Transmit(phospiflash, data, HAL_OSPI_TIMEOUT_DEFAULT_VALUE);
	if (HAL_status != HAL_OK)
	{
		retval = HAL_ERROR;
		Error_Handler();
	}

	// Check status
	uint8_t status = OctalFlashReadSr1();
	while (status == 0x03)
	{
		HAL_Delay(10);
		status = OctalFlashReadSr1();
	}

	if (status == 0x41)
	{
		retval  = HAL_ERROR;
	}

	return retval;
}

/**
 * @brief Clear program and errors
 * @return None
 */
void FlashClearProgramAndErrors()
{
	OSPI_RegularCmdTypeDef sCommand;
	/* Initialize the cmd in single SPI mode */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = 0x8282;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	/* Send command in single SPI mode */
	if (HAL_OSPI_Command(phospiflash, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) !=	HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief  Transfer Error callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_ErrorCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiErrors++;
}

/**
  * @brief  Abort completed callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_AbortCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiAbort++;
}

/**
  * @brief  FIFO Threshold callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_FifoThresholdCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiFifoThreshold++;
}

/**
  * @brief  Command completed callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_CmdCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiCmdCplt++;
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_RxCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiRxCplt++;
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
 void HAL_OSPI_TxCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiTxCplt++;
}

/**
  * @brief  Rx Half Transfer completed callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_RxHalfCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiRxHalfCplt++;
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_TxHalfCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiTxHalfCplt++;
}

/**
  * @brief  Status Match callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_StatusMatchCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiStatusMatch++;
}

/**
  * @brief  Timeout callback.
  * @param  hospi : OSPI handle
  * @retval None
  */
void HAL_OSPI_TimeOutCallback(OSPI_HandleTypeDef *hospi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hospi);
  mOspiTimeOut++;
}

/**
 * @brief Flash testing
 * @return None
 */
void FlashTest()
{
	OctalWriteEnable();
	uint8_t sr1 = OctalFlashReadSr1();
	UNUSED(sr1);	// Suppress warning

	// Erase 4K Sector
	OctalSpiFlashErase4KSector(0);
	sr1 = OctalFlashReadSr1();

	// Write to Sector
	uint8_t writeBuffer [512];
	for (int i = 0; i < 512; i++)
	{
		writeBuffer[i] = i;
	}
	FlashWrite(0, writeBuffer, 256);

	sr1 = OctalFlashReadSr1();
	//FlashClearProgramAndErrors();
	sr1 = OctalFlashReadSr1();


	// Read from Sector
	uint8_t readBuffer [512];
	memset(readBuffer, 0, 512);
	FlashRead(0, readBuffer, 256);
	readBuffer[0]++;

	// ...

	// Erase 256K Sector
	OctalSpiFlashErase256KSector(0x40000);
	sr1 = OctalFlashReadSr1();

	// Write to Sector
	FlashWrite(0x40000, writeBuffer, 256);

	sr1 = OctalFlashReadSr1();
	//FlashClearProgramAndErrors();
	sr1 = OctalFlashReadSr1();

	// Read from Sector
	memset(readBuffer, 0, 512);
	FlashRead(0x40000, readBuffer, 256);
	readBuffer[0]++;
}
