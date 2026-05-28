/********************************************************************
*
*   hyperbusram.h
*
*   Description:    Manages the Octo-Spi Hyperbus PSRAM
*
*   Copyright NextPhase Medical, Inc. 2023 -- All rights reserved.
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

// Local functions
void HyperbusEnableMemMapped(void);
void DelayBlock_Calibration(void);

__IO uint8_t *mem_addr;
uint32_t address = 0;
uint16_t index1;	/*index1 counter of bytes used when reading writing 256 bytes buffer */
uint16_t index2;	/*index2 counter of 256 bytes buffer used when reading writing the 1Mbytes extended buffer */

uint16_t mIdReg0 = 0x4242;
uint16_t mIdReg1 = 0x4242;
uint16_t mCrReg0 = 0x4242;
uint16_t mCrReg1 = 0x4242;

OSPI_HandleTypeDef * phospi = &hospi1;

/**
 *
 */
void HyperbusInit()
{
	// Fetch ID and CR registers
	mIdReg0 = HyperbusReadReg(ISS66WVH8M8_ID0_ADDRESS);
	mIdReg1 = HyperbusReadReg(ISS66WVH8M8_ID1_ADDRESS);
	mCrReg0 = HyperbusReadReg(ISS66WVH8M8_CR0_ADDRESS);
	mCrReg1 = HyperbusReadReg(ISS66WVH8M8_CR1_ADDRESS);

	// Enable memory mapped mode
	ISS66WVH8M8_EnableMemoryMappedMode(phospi);

	// Calibrate delay
	//DelayBlock_Calibration();
}

/**
 *
 */
void HyperbusReadRegs(uint16_t* regs)
{
	uint16_t * pRegs = regs;
	*pRegs = mIdReg0; pRegs++;
	*pRegs = mIdReg1; pRegs++;
	*pRegs = mCrReg0; pRegs++;
	*pRegs   = mCrReg1;
}


/**
 *
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
	{
		return HAL_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(phospi, (uint8_t *)&retval, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return retval;
}

/**
 *
 */
void HyperbusEnableMemMapped(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	OSPI_MemoryMappedTypeDef sMemMappedCfg;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_ENABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_ENABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_8_LINES;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_ENABLE;
	sCommand.DQSMode = HAL_OSPI_DQS_ENABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Address = 0;
	sCommand.NbData = 1;

	/* Memory-mapped mode configuration for Linear burst write operations */
	sCommand.OperationType = HAL_OSPI_OPTYPE_WRITE_CFG;
	sCommand.Instruction = LINEAR_BURST_WRITE;
	sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_SRAM_WRITE;
	if (HAL_OSPI_Command(phospi, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) !=	HAL_OK)
	{
		Error_Handler();
	}

	/* Memory-mapped mode configuration for Linear burst read operations */
	sCommand.OperationType = HAL_OSPI_OPTYPE_READ_CFG;
	sCommand.Instruction = LINEAR_BURST_READ;
	sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_SRAM_READ;
	if (HAL_OSPI_Command(phospi, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) !=	HAL_OK)
	{
		Error_Handler();
	}

	/*Disable timeout counter for memory mapped mode*/
	sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;

	/*Enable memory mapped mode*/
	if (HAL_OSPI_MemoryMapped(phospi, &sMemMappedCfg) != HAL_OK)
	{
		Error_Handler();
	}

	//DelayBlock_Calibration();
}

/**
 *
 */
void DelayBlock_Calibration(void)
{

}

/**
 *
 */
int32_t ISS66WVH8M8_ReadCfgReg0(OSPI_HandleTypeDef *Ctx, uint16_t *Value)
{
	OSPI_HyperbusCmdTypeDef  sCommand;

	/* Initialize the read command */
	sCommand.AddressSpace = HAL_OSPI_REGISTER_ADDRESS_SPACE;
	sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address      = ISS66WVH8M8_CR0_ADDRESS;
	sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
	sCommand.NbData       = 2U;

	/* Configure the command */
	if (HAL_OSPI_HyperbusCmd(Ctx, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	return HAL_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(Ctx, (uint8_t *)Value, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 *
 */
int32_t ISS66WVH8M8_ReadCfgReg1(OSPI_HandleTypeDef *Ctx, uint16_t *Value)
{
	OSPI_HyperbusCmdTypeDef  sCommand;

	/* Initialize the read command */
	sCommand.AddressSpace = HAL_OSPI_REGISTER_ADDRESS_SPACE;
	sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address      = ISS66WVH8M8_CR1_ADDRESS;
	sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
	sCommand.NbData       = 2U;

	/* Configure the command */
	if (HAL_OSPI_HyperbusCmd(Ctx, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	return HAL_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(Ctx, (uint8_t *)Value, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 *
 */
int32_t ISS66WVH8M8_ReadIdReg0(OSPI_HandleTypeDef *Ctx, uint16_t *Value)
{
	OSPI_HyperbusCmdTypeDef  sCommand;

	/* Initialize the read command */
	sCommand.AddressSpace = HAL_OSPI_REGISTER_ADDRESS_SPACE;
	sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address      = ISS66WVH8M8_ID0_ADDRESS;
	sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
	sCommand.NbData       = 2U;

	/* Configure the command */
	if (HAL_OSPI_HyperbusCmd(Ctx, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return HAL_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(Ctx, (uint8_t *)Value, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 *
 */
int32_t ISS66WVH8M8_ReadIdReg1(OSPI_HandleTypeDef *Ctx, uint16_t *Value)
{
	OSPI_HyperbusCmdTypeDef  sCommand;

	/* Initialize the read command */
	sCommand.AddressSpace = HAL_OSPI_REGISTER_ADDRESS_SPACE;
	sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address      = ISS66WVH8M8_ID1_ADDRESS;
	sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
	sCommand.NbData       = 2U;

	/* Configure the command */
	if (HAL_OSPI_HyperbusCmd(Ctx, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	return HAL_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(Ctx, (uint8_t *)Value, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	return HAL_ERROR;
	}

	return HAL_OK;
}

/**
 *
 */
int32_t ISS66WVH8M8_EnableMemoryMappedMode(OSPI_HandleTypeDef *Ctx)
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
		return -1;
	}

	/* OctoSPI activation of memory-mapped mode */
	sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;

	if (HAL_OSPI_MemoryMapped(Ctx, &sMemMappedCfg) != HAL_OK)
	{
		return -1;
	}

	return HAL_OK;
}
