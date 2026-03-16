//#define UseNewPort_DataReceived

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