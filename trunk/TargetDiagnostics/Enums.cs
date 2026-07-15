/********************************************************************
*
*   Enums.cs
*
*   Description: Enumerations used by this application.
*   
*   Note: eDiagnosticCommands must be kept in sync with the corresponding
*   list on the instrument!
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 3/16/2026 | Walter Eykel      | Created.
*
********************************************************************/

namespace CURDiags
{
    public class Enums
    {
        /// <summary>
        /// List of commands used in communication with the instrument.
        /// Note: eDiagnosticCommands must be kept in sync with the corresponding
        /// list on the instrument!
        /// </summary>
        public enum eDiagnosticCommands
        {
            eDIAG_NOP,
            eDIAG_HELLO,
            eDIAG_STATUS,
            eDIAG_LCD_DATA,
            eDIAG_LCD_DATA_ACK,
            eDIAG_LCD_SET_DISPLAY,
            eDIAG_LCD_BKLIGHT_ON,
            eDIAG_LCD_BKLIGHT_OFF,
            eDIAG_LCD_BKLIGHT_SET,
            eDIAG_TOUCH_INIT,
            eDIAG_TOUCH_READ,
            eDIAG_TOUCH_MODE,
            eDIAG_TOUCH_CAL,
            eDIAG_RTC_STATUS,
            eDIAG_RTC_WRITE,
            eDIAG_FLASH_STATUS,
            eDIAG_FLASH_ID,
            eDIAG_FLASH_READ,
            eDIAG_FLASH_WRITE,
            eDIAG_FLASH_ACK,
            eDIAG_FLASH_ERASE,
            eDIAG_FLASH_MASS_ERASE,
            eDIAG_FLASH_BURN,
            eDIAG_FLASH_RESET,
            eDIAG_FLASH_CLEAR_PROG,
            eDIAG_FLASH_TEST,
            eDIAG_AD7124_GET_STATUS,
            eDIAG_AD7124_REG_WRITE,
            eDIAG_AD7124_REG_READ,
            eDIAG_AD7124_INIT,
            eDIAG_AD7124_RESET,
            eDIAG_AD7124_READ_DATA,
            eDIAG_ACCEL_READ,
            eDIAG_ADC_READ,
            eDIAG_SET_STATE,
            eDIAG_READ_BAROMETRIC,
        }

        /// <summary>
        /// List of subsystems used on the embedded system
        /// </summary>
        public enum eSubsystems
        {
            eSystemArm,
            eSystemFlash,
            eSystemRam,
            eSystemAdc,
            eSystem7124,
            eSystemUart,
            eSystemTouch,
            eSystemRtc,
            eSystemLcd,
            eSystemStack,
            eSystemAccel,
            eSystemSpi,
            eSystemI2C,
            eSystemCath,
        }

    } // end class
}  // end namespace
