/********************************************************************
*
*   GUIForm.cs
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

using System.IO.Ports;

namespace CURDiags
{
    public partial class GUIForm : Form
    {
        private Serial? mSerialPort;
        private Commands? mCommands;

        public GUIForm()
        {
            InitializeComponent();

            Text += $" {Version.Value}";

            comboBoxBaudRate.SelectedIndex = 0;

            RefreshCOMPortList();
        }

        public bool IsCOMPortOpen => mSerialPort != null && mSerialPort.IsOpen;

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (IsCOMPortOpen)
            {
                ClosePort();
                return;
            }

            if (!int.TryParse(comboBoxBaudRate.Text, out int baudRate))
            {
                Logger.LogMessage("Bad baud rate");
                return;
            }

            Serial serial = new Serial(this);

            if (!serial.OpenPort(comboBoxCOMPort.Text, baudRate))
            {
                Logger.LogMessage("Failed to open comm port!");
                serial.Close();
                return;
            }

            mSerialPort = serial;
            mCommands = new Commands(serial);
        }

        public void ClosePort()
        {
            mSerialPort?.Close();
            mSerialPort = null;
            mCommands = null;
        }

        internal Commands? GetCommands()
        {
            return mCommands;
        }

        private void timerOneSecond_Tick(object sender, EventArgs e)
        {
            labelCOMStatus.BackColor = IsCOMPortOpen ? Color.Green : Color.Red;
            buttonConnect.Text = IsCOMPortOpen ? "Disconnect" : "Connect";
        }

        private void comboBoxCOMPort_DropDown(object sender, EventArgs e)
        {
            RefreshCOMPortList();
        }

        private void RefreshCOMPortList()
        {
            string? selectedPort = comboBoxCOMPort.SelectedItem as string;
            string currentText = comboBoxCOMPort.Text;
            string[] ports = SerialPort.GetPortNames().OrderBy(name => name).ToArray();

            comboBoxCOMPort.BeginUpdate();
            comboBoxCOMPort.Items.Clear();
            comboBoxCOMPort.Items.AddRange(ports);
            comboBoxCOMPort.EndUpdate();

            if (!string.IsNullOrWhiteSpace(selectedPort) && ports.Contains(selectedPort))
            {
                comboBoxCOMPort.SelectedItem = selectedPort;
            }
            else if (!string.IsNullOrWhiteSpace(currentText) && ports.Contains(currentText))
            {
                comboBoxCOMPort.SelectedItem = currentText;
            }
            else if (ports.Length > 0)
            {
                comboBoxCOMPort.SelectedIndex = 0;
            }
            else
            {
                comboBoxCOMPort.Text = string.Empty;
            }
        }

        private void GUIForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            ClosePort();
        }
    }
}
