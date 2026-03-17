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
    public partial class GUIForm : Form
    {
        internal void ProcessIncomingMessage(List<byte> data)
        {
            eDiagnosticCommands command = (eDiagnosticCommands)data[(int)Commands.MessageCommandIndex];

            switch (command)
            {
                case eDiagnosticCommands.Hello:
                    AddToMessageListBox(data);
                    break;
                default:
                    break;
            }
        }

        private void AddToMessageListBox(List<byte> data)
        {
            if (listBox1.InvokeRequired)
                listBox1.Invoke(new ThreadStart(delegate { AddToMessageListBox(data); }));
            else
                listBox1.Items.Insert(0, BitConverter.ToString(data.ToArray(), 0, data.Count));
        }
    }
}
