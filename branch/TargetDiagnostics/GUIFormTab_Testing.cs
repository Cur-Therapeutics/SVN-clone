/********************************************************************
*
*   GUIFormTab_Testing.cs
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

using static CURDiags.Enums;

namespace CURDiags
{
    public partial class GUIForm : Form
    {
        private void buttonHello_Click(object sender, EventArgs e)
        {
            Commands? commands = GetCommands();

            if (commands == null)
            {
                MessageBox.Show("Connect to a COM port first.");
                return;
            }

            bool isSent = commands.SendCommand(eDiagnosticCommands.Hello);

            if (!isSent)
            {
                MessageBox.Show("Failed to send Hello");
            }
        }
    }
}
