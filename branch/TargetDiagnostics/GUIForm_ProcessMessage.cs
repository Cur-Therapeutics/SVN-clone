/********************************************************************
*
*   GUIForm_ProcessMessage.cs
*
*   Description: Handles routing of individual incoming messages to
*   the proper handler.
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

using static CURDiags.Enums;

namespace CURDiags
{
    /// <summary>
    /// This source file contains the ProcessIncomingMessage() method to handle
    /// the routing of all incoming messages.
    /// </summary>
    public partial class GUIForm : Form
    {
        internal void ProcessIncomingMessage(byte[] data)
        {
            if (data.Length < Commands.Sizeof_sCommandHeader)
            {
                return;
            }

            Logger.LogMessage($"ProcessIncomingMessage() {(eDiagnosticCommands)data[Commands.MessageCommandIndex]}");

            eDiagnosticCommands command = (eDiagnosticCommands)data[(int)Commands.MessageCommandIndex];

            switch (command)
            {
                case eDiagnosticCommands.Hello:
                    AddToMessageListBox(data);
                    break;
                default:
                    Logger.LogError($"ProcessIncomingMessage() unhandled message {data[Commands.MessageCommandIndex]}");
                    break;
            }
        }

        private void AddToMessageListBox(byte[] data)
        {
            listBox1.Items.Insert(0, BitConverter.ToString(data.ToArray(), 0, data.Length));
        }
    }
}
