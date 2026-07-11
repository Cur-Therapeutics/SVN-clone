/********************************************************************
*
*   hyperbusram.h
*
*   Description:    Manages the Octo-Spi PSRAM
*   				IS66WVH8M8BLL-100B1LI Hyperbus PSRAM
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

#ifndef INC_HYPERBUSRAM_H_
#define INC_HYPERBUSRAM_H_

/**
 * IS66WVH8M8BLL-100B1LI Hyperbus PSRAM
 */
#define ISS66WVH8M8_CR0_ADDRESS         0x00001000U
#define ISS66WVH8M8_CR1_ADDRESS         0x00001002U
#define ISS66WVH8M8_ID0_ADDRESS			0x00000000U
#define ISS66WVH8M8_ID1_ADDRESS			0x00000002U

/**
 * Expected values
 */
#define ISS66WVH8M8_ID0_VALUE			0x0C83
#define ISS66WVH8M8_ID1_VALUE			0x0

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
