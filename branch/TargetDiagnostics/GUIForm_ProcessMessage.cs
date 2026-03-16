/********************************************************************
*
*   GUIFOrm_ProcessMessage.cs
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
    public partial class GUIForm : Form
    {
        internal void ProcessIncomingMessage(List<byte> data)
        {
            AddToMessageListBox(data);
          
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
