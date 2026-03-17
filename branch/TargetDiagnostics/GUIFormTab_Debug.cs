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

        private void TabDebug_Update()
        {
            if (dataGridViewDebugStats.Rows.Count <= 1)
            {
                dataGridViewDebugStats.Rows.Add("_outgoingMessageCount", "0");
                dataGridViewDebugStats.Rows.Add("_commsResetCount", "0");
                dataGridViewDebugStats.Rows.Add("_Port_DataReceivedEventCount", "0");
                dataGridViewDebugStats.Rows.Add("_badStartByteCount", "0");
                dataGridViewDebugStats.Rows.Add("_badIncomingSizeCount", "0");
                dataGridViewDebugStats.Rows.Add("_incomingMessageCount", "0");
                dataGridViewDebugStats.Rows.Add("_badIncomingCRCCount", "0");
            }

            int r = 0;
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._outgoingMessageCount.ToString();
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._commsResetCount.ToString();
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._Port_DataReceivedEventCount.ToString();
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._badStartByteCount.ToString();
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._badIncomingSizeCount.ToString();
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._incomingMessageCount.ToString();
            dataGridViewDebugStats.Rows[r++].Cells[1].Value = CommsData._badIncomingCRCCount.ToString();
        }
    }
}
