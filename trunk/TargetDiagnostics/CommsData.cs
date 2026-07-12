/********************************************************************
*
*   CommsData.cs
*
*   Description: Storage for communication statistics.
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
    internal class CommsData
    {
        internal static int _outgoingMessageCount;
        internal static int _commsResetCount;
        internal static int _Port_DataReceivedEventCount;
        internal static int _badStartByteCount;
        internal static int _badIncomingSizeCount;
        internal static int _incomingMessageCount;
        internal static int _badIncomingCRCCount;
    }
}