/********************************************************************
*
*   spi.h
*
*   Description:
*
*   Copyright NextPhase Medical Devices, Inc. 2025 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 12/23/25  | Brian Compter     | Created.
*
********************************************************************/
#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#include <stdint.h>
#include "main.h"
#include "gpio.h"

#define SPI_TIMEOUT    (500)

/**
 * Representation of a SPI port
 */
typedef struct
{
	SPI_HandleTypeDef * hSpiPort;
	sGpio * selectPin;
} sSpi;

/**
 * Functions
 */
void SpiInit(void);
void SpiRead(sSpi * spi, uint8_t * buffer, int size);
void SpiWrite(sSpi * spi, uint8_t * buffer, int size);
void SpiStartRead(sSpi * spi);
void SpiWriteRead(sSpi * spi, uint8_t * outBuffer, uint8_t * inBuffer, int size);
void SpiSetSelect(sSpi * spi, uint8_t select);
void SpiSelect(sSpi * spi);
void SpiDeSelect(sSpi * spi);

/**
 * Externs
 */
extern sSpi sSpiAdc1;
extern sSpi sSpiAdc2;
extern sSpi sSpiAdc3;

extern SPI_HandleTypeDef hspi2;

#endif /* INCLUDES_SPI_H_ */
