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

using System.Collections.Generic;

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
            Hello = 2,
        }
    }
}
