/********************************************************************
*
*   post.h
*
*   Description:    Power on self test
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 06/13/26  | Brian Compter     | Created
*
********************************************************************/
#ifndef INC_POST_H_
#define INC_POST_H_

void PostInit(void);
void PostDrive(void);
uint8_t PostIsComplete(void);
uint32_t PostGetResult(void);

#endif /* INC_POST_H_ */
