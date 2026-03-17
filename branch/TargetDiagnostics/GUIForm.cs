/********************************************************************
*
*   GUIForm.cs
*
*   Description: Main form for the application.
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

using MeiraDiagnostics;
using System.IO.Ports;
using System.Windows.Forms;
using Utilities;

namespace CURDiags
{
    /// <summary>
    /// This is the main form of the Diags application. Form initialization and
    /// shared functionality are in this source file.
    /// Code for the individual tab pages of the main tab control are in their
    /// own source file. (e.g. GUIFormTab_Testing.cs)
    /// </summary>
    public partial class GUIForm : Form
    {
        private Serial? mSerialPort;

        private FormResizer _resizer;

        /// <summary>
        /// Get a flag indiating whether the communication channel is usable.
        /// </summary>
        public bool IsCOMPortOpen => mSerialPort != null && mSerialPort.IsOpen;

        private const string ConfigrationFileName = "Configuration.csv";

        private readonly CsvFile _configrationFile = new CsvFile(ConfigrationFileName);

        /// <summary>
        /// Construct an instance of the GUIForm. Perform one-time initialization.
        /// </summary>
        public GUIForm()
        {
            InitializeComponent();

            Text += $" {Version.Value}";

            comboBoxBaudRate.SelectedIndex = 0;

            Logger.LoggedMessage += Logger_LoggedMessage;
            RefreshCOMPortList();

            if (string.IsNullOrEmpty(comboBoxCOMPort.Text))
                comboBoxCOMPort.Text = _configrationFile.GetValue("Port");
        }

        private readonly Dictionary<string, string> _configurationData = new();

        /// <summary>
        /// Handle the Closing event of the main Form.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void GUIForm_FormClosing(object _, FormClosingEventArgs __)
        {
            Logger.LoggedMessage -= Logger_LoggedMessage;
            ClosePort();
        }

        private void GUIForm_Load(object sender, EventArgs e)
        {
            _resizer = new FormResizer(this);
        }

        private void GUIForm_SizeChanged(object sender, EventArgs e)
        {
            _resizer?.ResizeControls();
        }

        /// <summary>
        /// Handle the Click event for the Connect button on the main form.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

            mSerialPort = new Serial();

            if (!mSerialPort.OpenPort(comboBoxCOMPort.Text, baudRate))
            {
                Logger.LogMessage("Failed to open comm port!");
                mSerialPort.Close();
                mSerialPort = null;
            }

            Commands.Init(mSerialPort);

            if (mSerialPort is not null)
                mSerialPort.IncomingMessage += SerialPort_IncomingMessage;

            _configrationFile.SetValues("Port", new string[] { comboBoxCOMPort.Text });
            _configrationFile.Save();
        }

        /// <summary>
        /// Handle the event indicating an imcoming message has been received.
        /// Call ProcessIncomingMessage() on the GUI thread.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SerialPort_IncomingMessage(object? sender, IncomingMessageEventArgs e)
        {
            if (IsDisposed || !IsHandleCreated)
                return;

            if (InvokeRequired)
                Invoke(new ThreadStart(delegate { SerialPort_IncomingMessage(sender, e); }));
            else
                ProcessIncomingMessage(e.data);
        }

        private void Logger_LoggedMessage(object? sender, LoggerEventArgs e)
        {
            if (IsDisposed || !IsHandleCreated)
                return;

            if (InvokeRequired)
                Invoke(new ThreadStart(delegate { Logger_LoggedMessage(sender, e); }));
            else
            {
                listBoxDebugLogList.Items.Insert(0, e.Message);
            }
        }

        /// <summary>
        /// Close the communication port.
        /// </summary>
        public void ClosePort()
        {
            if (mSerialPort != null)
                mSerialPort.IncomingMessage -= SerialPort_IncomingMessage;
            mSerialPort?.Close();
            mSerialPort = null;
            Commands.Init(null);
        }

        /// <summary>
        /// One-second timer.
        /// Handle periodic operation of the form.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timerOneSecond_Tick(object sender, EventArgs e)
        {
            labelCOMStatus.BackColor = IsCOMPortOpen ? Color.Green : Color.Red;
            buttonConnect.Text = IsCOMPortOpen ? "Disconnect" : "Connect";

            toolStripStatusLabel1.Text = IsCOMPortOpen ? "Connected" : "Not Connected";

            switch (tabControl1.SelectedTab.Name)
            {
                case "tabPageTesting":
                    break;
                case "tabPageDebug":
                    TabDebug_Update();
                    break;
            }
        }

        /// <summary>
        /// Handle the DropDown event for the COM port combo box.
        /// Populate the dropdown list.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBoxCOMPort_DropDown(object sender, EventArgs e)
        {
            RefreshCOMPortList();
        }

        /// <summary>
        /// Update the list of COM ports found.  
        /// </summary>
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

    }
}
