/********************************************************************
*
*   GUIFormTab_Testing.cs
*
*   Description: Handle operation of the Testing tab
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
    /// Testing tab of the main form tab control
    /// </summary>
    public partial class GUIForm : Form
    {
        private void buttonHello_Click(object sender, EventArgs e)
        {

            if (!IsCOMPortOpen)
            {
                MessageBox.Show("Connect to a COM port first.");
                return;
            }

            bool isSent = Commands.SendCommand(eDiagnosticCommands.Hello);

            if (!isSent)
            {
                MessageBox.Show("Failed to send Hello");
            }
        }
    }
}
