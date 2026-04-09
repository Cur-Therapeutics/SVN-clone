/********************************************************************
*
*   uart.c
*
*   Description:    Uart communications implementation
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 03/13/26  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "diagnostics.h"

/**
 * @brief  Rx Transfer completed callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	// Check source of callback
	if (huart == &huart1)
		DiagInterrupt(huart);

}  // end HAL_UART_RxCpltCallback
