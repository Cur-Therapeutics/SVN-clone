/********************************************************************
*
*   hyperbusram.h
*
*   Description:    Manages the Octo-Spi PSRAM
*   				S70KL1282DPBHI020 Hyperbus PSRAM
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

#ifndef INC_HYPERBUSRAM_H_
#define INC_HYPERBUSRAM_H_

/**
 * Hyperbus PSRAM
 */
#define HYPERBUS_CR0_ADDRESS        0x00001000U
#define HYPERBUS_CR1_ADDRESS        0x00001002U
#define HYPERBUS_ID0_ADDRESS		0x00000000U
#define HYPERBUS_ID1_ADDRESS		0x00000002U

/**
 * Expected values
 */
#define HYPERBUS_ID0_VALUE			0x0C81
#define HYPERBUS_ID1_VALUE			0x1

/**
 * Functions
 */
void HyperbusInit(void);
uint16_t HyperbusReadReg(uint32_t reg);
int32_t HyperbusEnableMemoryMappedMode(OSPI_HandleTypeDef *Ctx);

/**
 * Reference to the ospi handle
 */
extern OSPI_HandleTypeDef hospi1;

#endif /* INC_HYPERBUSRAM_H_ */
