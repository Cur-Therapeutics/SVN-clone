/********************************************************************
*
*   GUIFormTab_Debug.cs
*
*   Description: Handle the Debug tab
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
    public partial class GUIForm : Form
    {
        private void buttonDebugClearList_Click(object sender, EventArgs e)
        {
            listBoxDebugLogList.Items.Clear();
        }
    }
}
