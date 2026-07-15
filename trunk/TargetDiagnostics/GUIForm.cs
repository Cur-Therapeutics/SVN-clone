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

using System.IO.Ports;
using System.Net;
using System.Windows.Forms;
using Utilities;
using static CURDiags.Enums;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace CURDiags
{
    /// <summary>
    /// This is the main form of the Diags application. Form initialization and
    /// shared functionality are in this source file.
    /// </summary>
    public partial class GUIForm : Form
    {
        /// <summary>
        /// Serial port
        /// </summary>
        private Serial? mSerialPort;

        /// <summary>
        /// Get a flag indiating whether the communication channel is usable.
        /// </summary>
        public bool IsCOMPortOpen => mSerialPort != null && mSerialPort.IsOpen;

        /// <summary>
        /// Configuration file, used to store config params like the serial port and baud rate
        /// </summary>
        private const string ConfigrationFileName = "Configuration.csv";
        private readonly CsvFile _configrationFile = new CsvFile(ConfigrationFileName);

        /// <summary>
        /// Last directory assistance
        /// </summary>
        string mLastDirectory = "";

        /// <summary>
        /// Filename of file to load
        /// </summary>
        string mFileToLoad = "";

        /// <summary>
        /// Event handler for ACKs from the embedded
        /// </summary>
        static AutoResetEvent autoEvent = new AutoResetEvent(false);

        /// <summary>
        /// Construct an instance of the GUIForm. Perform one-time initialization.
        /// </summary>
        public GUIForm()
        {
            InitializeComponent();

            // Set the version number of the app in the title
            Text += $" {Version.Value}";

            // Set default comboBox selections
            comboBoxBaudRate.SelectedIndex = 0;
            comboBoxWindow.SelectedIndex = 0;
            comboBoxDisplayWindow.SelectedIndex = 0;
            comboBoxSlot.SelectedIndex = 0;
            comboBoxFlashReadSlot.SelectedIndex = 0;

            // Attach logger
            Logger.LoggedMessage += Logger_LoggedMessage;

            // Initialize comm port list if any are attached
            RefreshCOMPortList();
            if (string.IsNullOrEmpty(comboBoxCOMPort.Text))
                comboBoxCOMPort.Text = _configrationFile.GetValue("Port");

            // Populate data grid views with expected rows
            dataGridViewStatusMsg.Rows.Add("Firmware Version", "???");
            dataGridViewStatusMsg.Rows.Add("System Ticks", "???");
            dataGridViewStatusMsg.Rows.Add("Idle Ticks", "???");
            dataGridViewStatusMsg.Rows.Add("Skipped Ticks", "???");
            dataGridViewStatusMsg.Rows.Add("Min Idle", "???");
            dataGridViewStatusMsg.Rows.Add("Max Idle", "???");
            dataGridViewStatusMsg.Rows.Add("State", "???");
            dataGridViewStatusMsg.Rows.Add("Errors", "???");
            dataGridViewStatusMsg.Rows.Add("Health", "???");

            dataGridViewFlashRegisters.Rows.Add("Config Reg 1", "???");
            dataGridViewFlashRegisters.Rows.Add("Config Reg 2", "???");
            dataGridViewFlashRegisters.Rows.Add("Config Reg 3", "???");
            dataGridViewFlashRegisters.Rows.Add("Config Reg 4", "???");
            dataGridViewFlashRegisters.Rows.Add("Config Reg 5", "???");

            dataGridViewFlashIds.Rows.Add("Manufact. ID", "???");
            dataGridViewFlashIds.Rows.Add("Mem. Interface", "???");
            dataGridViewFlashIds.Rows.Add("Density", "???");
            dataGridViewFlashIds.Rows.Add("ID Len", "???");
            dataGridViewFlashIds.Rows.Add("Config", "???");
            dataGridViewFlashIds.Rows.Add("Family", "???");
            dataGridViewFlashIds.Rows.Add("Unique ID", "???? ????");

            dataGridViewBarometric.Rows.Add("Last Pressure (mmHg)", "????");
            dataGridViewBarometric.Rows.Add("Last Temp (C)", "????");
            dataGridViewBarometric.Rows.Add("PROG", "????");
            dataGridViewBarometric.Rows.Add("Sensitivity", "????");
            dataGridViewBarometric.Rows.Add("Offset", "????");
            dataGridViewBarometric.Rows.Add("tcoeffSens", "????");
            dataGridViewBarometric.Rows.Add("tcoeffOffset", "????");
            dataGridViewBarometric.Rows.Add("tref", "????");
            dataGridViewBarometric.Rows.Add("tempSens", "????");
        }

        /// <summary>
        /// Handle the Closing event of the main Form.
        /// </summary>
        private void GUIForm_FormClosing(object _, FormClosingEventArgs __)
        {
            Logger.LoggedMessage -= Logger_LoggedMessage;
            ClosePort();
        }

        private void buttonHello_Click(object sender, EventArgs e)
        {

        }

        private void buttonDebugClearList_Click(object sender, EventArgs e)
        {
            listBoxDebugLogList.Items.Clear();
        }

        /// <summary>
        /// Handle the Click event for the Connect button on the main form.
        /// </summary>
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
        private void timerOneSecond_Tick(object sender, EventArgs e)
        {
            // Update indicators
            buttonConnect.Text = IsCOMPortOpen ? "Disconnect" : "Connect";
            toolStripStatusLabel1.Text = IsCOMPortOpen ? "Connected" : "Not Connected";

            // If the com port is open, request status
            if (IsCOMPortOpen)
            {
                // Send periodic status messages, also battery
                Commands.SendCommand(eDiagnosticCommands.eDIAG_STATUS);
                Commands.SendCommand(eDiagnosticCommands.eDIAG_ADC_READ);

                // If we have not received message in a while we must not have good communications
                if (mLastMessageReceived.CompareTo(DateTime.Now.AddSeconds(-2)) < 0)
                {
                    UpdateLabelColor(labelCOMStatus, Color.Red);
                    UpdateLabelColor(labelSys, (Color.Gray));
                    UpdateLabelColor(labelFlash, (Color.Gray));
                    UpdateLabelColor(labelRam, (Color.Gray));
                    UpdateLabelColor(labelAdc, (Color.Gray));
                    UpdateLabelColor(label7124, (Color.Gray));
                    UpdateLabelColor(labelTouch, (Color.Gray));
                    UpdateLabelColor(labelRtc, (Color.Gray));
                    UpdateLabelColor(labelLcd, (Color.Gray));
                    UpdateLabelColor(labelStack, (Color.Gray));
                    UpdateLabelColor(labelAccel, (Color.Gray));
                    UpdateLabelColor(labelSpi, (Color.Gray));
                    UpdateLabelColor(labelI2C, (Color.Gray));
                    UpdateLabelColor(labelCatheter, (Color.Gray));
                }
                else
                    UpdateLabelColor(labelCOMStatus, Color.Green);
            }

            // Send periodic requests for data depending on the selected tab
            switch (tabControl1?.SelectedTab?.Name)
            {
                case "tabPageTesting":
                    break;
                case "tabPageDebug":
                    break;
                case "tabPageAccel":
                    Commands.SendCommand(eDiagnosticCommands.eDIAG_ACCEL_READ);
                    break;
                case "tabPageAdc":
                    break;
                case "tabPageAd7124":
                    Commands.SendCommand(eDiagnosticCommands.eDIAG_AD7124_READ_DATA);
                    break;
                case "tabPageRtc":
                    Commands.SendCommand(eDiagnosticCommands.eDIAG_RTC_STATUS);
                    break;
                case "tabPageTouch":
                    Commands.SendCommand(eDiagnosticCommands.eDIAG_TOUCH_READ);
                    break;
                case "tabPageBarometric":
                    Commands.SendCommand(eDiagnosticCommands.eDIAG_READ_BAROMETRIC);
                    break;
            }
        }

        /// <summary>
        /// Handle the DropDown event for the COM port combo box.
        /// Populate the dropdown list.
        /// </summary>
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

        private void buttonSelectFile_Click(object sender, EventArgs e)
        {
            // Fire up a file chooser to select 
            OpenFileDialog fileChooser = new OpenFileDialog();
            fileChooser.InitialDirectory = mLastDirectory;
            fileChooser.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
            fileChooser.FilterIndex = 2;
            fileChooser.RestoreDirectory = true;

            if (fileChooser.ShowDialog() == DialogResult.OK)
            {
                mFileToLoad = fileChooser.FileName;
                UpdateLabel(labelFileName, mFileToLoad);
            }
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            // Open file
            if (!File.Exists(mFileToLoad))
            {
                MessageBox.Show("No such file!");
                return;
            }

            // Convert to binary data
            List<byte> theData = new List<byte>();
            BitmapConverter.BitmapToRgbBinary(mFileToLoad, theData);
            byte[] rawBytes = theData.ToArray();

            // Calculate Starting Address
            // Each window is 320*240x4 bytes...
            int window = comboBoxWindow.SelectedIndex;
            UInt32 addr = (UInt32)(320 * 240 * 4 * window);
            UInt32 ramAddr = (UInt32)(320 * 240 * 4 * window);

            // Grab slot address here so we avoid cross thread operations
            UInt32 burnSlot = (UInt32)comboBoxSlot.SelectedIndex;

            // Send raw data to the embedded
            int bytesToSend = rawBytes.Length;
            int sentBytes = 0;
            UInt32 sendAddress = addr;
            UInt32 packetSize;
            const UInt32 MAX_PKG_SIZE = 256;

            System.Threading.ThreadPool.QueueUserWorkItem(delegate
            {
                bool isAcked = false;

                // Continue until all bytes are sent or we fail on retries
                while (sentBytes < bytesToSend)
                {
                    // Build the current packet
                    if (bytesToSend - sentBytes > MAX_PKG_SIZE)
                        packetSize = MAX_PKG_SIZE;
                    else
                        packetSize = (UInt32)(bytesToSend - sentBytes);

                    Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_LCD_DATA);
                    cmd.AddBytes(BitConverter.GetBytes(addr));          // Address
                    cmd.AddBytes(BitConverter.GetBytes(packetSize));    // Packet size
                    byte[] payload = new byte[packetSize];
                    Array.Copy(rawBytes, sentBytes, payload, 0, payload.Length);
                    cmd.AddBytes(payload);

                    // Send the packet to the embedded
                    Commands.SendCommand(cmd);

                    // Wait for an ACK

                    for (int i = 0; i < 5; i++)
                    {
                        // Resend on Timeout
                        if (autoEvent.WaitOne(500))
                        {
                            isAcked = true;
                            break;
                        }
                        Commands.SendCommand(cmd);
                    }
                    if (!isAcked)
                    {
                        // Fail on too many timeouts
                        UpdateLabel(labelLoadStatus, "Failed on too many retries! Address: " + addr);
                        return;
                    }
                    sentBytes += (int)packetSize;
                    addr += packetSize;

                    // Update progress bar and status
                    UpdateLabel(labelLoadStatus, "Status: Loading Address " + addr);
                    UpdateProgressBar(progressBarLoading, sentBytes, bytesToSend);
                }

                // Send burn command
                UpdateLabel(labelLoadStatus, "Status: Burning... ");
                Commands.sRequest burnCmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_FLASH_BURN);
                burnCmd.AddBytes(BitConverter.GetBytes(ramAddr));
                burnCmd.AddBytes(BitConverter.GetBytes(burnSlot));
                burnCmd.AddBytes(BitConverter.GetBytes((UInt32)(320 * 240 * 4)));

                Commands.SendCommand(burnCmd);
                if (autoEvent.WaitOne(20000))
                {
                    UpdateLabel(labelLoadStatus, "Status: Burning Completed.");
                }
                else
                {
                    UpdateLabel(labelLoadStatus, "Status: Burn Failed!");
                }

            });  // end QueuWorkerItem

        } // end ButtonLoad_Click

        private void buttonLcdSetWindow_Click(object sender, EventArgs e)
        {
            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_LCD_SET_DISPLAY);
            cmd.AddByte((byte)comboBoxDisplayWindow.SelectedIndex);
            Commands.SendCommand(cmd);
        }

        private void buttonDisplayUp_Click(object sender, EventArgs e)
        {
            if (comboBoxDisplayWindow.SelectedIndex < comboBoxDisplayWindow.Items.Count - 1)
            {
                comboBoxDisplayWindow.SelectedIndex++;
                buttonLcdSetWindow_Click(sender, e);
            }
        }

        private void buttonDisplayDDown_Click(object sender, EventArgs e)
        {
            if (comboBoxDisplayWindow.SelectedIndex > 0)
            {
                comboBoxDisplayWindow.SelectedIndex--;
                buttonLcdSetWindow_Click(sender, e);
            }
        }

        private void buttonSetBacklight_Click(object sender, EventArgs e)
        {
            UInt16 val;
            bool goodInput = UInt16.TryParse(textBoxBackLightValue.Text, out val);

            if (!goodInput)
                return;
            if (val < 0 || val > 4000)
                return;

            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_LCD_BKLIGHT_SET);
            cmd.AddBytes(BitConverter.GetBytes(val));
            Commands.SendCommand(cmd);
        }

        private void buttonBackLightOn_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_LCD_BKLIGHT_ON);
        }

        private void buttonBackLightOff_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_LCD_BKLIGHT_OFF);
        }

        private void buttonBacklightUp_Click(object sender, EventArgs e)
        {
            UInt16 val;
            bool goodInput = UInt16.TryParse(textBoxBackLightValue.Text, out val);
            if (!goodInput)
                return;
            val += 100;
            if (val > 4000)
                val = 4000;
            textBoxBackLightValue.Text = val.ToString();
            buttonSetBacklight_Click(sender, e);
        }

        private void buttonBackLightDown_Click(object sender, EventArgs e)
        {
            UInt16 val;
            bool goodInput = UInt16.TryParse(textBoxBackLightValue.Text, out val);
            if (!goodInput)
                return;

            if (val > 100)
                val -= 100;
            else
                val = 0;
            textBoxBackLightValue.Text = val.ToString();
            buttonSetBacklight_Click(sender, e);
        }

        private void buttonAccelRead_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_ACCEL_READ);
        }

        private void buttonAD7124Read_Click(object sender, EventArgs e)
        {
            UpdateTextBox(textBoxAd7124CountsHex, "");
            UpdateTextBox(textBoxAd7124CountsDec, "");
            UpdateTextBox(textBoxAd7124Volts, "");
            UpdateTextBox(textBoxAd7124mmHg, "");
            Commands.SendCommand(eDiagnosticCommands.eDIAG_AD7124_READ_DATA);
        }

        private void buttonAd7124StatusRead_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_AD7124_GET_STATUS);
        }

        private void buttonAd7124Reset_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_AD7124_RESET);
        }

        private void buttonFlashGetStatus_Click(object sender, EventArgs e)
        {
            // Clear previous inputs...
            int r = 0;
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "???";

            r = 0;
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "???";
            Commands.SendCommand(eDiagnosticCommands.eDIAG_FLASH_STATUS);
        }

        private void buttonRtcRead_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_RTC_STATUS);
        }

        private void buttonRtcWrite_Click(object sender, EventArgs e)
        {
            byte hour, min, sec;
            bool goodInput = byte.TryParse(textBoxRtcHourWrite.Text, out hour);
            goodInput |= byte.TryParse(textBoxRtcMinWrite.Text, out min);
            goodInput |= byte.TryParse(textBoxRtcSecWrite.Text, out sec);

            if (!goodInput)
                return;

            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_RTC_WRITE);
            cmd.AddByte(0xFF); cmd.AddByte(0xFF); cmd.AddByte(0xFF); cmd.AddByte(0xFF); // Status
            cmd.AddByte((hour));
            cmd.AddByte((min));
            cmd.AddByte((sec));
            cmd.AddByte(0x0); cmd.AddByte(0x0); cmd.AddByte(0x0); cmd.AddByte(0x0);     // Blank month, day, year, format
            Commands.SendCommand(cmd);
        }

        private void buttonFlashReset_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_FLASH_RESET);
        }

        private void buttonFlashClearProg_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_FLASH_CLEAR_PROG);
        }

        private void buttonBatRead_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_ADC_READ);
        }

        private void buttonTouchRead_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_TOUCH_READ);
        }

        private void buttonFlashTest_Click(object sender, EventArgs e)
        {
            Commands.SendCommand(eDiagnosticCommands.eDIAG_FLASH_TEST);
        }

        private void comboBoxFlashReadSlot_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Calculate new address for the flash read address
            UInt32 address = 0x40000 + (UInt32)(comboBoxFlashReadSlot.SelectedIndex * (256 * 1024 * 2));
            UpdateTextBox(textBoxFlashReadAddress, address.ToString());
        }

        private void buttonFlashRead_Click(object sender, EventArgs e)
        {
            UInt32 address;
            bool dataGood = UInt32.TryParse(textBoxFlashReadAddress.Text, out address);

            if (!dataGood)
            {
                MessageBox.Show("Invalid address!");
                return;
            }

            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_FLASH_READ);
            cmd.AddBytes(BitConverter.GetBytes(address));
            cmd.AddBytes(BitConverter.GetBytes((UInt32)512));
            Commands.SendCommand(cmd);

        }

        private void buttonSetState_Click(object sender, EventArgs e)
        {
            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_SET_STATE);
            cmd.AddBytes(BitConverter.GetBytes((UInt32)comboBoxStateSelect.SelectedIndex));
            Commands.SendCommand(cmd);
        }

        private void buttonTouchDebug_Click(object sender, EventArgs e)
        {
            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_TOUCH_MODE);
            cmd.AddByte(2);
            Commands.SendCommand(cmd);
        }

        private void buttonTouchIdle_Click(object sender, EventArgs e)
        {
            Commands.sRequest cmd = new Commands.sRequest(eDiagnosticCommands.eDIAG_TOUCH_MODE);
            cmd.AddByte(0);
            Commands.SendCommand(cmd);
        }
    }  // end class
}  // end namespace
