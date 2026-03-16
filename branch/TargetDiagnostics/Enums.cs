/********************************************************************
*
*   Enums.cs
*
*   Description:    
*
*   Copyright NextPhase Medical, Inc. 2025 -- All rights reserved.
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
        public enum eDiagnosticCommands
        {
            Hello = 2,
        }

        public enum sCommandHeaderIndicies
        {
            StartByte,
            SeqId,
            Command,
            Size1,
            Size2,
            Checksum
        }

    }
}
