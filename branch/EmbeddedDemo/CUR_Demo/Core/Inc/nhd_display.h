#ifndef NHD_DISPLAY_H
#define NHD_DISPLAY_H

#include "main.h"

#define NHD_I2C_ADDR (0x3F << 1)

// Control bytes
#define CMD_MODE  0x00
#define DATA_MODE 0x40

void NHD_Reset(void);
void NHD_SendCommand(uint8_t cmd);
void NHD_SendData(uint8_t *data, uint16_t size);

void NHD_Init(void);
void NHD_Clear(void);
void NHD_TestPattern(void);

void NHD_Test(void);

void NHD_AddressSweep(void);

#endif
