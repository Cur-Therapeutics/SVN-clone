/********************************************************************
*
*   spi.c
*
*   Description:    Controls access to the serial port interface
*
*   Copyright NextPhase Medical Devices, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 12/23/25  | Brian Compter     | Created.
*
********************************************************************/

#include "spi.h"
#include "main.h"
#include "gpio.h"
#include "health.h"

/**
 * Spi ports
 */
sSpi sSpiAccel 	= {&hspi1, &sGpioAccelSelect};
sSpi sSpiAdc 	= {&hspi2, &sGpioSpi2Select};

/**
 * Trash
 */
volatile unsigned char trash;

/**
 * @brief Check all SPI ports for errors and proper initialization
 * @return None
 */
void SpiInit()
{
	// Deselect all SPI ports
	SpiDeSelect(&sSpiAdc);
	SpiDeSelect(&sSpiAccel);
	HAL_Delay(50);

	// Check health
	if (	HAL_SPI_GetState(sSpiAdc.hSpiPort) != HAL_SPI_STATE_ERROR &&
			HAL_SPI_GetState(sSpiAdc.hSpiPort) != HAL_SPI_STATE_RESET &&
			HAL_SPI_GetState(sSpiAdc.hSpiPort) != HAL_SPI_STATE_ERROR &&
			HAL_SPI_GetState(sSpiAdc.hSpiPort) != HAL_SPI_STATE_RESET &&

			HAL_SPI_GetState(sSpiAccel.hSpiPort) != HAL_SPI_STATE_ERROR &&
			HAL_SPI_GetState(sSpiAccel.hSpiPort) != HAL_SPI_STATE_RESET &&
			HAL_SPI_GetState(sSpiAccel.hSpiPort) != HAL_SPI_STATE_ERROR &&
			HAL_SPI_GetState(sSpiAccel.hSpiPort) != HAL_SPI_STATE_RESET
	)
	{
		// SPI subsystem is initialized and not in error
		HealthSubsystemGood(eSystemSpi);
	}
	else
	{
		HealthSubsystemBad(eSystemSpi);
	}
}

/**
 * @brief Read from the serial port
 * @param buffer Pointer to a buffer to place the read data
 * @param size The number of bytes to read
 * @return None
 */
void SpiRead(sSpi * spi, uint8_t * buffer, int size)
{
	HAL_SPI_Receive(spi->hSpiPort, buffer, size, SPI_TIMEOUT);
}

/**
 * @brief Write to the serial port
 * @param spi The Spi port to write to
 * @param buffer Pointer to the data to send
 * @param size The number of bytes to send
 * @return None
 */
void SpiWrite(sSpi * spi, uint8_t * buffer, int size)
{
	HAL_SPI_Transmit(spi->hSpiPort, buffer, size, SPI_TIMEOUT);
}

/**
 * @brief Read to the serial port
 * @param spi The Spi port to write to
 * @param outBuffer Pointer to the data to send
 * @param inBuffer Pointer to location to place read data
 * @param size The number of bytes to receive
 */
void SpiWriteRead(sSpi * spi, uint8_t * outBuffer, uint8_t * inBuffer, int size)
{
	HAL_SPI_TransmitReceive(spi->hSpiPort, outBuffer, inBuffer, size, SPI_TIMEOUT);
}

/**
 * @brief Start a read sequence which will be handled by interrupts
 * @param spi The spi port to read from
 * @return None
 */
void SpiStartRead(sSpi * spi)
{
	/* TBD */
}

/**
 * @brief Set the select for this SPI port
 * @param spi The spi port
 * @param select The select setting
 * @return None
 */
void SpiSetSelect(sSpi * spi, uint8_t select)
{
	if (select)
		SpiSelect(spi);
	else
		SpiDeSelect(spi);
}

/**
 * @brief Select this SPI port
 * @param spi The spi port
 * @return None
 */
void SpiSelect(sSpi * spi)
{
	GpioClear(spi->selectPin);
}

/**
 * @brief Deselect this SPI port
 * @param spi The spi port
 * @return None
 */
void SpiDeSelect(sSpi * spi)
{
	GpioSet(spi->selectPin);
}
