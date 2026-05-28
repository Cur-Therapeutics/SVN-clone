/********************************************************************
*
*   hyperbusram.h
*
*   Description:    Manages the Octo-Spi PSRAM
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


#define LINEAR_BURST_READ 0x20
#define LINEAR_BURST_WRITE 0xA0
#define DUMMY_CLOCK_CYCLES_SRAM_READ 5
#define DUMMY_CLOCK_CYCLES_SRAM_WRITE 4


void HyperbusInit(void);
void HyperbusTest(void);
void HyperbusReadRegs(uint16_t* regs);
uint16_t HyperbusReadReg(uint32_t reg);

int32_t ISS66WVH8M8_ReadCfgReg0(OSPI_HandleTypeDef *Ctx, uint16_t *Value);
int32_t ISS66WVH8M8_ReadCfgReg1(OSPI_HandleTypeDef *Ctx, uint16_t *Value);

int32_t ISS66WVH8M8_ReadIdReg0(OSPI_HandleTypeDef *Ctx, uint16_t *Value);
int32_t ISS66WVH8M8_ReadIdReg1(OSPI_HandleTypeDef *Ctx, uint16_t *Value);


int32_t ISS66WVH8M8_EnableMemoryMappedMode(OSPI_HandleTypeDef *Ctx);

extern OSPI_HandleTypeDef hospi1;

#endif /* INC_HYPERBUSRAM_H_ */
