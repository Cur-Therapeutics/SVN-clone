/********************************************************************
*
*   stack_check.c
*
*   Description:    Verify the integrity of the stack
*
*   Copyright PPMD, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 08/19/19  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "health.h"
#include "faulthandler.h"
#include "stack_check.h"

/**
  * @brief Get SP Register
  * @details Returns the current value of the Stack Pointer (SP).
  * @retval LR Register value
*/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_SP(void)
{
  register uint32_t result;

  __ASM volatile ("MOV %0, SP\n" : "=r" (result) );
  return(result);
}

/**
  * @brief  Verify stack integrity
  * @retval None
  */
void StackCheck()
{
	static uint32_t sStackPointer = 0;
	uint32_t newStackPointer;

	// See if our stack pointer is drifting
	newStackPointer = __get_SP();
	if ((sStackPointer != 0) && (sStackPointer != newStackPointer))
	{
		HealthSubsystemBad(eSystemStack);
		FaultHandler(ERR_STK_DRIFT);
	}
	sStackPointer = newStackPointer;
}
