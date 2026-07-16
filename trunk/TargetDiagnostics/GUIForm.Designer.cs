using System.IO.Ports;

namespace CURDiags
{
    partial class GUIForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GUIForm));
            tabControl1 = new TabControl();
            tabPageStatus = new TabPage();
            groupBox16 = new GroupBox();
            comboBoxStateSelect = new ComboBox();
            buttonSetState = new Button();
            labelSystemState = new Label();
            groupBox2 = new GroupBox();
            dataGridViewStatusMsg = new DataGridView();
            Parameter = new DataGridViewTextBoxColumn();
            Value1 = new DataGridViewTextBoxColumn();
            label1 = new Label();
            listBox1 = new ListBox();
            tabPageDebug = new TabPage();
            dataGridViewDebugStats = new DataGridView();
            NameCol = new DataGridViewTextBoxColumn();
            Value = new DataGridViewTextBoxColumn();
            buttonDebugClearList = new Button();
            listBoxDebugLogList = new ListBox();
            tabPageLCD = new TabPage();
            groupBox5 = new GroupBox();
            buttonBackLightOn = new Button();
            buttonBackLightOff = new Button();
            buttonBackLightDown = new Button();
            buttonBacklightUp = new Button();
            textBoxBackLightValue = new TextBox();
            buttonSetBacklight = new Button();
            groupBox4 = new GroupBox();
            buttonDisplayDDown = new Button();
            buttonDisplayUp = new Button();
            label3 = new Label();
            comboBoxDisplayWindow = new ComboBox();
            buttonLcdSetWindow = new Button();
            groupBox3 = new GroupBox();
            label41 = new Label();
            comboBoxSlot = new ComboBox();
            labelLoadStatus = new Label();
            label2 = new Label();
            comboBoxWindow = new ComboBox();
            buttonLoad = new Button();
            progressBarLoading = new ProgressBar();
            labelFileName = new Label();
            buttonSelectFile = new Button();
            tabPageTouch = new TabPage();
            buttonClearTouchEvents = new Button();
            listBoxTouchEvents = new ListBox();
            groupBox9 = new GroupBox();
            buttonTouchIdle = new Button();
            buttonTouchDebug = new Button();
            textBoxTouchVendorId = new TextBox();
            label25 = new Label();
            textBoxTouchFirmwareId = new TextBox();
            label24 = new Label();
            textBoxTouchVersionLow = new TextBox();
            label23 = new Label();
            textBoxTouchVersionHigh = new TextBox();
            label22 = new Label();
            buttonTouchInit = new Button();
            buttonTouchStatus = new Button();
            buttonTouchReadAdv = new Button();
            groupBox8 = new GroupBox();
            label27 = new Label();
            label26 = new Label();
            buttonTouchRead = new Button();
            buttonTouchClear = new Button();
            textBoxTouchYMax = new TextBox();
            textBoxTouchYMin = new TextBox();
            label20 = new Label();
            textBoxTouchXMax = new TextBox();
            textBoxTouchXMin = new TextBox();
            label21 = new Label();
            textBoxTouchArea = new TextBox();
            label18 = new Label();
            textBoxTouchWeight = new TextBox();
            label19 = new Label();
            textBoxTouchYRaw = new TextBox();
            textBoxTouchYPosition = new TextBox();
            label17 = new Label();
            textBoxTouchXRaw = new TextBox();
            textBoxTouchXPosition = new TextBox();
            label16 = new Label();
            textBoxTouchEvent = new TextBox();
            label15 = new Label();
            textBoxTouchPoints = new TextBox();
            label14 = new Label();
            tabPageAccel = new TabPage();
            groupBox6 = new GroupBox();
            buttonAccelRead = new Button();
            textBoxAccelZ = new TextBox();
            label4 = new Label();
            textBoxAccelY = new TextBox();
            label5 = new Label();
            textBoxAccelX = new TextBox();
            label6 = new Label();
            tabPageRtc = new TabPage();
            groupBox7 = new GroupBox();
            textBoxRtcSecRead = new TextBox();
            textBoxRtcSecWrite = new TextBox();
            label10 = new Label();
            textBoxRtcMinRead = new TextBox();
            textBoxRtcMinWrite = new TextBox();
            label9 = new Label();
            textBoxRtcHourRead = new TextBox();
            buttonRtcRead = new Button();
            buttonRtcWrite = new Button();
            textBoxRtcHourWrite = new TextBox();
            label8 = new Label();
            tabPageAd7124 = new TabPage();
            groupBox11 = new GroupBox();
            buttonAd7124Reset = new Button();
            buttonAd7124StatusRead = new Button();
            textBoxAd7124Channel = new TextBox();
            label37 = new Label();
            textBoxAd7124ErrorEn = new TextBox();
            label38 = new Label();
            textBoxAd7124Filter = new TextBox();
            label35 = new Label();
            textBoxAd7124Config = new TextBox();
            label36 = new Label();
            textBoxAd7124Offset = new TextBox();
            label34 = new Label();
            textBoxAd7124Error = new TextBox();
            label31 = new Label();
            textBoxAd7124Id = new TextBox();
            label32 = new Label();
            textBoxAd7124Io2 = new TextBox();
            label29 = new Label();
            textBoxAd7124Io1 = new TextBox();
            label30 = new Label();
            textBoxAd7124Control = new TextBox();
            label28 = new Label();
            textBoxAd7124Status = new TextBox();
            label13 = new Label();
            groupBox10 = new GroupBox();
            textBoxAd7124mmHg = new TextBox();
            label40 = new Label();
            buttonAD7124Read = new Button();
            textBoxAd7124Volts = new TextBox();
            label12 = new Label();
            textBoxAd7124CountsDec = new TextBox();
            label11 = new Label();
            textBoxAd7124CountsHex = new TextBox();
            label7 = new Label();
            tabPageFlash = new TabPage();
            groupBox15 = new GroupBox();
            textBoxFlashReadData = new TextBox();
            buttonFlashRead = new Button();
            label46 = new Label();
            textBoxFlashReadAddress = new TextBox();
            label45 = new Label();
            comboBoxFlashReadSlot = new ComboBox();
            groupBox13 = new GroupBox();
            buttonFlashTest = new Button();
            buttonFlashClearProg = new Button();
            buttonFlashReset = new Button();
            groupBox12 = new GroupBox();
            dataGridViewFlashIds = new DataGridView();
            dataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
            dataGridViewTextBoxColumn2 = new DataGridViewTextBoxColumn();
            buttonFlashGetStatus = new Button();
            dataGridViewFlashRegisters = new DataGridView();
            Register = new DataGridViewTextBoxColumn();
            RegValues = new DataGridViewTextBoxColumn();
            textBoxFlashStatus2 = new TextBox();
            label39 = new Label();
            textBoxFlashStatus1 = new TextBox();
            label33 = new Label();
            tabPageAdc = new TabPage();
            groupBox14 = new GroupBox();
            buttonBatRead = new Button();
            textBoxBatVolts = new TextBox();
            label42 = new Label();
            textBoxBatCountDec = new TextBox();
            label43 = new Label();
            textBoxBatCountsHex = new TextBox();
            label44 = new Label();
            tabPageBarometric = new TabPage();
            dataGridViewBarometric = new DataGridView();
            dataGridViewTextBoxColumn3 = new DataGridViewTextBoxColumn();
            dataGridViewTextBoxColumn4 = new DataGridViewTextBoxColumn();
            tabPageDataLog = new TabPage();
            groupBox18 = new GroupBox();
            labelDownloadStatus = new Label();
            buttonDownload = new Button();
            textBoxStartSample = new TextBox();
            label50 = new Label();
            groupBox17 = new GroupBox();
            buttonDataLogReadEventLog = new Button();
            textBoxDataLogSectorEnd = new TextBox();
            label47 = new Label();
            textBoxDataLogSectorBegin = new TextBox();
            label48 = new Label();
            textBoxDataLogSamples = new TextBox();
            label49 = new Label();
            labelCOMStatus = new Label();
            buttonConnect = new Button();
            comboBoxCOMPort = new ComboBox();
            timerOneSecond = new System.Windows.Forms.Timer(components);
            comboBoxBaudRate = new ComboBox();
            statusStrip1 = new StatusStrip();
            toolStripStatusLabel1 = new ToolStripStatusLabel();
            groupBox1 = new GroupBox();
            labelRtc = new Label();
            labelCatheter = new Label();
            labelI2C = new Label();
            labelSpi = new Label();
            labelAccel = new Label();
            labelStack = new Label();
            labelLcd = new Label();
            labelTouch = new Label();
            label7124 = new Label();
            labelAdc = new Label();
            labelFlash = new Label();
            labelRam = new Label();
            labelSys = new Label();
            progressBarDataDownload = new ProgressBar();
            tabControl1.SuspendLayout();
            tabPageStatus.SuspendLayout();
            groupBox16.SuspendLayout();
            groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridViewStatusMsg).BeginInit();
            tabPageDebug.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridViewDebugStats).BeginInit();
            tabPageLCD.SuspendLayout();
            groupBox5.SuspendLayout();
            groupBox4.SuspendLayout();
            groupBox3.SuspendLayout();
            tabPageTouch.SuspendLayout();
            groupBox9.SuspendLayout();
            groupBox8.SuspendLayout();
            tabPageAccel.SuspendLayout();
            groupBox6.SuspendLayout();
            tabPageRtc.SuspendLayout();
            groupBox7.SuspendLayout();
            tabPageAd7124.SuspendLayout();
            groupBox11.SuspendLayout();
            groupBox10.SuspendLayout();
            tabPageFlash.SuspendLayout();
            groupBox15.SuspendLayout();
            groupBox13.SuspendLayout();
            groupBox12.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridViewFlashIds).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewFlashRegisters).BeginInit();
            tabPageAdc.SuspendLayout();
            groupBox14.SuspendLayout();
            tabPageBarometric.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridViewBarometric).BeginInit();
            tabPageDataLog.SuspendLayout();
            groupBox18.SuspendLayout();
            groupBox17.SuspendLayout();
            statusStrip1.SuspendLayout();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // tabControl1
            // 
            tabControl1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            tabControl1.Controls.Add(tabPageStatus);
            tabControl1.Controls.Add(tabPageDebug);
            tabControl1.Controls.Add(tabPageLCD);
            tabControl1.Controls.Add(tabPageTouch);
            tabControl1.Controls.Add(tabPageAccel);
            tabControl1.Controls.Add(tabPageRtc);
            tabControl1.Controls.Add(tabPageAd7124);
            tabControl1.Controls.Add(tabPageFlash);
            tabControl1.Controls.Add(tabPageAdc);
            tabControl1.Controls.Add(tabPageBarometric);
            tabControl1.Controls.Add(tabPageDataLog);
            tabControl1.Location = new Point(12, 95);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(1031, 550);
            tabControl1.TabIndex = 0;
            // 
            // tabPageStatus
            // 
            tabPageStatus.Controls.Add(groupBox16);
            tabPageStatus.Controls.Add(groupBox2);
            tabPageStatus.Controls.Add(label1);
            tabPageStatus.Controls.Add(listBox1);
            tabPageStatus.Location = new Point(4, 24);
            tabPageStatus.Name = "tabPageStatus";
            tabPageStatus.Padding = new Padding(3);
            tabPageStatus.Size = new Size(1023, 522);
            tabPageStatus.TabIndex = 0;
            tabPageStatus.Text = "Status";
            tabPageStatus.UseVisualStyleBackColor = true;
            // 
            // groupBox16
            // 
            groupBox16.Controls.Add(comboBoxStateSelect);
            groupBox16.Controls.Add(buttonSetState);
            groupBox16.Controls.Add(labelSystemState);
            groupBox16.Location = new Point(446, 109);
            groupBox16.Name = "groupBox16";
            groupBox16.Size = new Size(571, 200);
            groupBox16.TabIndex = 4;
            groupBox16.TabStop = false;
            groupBox16.Text = "System State";
            // 
            // comboBoxStateSelect
            // 
            comboBoxStateSelect.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comboBoxStateSelect.FormattingEnabled = true;
            comboBoxStateSelect.Items.AddRange(new object[] { "eSTATE_POST", "eSTATE_SPLASH", "eSTATE_READY_TO_CONNECT", "eSTATE_SELECT_UNITS", "eSTATE_MEASURING", "eSTATE_COMPLETE", "eSTATE_TEST", "eSTATE_ERROR" });
            comboBoxStateSelect.Location = new Point(6, 74);
            comboBoxStateSelect.Name = "comboBoxStateSelect";
            comboBoxStateSelect.Size = new Size(206, 29);
            comboBoxStateSelect.TabIndex = 9;
            // 
            // buttonSetState
            // 
            buttonSetState.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonSetState.Location = new Point(6, 109);
            buttonSetState.Name = "buttonSetState";
            buttonSetState.Size = new Size(206, 52);
            buttonSetState.TabIndex = 8;
            buttonSetState.Text = "Set State";
            buttonSetState.UseVisualStyleBackColor = true;
            buttonSetState.Click += buttonSetState_Click;
            // 
            // labelSystemState
            // 
            labelSystemState.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            labelSystemState.Location = new Point(6, 19);
            labelSystemState.Name = "labelSystemState";
            labelSystemState.Size = new Size(206, 39);
            labelSystemState.TabIndex = 6;
            labelSystemState.Text = "UNKNOWN";
            labelSystemState.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(dataGridViewStatusMsg);
            groupBox2.Location = new Point(6, 6);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(434, 416);
            groupBox2.TabIndex = 3;
            groupBox2.TabStop = false;
            groupBox2.Text = "System";
            // 
            // dataGridViewStatusMsg
            // 
            dataGridViewStatusMsg.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewStatusMsg.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            dataGridViewStatusMsg.Columns.AddRange(new DataGridViewColumn[] { Parameter, Value1 });
            dataGridViewStatusMsg.Location = new Point(6, 22);
            dataGridViewStatusMsg.Name = "dataGridViewStatusMsg";
            dataGridViewStatusMsg.ReadOnly = true;
            dataGridViewStatusMsg.RowHeadersVisible = false;
            dataGridViewStatusMsg.Size = new Size(422, 296);
            dataGridViewStatusMsg.TabIndex = 0;
            // 
            // Parameter
            // 
            Parameter.HeaderText = "Parameter";
            Parameter.Name = "Parameter";
            Parameter.ReadOnly = true;
            // 
            // Value1
            // 
            Value1.HeaderText = "Value";
            Value1.Name = "Value1";
            Value1.ReadOnly = true;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(446, 6);
            label1.Name = "label1";
            label1.Size = new Size(112, 15);
            label1.TabIndex = 2;
            label1.Text = "Incoming messages";
            // 
            // listBox1
            // 
            listBox1.FormattingEnabled = true;
            listBox1.Location = new Point(446, 24);
            listBox1.Name = "listBox1";
            listBox1.Size = new Size(571, 79);
            listBox1.TabIndex = 1;
            // 
            // tabPageDebug
            // 
            tabPageDebug.Controls.Add(dataGridViewDebugStats);
            tabPageDebug.Controls.Add(buttonDebugClearList);
            tabPageDebug.Controls.Add(listBoxDebugLogList);
            tabPageDebug.Location = new Point(4, 24);
            tabPageDebug.Name = "tabPageDebug";
            tabPageDebug.Size = new Size(1023, 522);
            tabPageDebug.TabIndex = 1;
            tabPageDebug.Text = "Debug";
            tabPageDebug.UseVisualStyleBackColor = true;
            // 
            // dataGridViewDebugStats
            // 
            dataGridViewDebugStats.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewDebugStats.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            dataGridViewDebugStats.Columns.AddRange(new DataGridViewColumn[] { NameCol, Value });
            dataGridViewDebugStats.Location = new Point(459, 8);
            dataGridViewDebugStats.Name = "dataGridViewDebugStats";
            dataGridViewDebugStats.RowHeadersVisible = false;
            dataGridViewDebugStats.Size = new Size(451, 280);
            dataGridViewDebugStats.TabIndex = 4;
            // 
            // NameCol
            // 
            NameCol.HeaderText = "Description";
            NameCol.Name = "NameCol";
            // 
            // Value
            // 
            Value.HeaderText = "Value";
            Value.Name = "Value";
            // 
            // buttonDebugClearList
            // 
            buttonDebugClearList.Location = new Point(7, 321);
            buttonDebugClearList.Name = "buttonDebugClearList";
            buttonDebugClearList.Size = new Size(75, 23);
            buttonDebugClearList.TabIndex = 3;
            buttonDebugClearList.Text = "Clear";
            buttonDebugClearList.UseVisualStyleBackColor = true;
            buttonDebugClearList.Click += buttonDebugClearList_Click;
            // 
            // listBoxDebugLogList
            // 
            listBoxDebugLogList.FormattingEnabled = true;
            listBoxDebugLogList.Location = new Point(7, 8);
            listBoxDebugLogList.Name = "listBoxDebugLogList";
            listBoxDebugLogList.Size = new Size(443, 289);
            listBoxDebugLogList.TabIndex = 2;
            // 
            // tabPageLCD
            // 
            tabPageLCD.Controls.Add(groupBox5);
            tabPageLCD.Controls.Add(groupBox4);
            tabPageLCD.Controls.Add(groupBox3);
            tabPageLCD.Location = new Point(4, 24);
            tabPageLCD.Name = "tabPageLCD";
            tabPageLCD.Padding = new Padding(3);
            tabPageLCD.Size = new Size(1023, 522);
            tabPageLCD.TabIndex = 2;
            tabPageLCD.Text = "LCD";
            tabPageLCD.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            groupBox5.Controls.Add(buttonBackLightOn);
            groupBox5.Controls.Add(buttonBackLightOff);
            groupBox5.Controls.Add(buttonBackLightDown);
            groupBox5.Controls.Add(buttonBacklightUp);
            groupBox5.Controls.Add(textBoxBackLightValue);
            groupBox5.Controls.Add(buttonSetBacklight);
            groupBox5.Location = new Point(581, 6);
            groupBox5.Name = "groupBox5";
            groupBox5.Size = new Size(170, 252);
            groupBox5.TabIndex = 2;
            groupBox5.TabStop = false;
            groupBox5.Text = "Backlight";
            // 
            // buttonBackLightOn
            // 
            buttonBackLightOn.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            buttonBackLightOn.Location = new Point(6, 159);
            buttonBackLightOn.Name = "buttonBackLightOn";
            buttonBackLightOn.Size = new Size(158, 42);
            buttonBackLightOn.TabIndex = 13;
            buttonBackLightOn.Text = "ON";
            buttonBackLightOn.UseVisualStyleBackColor = true;
            buttonBackLightOn.Click += buttonBackLightOn_Click;
            // 
            // buttonBackLightOff
            // 
            buttonBackLightOff.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            buttonBackLightOff.Location = new Point(6, 204);
            buttonBackLightOff.Name = "buttonBackLightOff";
            buttonBackLightOff.Size = new Size(158, 42);
            buttonBackLightOff.TabIndex = 12;
            buttonBackLightOff.Text = "OFF";
            buttonBackLightOff.UseVisualStyleBackColor = true;
            buttonBackLightOff.Click += buttonBackLightOff_Click;
            // 
            // buttonBackLightDown
            // 
            buttonBackLightDown.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            buttonBackLightDown.Location = new Point(83, 99);
            buttonBackLightDown.Name = "buttonBackLightDown";
            buttonBackLightDown.Size = new Size(72, 42);
            buttonBackLightDown.TabIndex = 11;
            buttonBackLightDown.Text = "-";
            buttonBackLightDown.UseVisualStyleBackColor = true;
            buttonBackLightDown.Click += buttonBackLightDown_Click;
            // 
            // buttonBacklightUp
            // 
            buttonBacklightUp.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            buttonBacklightUp.Location = new Point(6, 99);
            buttonBacklightUp.Name = "buttonBacklightUp";
            buttonBacklightUp.Size = new Size(71, 42);
            buttonBacklightUp.TabIndex = 10;
            buttonBacklightUp.Text = "+\r\n";
            buttonBacklightUp.UseVisualStyleBackColor = true;
            buttonBacklightUp.Click += buttonBacklightUp_Click;
            // 
            // textBoxBackLightValue
            // 
            textBoxBackLightValue.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxBackLightValue.Location = new Point(6, 64);
            textBoxBackLightValue.Name = "textBoxBackLightValue";
            textBoxBackLightValue.Size = new Size(154, 29);
            textBoxBackLightValue.TabIndex = 2;
            textBoxBackLightValue.Text = "4000";
            // 
            // buttonSetBacklight
            // 
            buttonSetBacklight.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonSetBacklight.Location = new Point(6, 22);
            buttonSetBacklight.Name = "buttonSetBacklight";
            buttonSetBacklight.Size = new Size(154, 36);
            buttonSetBacklight.TabIndex = 1;
            buttonSetBacklight.Text = "Set Backlight";
            buttonSetBacklight.UseVisualStyleBackColor = true;
            buttonSetBacklight.Click += buttonSetBacklight_Click;
            // 
            // groupBox4
            // 
            groupBox4.Controls.Add(buttonDisplayDDown);
            groupBox4.Controls.Add(buttonDisplayUp);
            groupBox4.Controls.Add(label3);
            groupBox4.Controls.Add(comboBoxDisplayWindow);
            groupBox4.Controls.Add(buttonLcdSetWindow);
            groupBox4.Location = new Point(357, 6);
            groupBox4.Name = "groupBox4";
            groupBox4.Size = new Size(218, 252);
            groupBox4.TabIndex = 1;
            groupBox4.TabStop = false;
            groupBox4.Text = "Display";
            // 
            // buttonDisplayDDown
            // 
            buttonDisplayDDown.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            buttonDisplayDDown.Location = new Point(113, 144);
            buttonDisplayDDown.Name = "buttonDisplayDDown";
            buttonDisplayDDown.Size = new Size(99, 42);
            buttonDisplayDDown.TabIndex = 9;
            buttonDisplayDDown.Text = "-";
            buttonDisplayDDown.UseVisualStyleBackColor = true;
            buttonDisplayDDown.Click += buttonDisplayDDown_Click;
            // 
            // buttonDisplayUp
            // 
            buttonDisplayUp.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            buttonDisplayUp.Location = new Point(6, 144);
            buttonDisplayUp.Name = "buttonDisplayUp";
            buttonDisplayUp.Size = new Size(99, 42);
            buttonDisplayUp.TabIndex = 8;
            buttonDisplayUp.Text = "+\r\n";
            buttonDisplayUp.UseVisualStyleBackColor = true;
            buttonDisplayUp.Click += buttonDisplayUp_Click;
            // 
            // label3
            // 
            label3.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label3.Location = new Point(6, 22);
            label3.Name = "label3";
            label3.Size = new Size(206, 26);
            label3.TabIndex = 7;
            label3.Text = "Display Window";
            label3.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // comboBoxDisplayWindow
            // 
            comboBoxDisplayWindow.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comboBoxDisplayWindow.FormattingEnabled = true;
            comboBoxDisplayWindow.Items.AddRange(new object[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" });
            comboBoxDisplayWindow.Location = new Point(6, 51);
            comboBoxDisplayWindow.Name = "comboBoxDisplayWindow";
            comboBoxDisplayWindow.Size = new Size(206, 29);
            comboBoxDisplayWindow.TabIndex = 6;
            // 
            // buttonLcdSetWindow
            // 
            buttonLcdSetWindow.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonLcdSetWindow.Location = new Point(6, 86);
            buttonLcdSetWindow.Name = "buttonLcdSetWindow";
            buttonLcdSetWindow.Size = new Size(206, 52);
            buttonLcdSetWindow.TabIndex = 1;
            buttonLcdSetWindow.Text = "Set Display Window";
            buttonLcdSetWindow.UseVisualStyleBackColor = true;
            buttonLcdSetWindow.Click += buttonLcdSetWindow_Click;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(label41);
            groupBox3.Controls.Add(comboBoxSlot);
            groupBox3.Controls.Add(labelLoadStatus);
            groupBox3.Controls.Add(label2);
            groupBox3.Controls.Add(comboBoxWindow);
            groupBox3.Controls.Add(buttonLoad);
            groupBox3.Controls.Add(progressBarLoading);
            groupBox3.Controls.Add(labelFileName);
            groupBox3.Controls.Add(buttonSelectFile);
            groupBox3.Location = new Point(6, 6);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(345, 416);
            groupBox3.TabIndex = 0;
            groupBox3.TabStop = false;
            groupBox3.Text = "Data Loader";
            // 
            // label41
            // 
            label41.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label41.Location = new Point(210, 83);
            label41.Name = "label41";
            label41.Size = new Size(121, 26);
            label41.TabIndex = 8;
            label41.Text = "Slot";
            label41.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // comboBoxSlot
            // 
            comboBoxSlot.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comboBoxSlot.FormattingEnabled = true;
            comboBoxSlot.Items.AddRange(new object[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" });
            comboBoxSlot.Location = new Point(210, 112);
            comboBoxSlot.Name = "comboBoxSlot";
            comboBoxSlot.Size = new Size(121, 29);
            comboBoxSlot.TabIndex = 7;
            // 
            // labelLoadStatus
            // 
            labelLoadStatus.AutoSize = true;
            labelLoadStatus.Location = new Point(6, 166);
            labelLoadStatus.Name = "labelLoadStatus";
            labelLoadStatus.Size = new Size(45, 15);
            labelLoadStatus.TabIndex = 6;
            labelLoadStatus.Text = "Status: ";
            // 
            // label2
            // 
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label2.Location = new Point(210, 16);
            label2.Name = "label2";
            label2.Size = new Size(121, 26);
            label2.TabIndex = 5;
            label2.Text = "Window";
            label2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // comboBoxWindow
            // 
            comboBoxWindow.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comboBoxWindow.FormattingEnabled = true;
            comboBoxWindow.Items.AddRange(new object[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" });
            comboBoxWindow.Location = new Point(210, 45);
            comboBoxWindow.Name = "comboBoxWindow";
            comboBoxWindow.Size = new Size(121, 29);
            comboBoxWindow.TabIndex = 4;
            // 
            // buttonLoad
            // 
            buttonLoad.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonLoad.Location = new Point(108, 22);
            buttonLoad.Name = "buttonLoad";
            buttonLoad.Size = new Size(96, 52);
            buttonLoad.TabIndex = 3;
            buttonLoad.Text = "Load";
            buttonLoad.UseVisualStyleBackColor = true;
            buttonLoad.Click += buttonLoad_Click;
            // 
            // progressBarLoading
            // 
            progressBarLoading.Location = new Point(6, 271);
            progressBarLoading.Name = "progressBarLoading";
            progressBarLoading.Size = new Size(325, 42);
            progressBarLoading.TabIndex = 2;
            // 
            // labelFileName
            // 
            labelFileName.Location = new Point(6, 226);
            labelFileName.Name = "labelFileName";
            labelFileName.Size = new Size(325, 42);
            labelFileName.TabIndex = 1;
            labelFileName.Text = "File Name...";
            // 
            // buttonSelectFile
            // 
            buttonSelectFile.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonSelectFile.Location = new Point(6, 22);
            buttonSelectFile.Name = "buttonSelectFile";
            buttonSelectFile.Size = new Size(96, 52);
            buttonSelectFile.TabIndex = 0;
            buttonSelectFile.Text = "Select File";
            buttonSelectFile.UseVisualStyleBackColor = true;
            buttonSelectFile.Click += buttonSelectFile_Click;
            // 
            // tabPageTouch
            // 
            tabPageTouch.Controls.Add(buttonClearTouchEvents);
            tabPageTouch.Controls.Add(listBoxTouchEvents);
            tabPageTouch.Controls.Add(groupBox9);
            tabPageTouch.Controls.Add(groupBox8);
            tabPageTouch.Location = new Point(4, 24);
            tabPageTouch.Name = "tabPageTouch";
            tabPageTouch.Padding = new Padding(3);
            tabPageTouch.Size = new Size(1023, 522);
            tabPageTouch.TabIndex = 3;
            tabPageTouch.Text = "Touch";
            tabPageTouch.UseVisualStyleBackColor = true;
            // 
            // buttonClearTouchEvents
            // 
            buttonClearTouchEvents.Location = new Point(902, 208);
            buttonClearTouchEvents.Name = "buttonClearTouchEvents";
            buttonClearTouchEvents.Size = new Size(75, 171);
            buttonClearTouchEvents.TabIndex = 5;
            buttonClearTouchEvents.Text = "Clear";
            buttonClearTouchEvents.UseVisualStyleBackColor = true;
            // 
            // listBoxTouchEvents
            // 
            listBoxTouchEvents.FormattingEnabled = true;
            listBoxTouchEvents.HorizontalScrollbar = true;
            listBoxTouchEvents.Location = new Point(304, 210);
            listBoxTouchEvents.Name = "listBoxTouchEvents";
            listBoxTouchEvents.Size = new Size(592, 169);
            listBoxTouchEvents.TabIndex = 4;
            // 
            // groupBox9
            // 
            groupBox9.Controls.Add(buttonTouchIdle);
            groupBox9.Controls.Add(buttonTouchDebug);
            groupBox9.Controls.Add(textBoxTouchVendorId);
            groupBox9.Controls.Add(label25);
            groupBox9.Controls.Add(textBoxTouchFirmwareId);
            groupBox9.Controls.Add(label24);
            groupBox9.Controls.Add(textBoxTouchVersionLow);
            groupBox9.Controls.Add(label23);
            groupBox9.Controls.Add(textBoxTouchVersionHigh);
            groupBox9.Controls.Add(label22);
            groupBox9.Controls.Add(buttonTouchInit);
            groupBox9.Controls.Add(buttonTouchStatus);
            groupBox9.Controls.Add(buttonTouchReadAdv);
            groupBox9.Location = new Point(304, 6);
            groupBox9.Name = "groupBox9";
            groupBox9.Size = new Size(352, 194);
            groupBox9.TabIndex = 2;
            groupBox9.TabStop = false;
            groupBox9.Text = "Advanced";
            // 
            // buttonTouchIdle
            // 
            buttonTouchIdle.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchIdle.Location = new Point(218, 69);
            buttonTouchIdle.Name = "buttonTouchIdle";
            buttonTouchIdle.Size = new Size(128, 46);
            buttonTouchIdle.TabIndex = 38;
            buttonTouchIdle.Text = "Idle Mode";
            buttonTouchIdle.UseVisualStyleBackColor = true;
            buttonTouchIdle.Click += buttonTouchIdle_Click;
            // 
            // buttonTouchDebug
            // 
            buttonTouchDebug.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchDebug.Location = new Point(218, 17);
            buttonTouchDebug.Name = "buttonTouchDebug";
            buttonTouchDebug.Size = new Size(128, 46);
            buttonTouchDebug.TabIndex = 37;
            buttonTouchDebug.Text = "Test Mode";
            buttonTouchDebug.UseVisualStyleBackColor = true;
            buttonTouchDebug.Click += buttonTouchDebug_Click;
            // 
            // textBoxTouchVendorId
            // 
            textBoxTouchVendorId.Location = new Point(112, 105);
            textBoxTouchVendorId.Name = "textBoxTouchVendorId";
            textBoxTouchVendorId.ReadOnly = true;
            textBoxTouchVendorId.Size = new Size(100, 23);
            textBoxTouchVendorId.TabIndex = 36;
            textBoxTouchVendorId.Text = "0";
            textBoxTouchVendorId.TextAlign = HorizontalAlignment.Center;
            // 
            // label25
            // 
            label25.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label25.Location = new Point(6, 104);
            label25.Name = "label25";
            label25.Size = new Size(100, 21);
            label25.TabIndex = 35;
            label25.Text = "Vendor Id";
            label25.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchFirmwareId
            // 
            textBoxTouchFirmwareId.Location = new Point(112, 76);
            textBoxTouchFirmwareId.Name = "textBoxTouchFirmwareId";
            textBoxTouchFirmwareId.ReadOnly = true;
            textBoxTouchFirmwareId.Size = new Size(100, 23);
            textBoxTouchFirmwareId.TabIndex = 34;
            textBoxTouchFirmwareId.Text = "0";
            textBoxTouchFirmwareId.TextAlign = HorizontalAlignment.Center;
            // 
            // label24
            // 
            label24.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label24.Location = new Point(6, 75);
            label24.Name = "label24";
            label24.Size = new Size(100, 21);
            label24.TabIndex = 33;
            label24.Text = "Firmware ID";
            label24.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchVersionLow
            // 
            textBoxTouchVersionLow.Location = new Point(112, 47);
            textBoxTouchVersionLow.Name = "textBoxTouchVersionLow";
            textBoxTouchVersionLow.ReadOnly = true;
            textBoxTouchVersionLow.Size = new Size(100, 23);
            textBoxTouchVersionLow.TabIndex = 32;
            textBoxTouchVersionLow.Text = "0";
            textBoxTouchVersionLow.TextAlign = HorizontalAlignment.Center;
            // 
            // label23
            // 
            label23.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label23.Location = new Point(6, 46);
            label23.Name = "label23";
            label23.Size = new Size(100, 21);
            label23.TabIndex = 31;
            label23.Text = "Version Low";
            label23.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchVersionHigh
            // 
            textBoxTouchVersionHigh.Location = new Point(112, 18);
            textBoxTouchVersionHigh.Name = "textBoxTouchVersionHigh";
            textBoxTouchVersionHigh.ReadOnly = true;
            textBoxTouchVersionHigh.Size = new Size(100, 23);
            textBoxTouchVersionHigh.TabIndex = 30;
            textBoxTouchVersionHigh.Text = "0";
            textBoxTouchVersionHigh.TextAlign = HorizontalAlignment.Center;
            // 
            // label22
            // 
            label22.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label22.Location = new Point(6, 17);
            label22.Name = "label22";
            label22.Size = new Size(100, 21);
            label22.TabIndex = 29;
            label22.Text = "Version High";
            label22.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // buttonTouchInit
            // 
            buttonTouchInit.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchInit.Location = new Point(3, 136);
            buttonTouchInit.Name = "buttonTouchInit";
            buttonTouchInit.Size = new Size(63, 46);
            buttonTouchInit.TabIndex = 28;
            buttonTouchInit.Text = "INIT";
            buttonTouchInit.UseVisualStyleBackColor = true;
            // 
            // buttonTouchStatus
            // 
            buttonTouchStatus.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchStatus.Location = new Point(72, 136);
            buttonTouchStatus.Name = "buttonTouchStatus";
            buttonTouchStatus.Size = new Size(81, 46);
            buttonTouchStatus.TabIndex = 27;
            buttonTouchStatus.Text = "Status";
            buttonTouchStatus.UseVisualStyleBackColor = true;
            // 
            // buttonTouchReadAdv
            // 
            buttonTouchReadAdv.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchReadAdv.Location = new Point(159, 136);
            buttonTouchReadAdv.Name = "buttonTouchReadAdv";
            buttonTouchReadAdv.Size = new Size(63, 46);
            buttonTouchReadAdv.TabIndex = 26;
            buttonTouchReadAdv.Text = "READ";
            buttonTouchReadAdv.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            groupBox8.Controls.Add(label27);
            groupBox8.Controls.Add(label26);
            groupBox8.Controls.Add(buttonTouchRead);
            groupBox8.Controls.Add(buttonTouchClear);
            groupBox8.Controls.Add(textBoxTouchYMax);
            groupBox8.Controls.Add(textBoxTouchYMin);
            groupBox8.Controls.Add(label20);
            groupBox8.Controls.Add(textBoxTouchXMax);
            groupBox8.Controls.Add(textBoxTouchXMin);
            groupBox8.Controls.Add(label21);
            groupBox8.Controls.Add(textBoxTouchArea);
            groupBox8.Controls.Add(label18);
            groupBox8.Controls.Add(textBoxTouchWeight);
            groupBox8.Controls.Add(label19);
            groupBox8.Controls.Add(textBoxTouchYRaw);
            groupBox8.Controls.Add(textBoxTouchYPosition);
            groupBox8.Controls.Add(label17);
            groupBox8.Controls.Add(textBoxTouchXRaw);
            groupBox8.Controls.Add(textBoxTouchXPosition);
            groupBox8.Controls.Add(label16);
            groupBox8.Controls.Add(textBoxTouchEvent);
            groupBox8.Controls.Add(label15);
            groupBox8.Controls.Add(textBoxTouchPoints);
            groupBox8.Controls.Add(label14);
            groupBox8.Location = new Point(6, 6);
            groupBox8.Name = "groupBox8";
            groupBox8.Size = new Size(292, 373);
            groupBox8.TabIndex = 1;
            groupBox8.TabStop = false;
            groupBox8.Text = "Status";
            // 
            // label27
            // 
            label27.Font = new Font("Segoe UI", 9.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label27.Location = new Point(222, 141);
            label27.Name = "label27";
            label27.Size = new Size(50, 21);
            label27.TabIndex = 28;
            label27.Text = "counts";
            label27.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label26
            // 
            label26.Font = new Font("Segoe UI", 9.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label26.Location = new Point(222, 112);
            label26.Name = "label26";
            label26.Size = new Size(50, 21);
            label26.TabIndex = 27;
            label26.Text = "px";
            label26.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // buttonTouchRead
            // 
            buttonTouchRead.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchRead.Location = new Point(6, 331);
            buttonTouchRead.Name = "buttonTouchRead";
            buttonTouchRead.Size = new Size(235, 36);
            buttonTouchRead.TabIndex = 26;
            buttonTouchRead.Text = "Read";
            buttonTouchRead.UseVisualStyleBackColor = true;
            buttonTouchRead.Click += buttonTouchRead_Click;
            // 
            // buttonTouchClear
            // 
            buttonTouchClear.Font = new Font("Segoe UI", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTouchClear.Location = new Point(222, 273);
            buttonTouchClear.Name = "buttonTouchClear";
            buttonTouchClear.Size = new Size(63, 52);
            buttonTouchClear.TabIndex = 25;
            buttonTouchClear.Text = "CLEAR";
            buttonTouchClear.UseVisualStyleBackColor = true;
            // 
            // textBoxTouchYMax
            // 
            textBoxTouchYMax.Location = new Point(116, 302);
            textBoxTouchYMax.Name = "textBoxTouchYMax";
            textBoxTouchYMax.ReadOnly = true;
            textBoxTouchYMax.Size = new Size(100, 23);
            textBoxTouchYMax.TabIndex = 24;
            textBoxTouchYMax.Text = "0";
            textBoxTouchYMax.TextAlign = HorizontalAlignment.Center;
            // 
            // textBoxTouchYMin
            // 
            textBoxTouchYMin.Location = new Point(116, 273);
            textBoxTouchYMin.Name = "textBoxTouchYMin";
            textBoxTouchYMin.ReadOnly = true;
            textBoxTouchYMin.Size = new Size(100, 23);
            textBoxTouchYMin.TabIndex = 23;
            textBoxTouchYMin.Text = "0";
            textBoxTouchYMin.TextAlign = HorizontalAlignment.Center;
            // 
            // label20
            // 
            label20.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label20.Location = new Point(116, 249);
            label20.Name = "label20";
            label20.Size = new Size(100, 21);
            label20.TabIndex = 22;
            label20.Text = "Y Min/Max";
            label20.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchXMax
            // 
            textBoxTouchXMax.Location = new Point(6, 302);
            textBoxTouchXMax.Name = "textBoxTouchXMax";
            textBoxTouchXMax.ReadOnly = true;
            textBoxTouchXMax.Size = new Size(100, 23);
            textBoxTouchXMax.TabIndex = 21;
            textBoxTouchXMax.Text = "0";
            textBoxTouchXMax.TextAlign = HorizontalAlignment.Center;
            // 
            // textBoxTouchXMin
            // 
            textBoxTouchXMin.Location = new Point(6, 273);
            textBoxTouchXMin.Name = "textBoxTouchXMin";
            textBoxTouchXMin.ReadOnly = true;
            textBoxTouchXMin.Size = new Size(100, 23);
            textBoxTouchXMin.TabIndex = 20;
            textBoxTouchXMin.Text = "0";
            textBoxTouchXMin.TextAlign = HorizontalAlignment.Center;
            // 
            // label21
            // 
            label21.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label21.Location = new Point(6, 249);
            label21.Name = "label21";
            label21.Size = new Size(100, 21);
            label21.TabIndex = 19;
            label21.Text = "X Min/Max";
            label21.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchArea
            // 
            textBoxTouchArea.Location = new Point(116, 203);
            textBoxTouchArea.Name = "textBoxTouchArea";
            textBoxTouchArea.ReadOnly = true;
            textBoxTouchArea.Size = new Size(100, 23);
            textBoxTouchArea.TabIndex = 18;
            textBoxTouchArea.Text = "0";
            textBoxTouchArea.TextAlign = HorizontalAlignment.Center;
            // 
            // label18
            // 
            label18.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label18.Location = new Point(116, 179);
            label18.Name = "label18";
            label18.Size = new Size(100, 21);
            label18.TabIndex = 17;
            label18.Text = "Area";
            label18.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchWeight
            // 
            textBoxTouchWeight.Location = new Point(6, 203);
            textBoxTouchWeight.Name = "textBoxTouchWeight";
            textBoxTouchWeight.ReadOnly = true;
            textBoxTouchWeight.Size = new Size(100, 23);
            textBoxTouchWeight.TabIndex = 16;
            textBoxTouchWeight.Text = "0";
            textBoxTouchWeight.TextAlign = HorizontalAlignment.Center;
            // 
            // label19
            // 
            label19.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label19.Location = new Point(6, 179);
            label19.Name = "label19";
            label19.Size = new Size(100, 21);
            label19.TabIndex = 15;
            label19.Text = "Weight";
            label19.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchYRaw
            // 
            textBoxTouchYRaw.Location = new Point(116, 139);
            textBoxTouchYRaw.Name = "textBoxTouchYRaw";
            textBoxTouchYRaw.ReadOnly = true;
            textBoxTouchYRaw.Size = new Size(100, 23);
            textBoxTouchYRaw.TabIndex = 14;
            textBoxTouchYRaw.Text = "0";
            textBoxTouchYRaw.TextAlign = HorizontalAlignment.Center;
            // 
            // textBoxTouchYPosition
            // 
            textBoxTouchYPosition.Location = new Point(116, 110);
            textBoxTouchYPosition.Name = "textBoxTouchYPosition";
            textBoxTouchYPosition.ReadOnly = true;
            textBoxTouchYPosition.Size = new Size(100, 23);
            textBoxTouchYPosition.TabIndex = 13;
            textBoxTouchYPosition.Text = "0";
            textBoxTouchYPosition.TextAlign = HorizontalAlignment.Center;
            // 
            // label17
            // 
            label17.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label17.Location = new Point(116, 86);
            label17.Name = "label17";
            label17.Size = new Size(100, 21);
            label17.TabIndex = 12;
            label17.Text = "Y Position";
            label17.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchXRaw
            // 
            textBoxTouchXRaw.Location = new Point(6, 139);
            textBoxTouchXRaw.Name = "textBoxTouchXRaw";
            textBoxTouchXRaw.ReadOnly = true;
            textBoxTouchXRaw.Size = new Size(100, 23);
            textBoxTouchXRaw.TabIndex = 11;
            textBoxTouchXRaw.Text = "0";
            textBoxTouchXRaw.TextAlign = HorizontalAlignment.Center;
            // 
            // textBoxTouchXPosition
            // 
            textBoxTouchXPosition.Location = new Point(6, 110);
            textBoxTouchXPosition.Name = "textBoxTouchXPosition";
            textBoxTouchXPosition.ReadOnly = true;
            textBoxTouchXPosition.Size = new Size(100, 23);
            textBoxTouchXPosition.TabIndex = 10;
            textBoxTouchXPosition.Text = "0";
            textBoxTouchXPosition.TextAlign = HorizontalAlignment.Center;
            // 
            // label16
            // 
            label16.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label16.Location = new Point(6, 86);
            label16.Name = "label16";
            label16.Size = new Size(100, 21);
            label16.TabIndex = 9;
            label16.Text = "X Position";
            label16.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchEvent
            // 
            textBoxTouchEvent.Location = new Point(116, 44);
            textBoxTouchEvent.Name = "textBoxTouchEvent";
            textBoxTouchEvent.ReadOnly = true;
            textBoxTouchEvent.Size = new Size(100, 23);
            textBoxTouchEvent.TabIndex = 8;
            textBoxTouchEvent.Text = "0";
            textBoxTouchEvent.TextAlign = HorizontalAlignment.Center;
            // 
            // label15
            // 
            label15.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label15.Location = new Point(116, 20);
            label15.Name = "label15";
            label15.Size = new Size(100, 21);
            label15.TabIndex = 7;
            label15.Text = "Touch Event";
            label15.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxTouchPoints
            // 
            textBoxTouchPoints.Location = new Point(6, 44);
            textBoxTouchPoints.Name = "textBoxTouchPoints";
            textBoxTouchPoints.ReadOnly = true;
            textBoxTouchPoints.Size = new Size(100, 23);
            textBoxTouchPoints.TabIndex = 6;
            textBoxTouchPoints.Text = "0";
            textBoxTouchPoints.TextAlign = HorizontalAlignment.Center;
            // 
            // label14
            // 
            label14.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label14.Location = new Point(6, 20);
            label14.Name = "label14";
            label14.Size = new Size(100, 21);
            label14.TabIndex = 5;
            label14.Text = "Touch Points";
            label14.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // tabPageAccel
            // 
            tabPageAccel.Controls.Add(groupBox6);
            tabPageAccel.Location = new Point(4, 24);
            tabPageAccel.Name = "tabPageAccel";
            tabPageAccel.Padding = new Padding(3);
            tabPageAccel.Size = new Size(1023, 522);
            tabPageAccel.TabIndex = 4;
            tabPageAccel.Text = "Accel";
            tabPageAccel.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            groupBox6.Controls.Add(buttonAccelRead);
            groupBox6.Controls.Add(textBoxAccelZ);
            groupBox6.Controls.Add(label4);
            groupBox6.Controls.Add(textBoxAccelY);
            groupBox6.Controls.Add(label5);
            groupBox6.Controls.Add(textBoxAccelX);
            groupBox6.Controls.Add(label6);
            groupBox6.Location = new Point(6, 6);
            groupBox6.Name = "groupBox6";
            groupBox6.Size = new Size(388, 310);
            groupBox6.TabIndex = 0;
            groupBox6.TabStop = false;
            groupBox6.Text = "Data";
            // 
            // buttonAccelRead
            // 
            buttonAccelRead.Font = new Font("Segoe UI", 12F);
            buttonAccelRead.Location = new Point(50, 138);
            buttonAccelRead.Name = "buttonAccelRead";
            buttonAccelRead.Size = new Size(100, 34);
            buttonAccelRead.TabIndex = 17;
            buttonAccelRead.Text = "READ";
            buttonAccelRead.UseVisualStyleBackColor = true;
            buttonAccelRead.Click += buttonAccelRead_Click;
            // 
            // textBoxAccelZ
            // 
            textBoxAccelZ.Location = new Point(50, 98);
            textBoxAccelZ.Name = "textBoxAccelZ";
            textBoxAccelZ.ReadOnly = true;
            textBoxAccelZ.Size = new Size(100, 23);
            textBoxAccelZ.TabIndex = 16;
            textBoxAccelZ.TextAlign = HorizontalAlignment.Center;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label4.Location = new Point(15, 96);
            label4.Name = "label4";
            label4.Size = new Size(20, 21);
            label4.TabIndex = 15;
            label4.Text = "Z";
            // 
            // textBoxAccelY
            // 
            textBoxAccelY.Location = new Point(50, 69);
            textBoxAccelY.Name = "textBoxAccelY";
            textBoxAccelY.ReadOnly = true;
            textBoxAccelY.Size = new Size(100, 23);
            textBoxAccelY.TabIndex = 14;
            textBoxAccelY.TextAlign = HorizontalAlignment.Center;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label5.Location = new Point(15, 67);
            label5.Name = "label5";
            label5.Size = new Size(20, 21);
            label5.TabIndex = 13;
            label5.Text = "Y";
            // 
            // textBoxAccelX
            // 
            textBoxAccelX.Location = new Point(50, 40);
            textBoxAccelX.Name = "textBoxAccelX";
            textBoxAccelX.ReadOnly = true;
            textBoxAccelX.Size = new Size(100, 23);
            textBoxAccelX.TabIndex = 12;
            textBoxAccelX.TextAlign = HorizontalAlignment.Center;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label6.Location = new Point(15, 38);
            label6.Name = "label6";
            label6.Size = new Size(20, 21);
            label6.TabIndex = 11;
            label6.Text = "X";
            // 
            // tabPageRtc
            // 
            tabPageRtc.Controls.Add(groupBox7);
            tabPageRtc.Location = new Point(4, 24);
            tabPageRtc.Name = "tabPageRtc";
            tabPageRtc.Padding = new Padding(3);
            tabPageRtc.Size = new Size(1023, 522);
            tabPageRtc.TabIndex = 5;
            tabPageRtc.Text = "RTC";
            tabPageRtc.UseVisualStyleBackColor = true;
            // 
            // groupBox7
            // 
            groupBox7.Controls.Add(textBoxRtcSecRead);
            groupBox7.Controls.Add(textBoxRtcSecWrite);
            groupBox7.Controls.Add(label10);
            groupBox7.Controls.Add(textBoxRtcMinRead);
            groupBox7.Controls.Add(textBoxRtcMinWrite);
            groupBox7.Controls.Add(label9);
            groupBox7.Controls.Add(textBoxRtcHourRead);
            groupBox7.Controls.Add(buttonRtcRead);
            groupBox7.Controls.Add(buttonRtcWrite);
            groupBox7.Controls.Add(textBoxRtcHourWrite);
            groupBox7.Controls.Add(label8);
            groupBox7.Location = new Point(6, 6);
            groupBox7.Name = "groupBox7";
            groupBox7.Size = new Size(397, 416);
            groupBox7.TabIndex = 1;
            groupBox7.TabStop = false;
            groupBox7.Text = "Get / Set";
            // 
            // textBoxRtcSecRead
            // 
            textBoxRtcSecRead.Location = new Point(195, 107);
            textBoxRtcSecRead.Name = "textBoxRtcSecRead";
            textBoxRtcSecRead.ReadOnly = true;
            textBoxRtcSecRead.Size = new Size(100, 23);
            textBoxRtcSecRead.TabIndex = 10;
            textBoxRtcSecRead.TextAlign = HorizontalAlignment.Center;
            // 
            // textBoxRtcSecWrite
            // 
            textBoxRtcSecWrite.Location = new Point(89, 107);
            textBoxRtcSecWrite.Name = "textBoxRtcSecWrite";
            textBoxRtcSecWrite.Size = new Size(100, 23);
            textBoxRtcSecWrite.TabIndex = 9;
            textBoxRtcSecWrite.TextAlign = HorizontalAlignment.Center;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label10.Location = new Point(19, 105);
            label10.Name = "label10";
            label10.Size = new Size(36, 21);
            label10.TabIndex = 8;
            label10.Text = "Sec";
            // 
            // textBoxRtcMinRead
            // 
            textBoxRtcMinRead.Location = new Point(195, 78);
            textBoxRtcMinRead.Name = "textBoxRtcMinRead";
            textBoxRtcMinRead.ReadOnly = true;
            textBoxRtcMinRead.Size = new Size(100, 23);
            textBoxRtcMinRead.TabIndex = 7;
            textBoxRtcMinRead.TextAlign = HorizontalAlignment.Center;
            // 
            // textBoxRtcMinWrite
            // 
            textBoxRtcMinWrite.Location = new Point(89, 78);
            textBoxRtcMinWrite.Name = "textBoxRtcMinWrite";
            textBoxRtcMinWrite.Size = new Size(100, 23);
            textBoxRtcMinWrite.TabIndex = 6;
            textBoxRtcMinWrite.TextAlign = HorizontalAlignment.Center;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label9.Location = new Point(19, 76);
            label9.Name = "label9";
            label9.Size = new Size(40, 21);
            label9.TabIndex = 5;
            label9.Text = "Min";
            // 
            // textBoxRtcHourRead
            // 
            textBoxRtcHourRead.Location = new Point(195, 49);
            textBoxRtcHourRead.Name = "textBoxRtcHourRead";
            textBoxRtcHourRead.ReadOnly = true;
            textBoxRtcHourRead.Size = new Size(100, 23);
            textBoxRtcHourRead.TabIndex = 4;
            textBoxRtcHourRead.TextAlign = HorizontalAlignment.Center;
            // 
            // buttonRtcRead
            // 
            buttonRtcRead.Font = new Font("Segoe UI", 12F);
            buttonRtcRead.Location = new Point(195, 136);
            buttonRtcRead.Name = "buttonRtcRead";
            buttonRtcRead.Size = new Size(100, 34);
            buttonRtcRead.TabIndex = 3;
            buttonRtcRead.Text = "READ";
            buttonRtcRead.UseVisualStyleBackColor = true;
            buttonRtcRead.Click += buttonRtcRead_Click;
            // 
            // buttonRtcWrite
            // 
            buttonRtcWrite.Font = new Font("Segoe UI", 12F);
            buttonRtcWrite.Location = new Point(89, 136);
            buttonRtcWrite.Name = "buttonRtcWrite";
            buttonRtcWrite.Size = new Size(100, 34);
            buttonRtcWrite.TabIndex = 2;
            buttonRtcWrite.Text = "WRITE";
            buttonRtcWrite.UseVisualStyleBackColor = true;
            buttonRtcWrite.Click += buttonRtcWrite_Click;
            // 
            // textBoxRtcHourWrite
            // 
            textBoxRtcHourWrite.Location = new Point(89, 49);
            textBoxRtcHourWrite.Name = "textBoxRtcHourWrite";
            textBoxRtcHourWrite.Size = new Size(100, 23);
            textBoxRtcHourWrite.TabIndex = 1;
            textBoxRtcHourWrite.TextAlign = HorizontalAlignment.Center;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label8.Location = new Point(19, 47);
            label8.Name = "label8";
            label8.Size = new Size(48, 21);
            label8.TabIndex = 0;
            label8.Text = "Hour";
            // 
            // tabPageAd7124
            // 
            tabPageAd7124.Controls.Add(groupBox11);
            tabPageAd7124.Controls.Add(groupBox10);
            tabPageAd7124.Location = new Point(4, 24);
            tabPageAd7124.Name = "tabPageAd7124";
            tabPageAd7124.Padding = new Padding(3);
            tabPageAd7124.Size = new Size(1023, 522);
            tabPageAd7124.TabIndex = 6;
            tabPageAd7124.Text = "AD7124";
            tabPageAd7124.UseVisualStyleBackColor = true;
            // 
            // groupBox11
            // 
            groupBox11.Controls.Add(buttonAd7124Reset);
            groupBox11.Controls.Add(buttonAd7124StatusRead);
            groupBox11.Controls.Add(textBoxAd7124Channel);
            groupBox11.Controls.Add(label37);
            groupBox11.Controls.Add(textBoxAd7124ErrorEn);
            groupBox11.Controls.Add(label38);
            groupBox11.Controls.Add(textBoxAd7124Filter);
            groupBox11.Controls.Add(label35);
            groupBox11.Controls.Add(textBoxAd7124Config);
            groupBox11.Controls.Add(label36);
            groupBox11.Controls.Add(textBoxAd7124Offset);
            groupBox11.Controls.Add(label34);
            groupBox11.Controls.Add(textBoxAd7124Error);
            groupBox11.Controls.Add(label31);
            groupBox11.Controls.Add(textBoxAd7124Id);
            groupBox11.Controls.Add(label32);
            groupBox11.Controls.Add(textBoxAd7124Io2);
            groupBox11.Controls.Add(label29);
            groupBox11.Controls.Add(textBoxAd7124Io1);
            groupBox11.Controls.Add(label30);
            groupBox11.Controls.Add(textBoxAd7124Control);
            groupBox11.Controls.Add(label28);
            groupBox11.Controls.Add(textBoxAd7124Status);
            groupBox11.Controls.Add(label13);
            groupBox11.Location = new Point(291, 6);
            groupBox11.Name = "groupBox11";
            groupBox11.Size = new Size(580, 416);
            groupBox11.TabIndex = 1;
            groupBox11.TabStop = false;
            groupBox11.Text = "Status";
            // 
            // buttonAd7124Reset
            // 
            buttonAd7124Reset.Font = new Font("Segoe UI", 12F);
            buttonAd7124Reset.Location = new Point(6, 329);
            buttonAd7124Reset.Name = "buttonAd7124Reset";
            buttonAd7124Reset.Size = new Size(162, 34);
            buttonAd7124Reset.TabIndex = 37;
            buttonAd7124Reset.Text = "RESET / INIT";
            buttonAd7124Reset.UseVisualStyleBackColor = true;
            buttonAd7124Reset.Click += buttonAd7124Reset_Click;
            // 
            // buttonAd7124StatusRead
            // 
            buttonAd7124StatusRead.Font = new Font("Segoe UI", 12F);
            buttonAd7124StatusRead.Location = new Point(7, 263);
            buttonAd7124StatusRead.Name = "buttonAd7124StatusRead";
            buttonAd7124StatusRead.Size = new Size(162, 60);
            buttonAd7124StatusRead.TabIndex = 36;
            buttonAd7124StatusRead.Text = "READ";
            buttonAd7124StatusRead.UseVisualStyleBackColor = true;
            buttonAd7124StatusRead.Click += buttonAd7124StatusRead_Click;
            // 
            // textBoxAd7124Channel
            // 
            textBoxAd7124Channel.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Channel.Location = new Point(409, 68);
            textBoxAd7124Channel.Name = "textBoxAd7124Channel";
            textBoxAd7124Channel.ReadOnly = true;
            textBoxAd7124Channel.Size = new Size(119, 29);
            textBoxAd7124Channel.TabIndex = 35;
            textBoxAd7124Channel.Text = "????";
            textBoxAd7124Channel.TextAlign = HorizontalAlignment.Center;
            // 
            // label37
            // 
            label37.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label37.Location = new Point(306, 71);
            label37.Name = "label37";
            label37.Size = new Size(97, 21);
            label37.TabIndex = 34;
            label37.Text = "Channel:";
            // 
            // textBoxAd7124ErrorEn
            // 
            textBoxAd7124ErrorEn.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124ErrorEn.Location = new Point(409, 33);
            textBoxAd7124ErrorEn.Name = "textBoxAd7124ErrorEn";
            textBoxAd7124ErrorEn.ReadOnly = true;
            textBoxAd7124ErrorEn.Size = new Size(119, 29);
            textBoxAd7124ErrorEn.TabIndex = 33;
            textBoxAd7124ErrorEn.Text = "????";
            textBoxAd7124ErrorEn.TextAlign = HorizontalAlignment.Center;
            // 
            // label38
            // 
            label38.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label38.Location = new Point(306, 36);
            label38.Name = "label38";
            label38.Size = new Size(97, 21);
            label38.TabIndex = 32;
            label38.Text = "Error En:";
            // 
            // textBoxAd7124Filter
            // 
            textBoxAd7124Filter.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Filter.Location = new Point(409, 138);
            textBoxAd7124Filter.Name = "textBoxAd7124Filter";
            textBoxAd7124Filter.ReadOnly = true;
            textBoxAd7124Filter.Size = new Size(119, 29);
            textBoxAd7124Filter.TabIndex = 31;
            textBoxAd7124Filter.Text = "????";
            textBoxAd7124Filter.TextAlign = HorizontalAlignment.Center;
            // 
            // label35
            // 
            label35.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label35.Location = new Point(306, 141);
            label35.Name = "label35";
            label35.Size = new Size(97, 21);
            label35.TabIndex = 30;
            label35.Text = "Filter:";
            // 
            // textBoxAd7124Config
            // 
            textBoxAd7124Config.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Config.Location = new Point(409, 103);
            textBoxAd7124Config.Name = "textBoxAd7124Config";
            textBoxAd7124Config.ReadOnly = true;
            textBoxAd7124Config.Size = new Size(119, 29);
            textBoxAd7124Config.TabIndex = 29;
            textBoxAd7124Config.Text = "????";
            textBoxAd7124Config.TextAlign = HorizontalAlignment.Center;
            // 
            // label36
            // 
            label36.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label36.Location = new Point(306, 106);
            label36.Name = "label36";
            label36.Size = new Size(97, 21);
            label36.TabIndex = 28;
            label36.Text = "Config:";
            // 
            // textBoxAd7124Offset
            // 
            textBoxAd7124Offset.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Offset.Location = new Point(409, 173);
            textBoxAd7124Offset.Name = "textBoxAd7124Offset";
            textBoxAd7124Offset.ReadOnly = true;
            textBoxAd7124Offset.Size = new Size(119, 29);
            textBoxAd7124Offset.TabIndex = 25;
            textBoxAd7124Offset.Text = "????";
            textBoxAd7124Offset.TextAlign = HorizontalAlignment.Center;
            // 
            // label34
            // 
            label34.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label34.Location = new Point(306, 176);
            label34.Name = "label34";
            label34.Size = new Size(97, 21);
            label34.TabIndex = 24;
            label34.Text = "Offset:";
            // 
            // textBoxAd7124Error
            // 
            textBoxAd7124Error.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Error.Location = new Point(151, 205);
            textBoxAd7124Error.Name = "textBoxAd7124Error";
            textBoxAd7124Error.ReadOnly = true;
            textBoxAd7124Error.Size = new Size(119, 29);
            textBoxAd7124Error.TabIndex = 23;
            textBoxAd7124Error.Text = "????";
            textBoxAd7124Error.TextAlign = HorizontalAlignment.Center;
            // 
            // label31
            // 
            label31.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label31.Location = new Point(7, 208);
            label31.Name = "label31";
            label31.Size = new Size(97, 21);
            label31.TabIndex = 22;
            label31.Text = "Error:";
            // 
            // textBoxAd7124Id
            // 
            textBoxAd7124Id.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Id.Location = new Point(151, 170);
            textBoxAd7124Id.Name = "textBoxAd7124Id";
            textBoxAd7124Id.ReadOnly = true;
            textBoxAd7124Id.Size = new Size(119, 29);
            textBoxAd7124Id.TabIndex = 21;
            textBoxAd7124Id.Text = "????";
            textBoxAd7124Id.TextAlign = HorizontalAlignment.Center;
            // 
            // label32
            // 
            label32.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label32.Location = new Point(7, 173);
            label32.Name = "label32";
            label32.Size = new Size(97, 21);
            label32.TabIndex = 20;
            label32.Text = "ID:";
            // 
            // textBoxAd7124Io2
            // 
            textBoxAd7124Io2.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Io2.Location = new Point(151, 135);
            textBoxAd7124Io2.Name = "textBoxAd7124Io2";
            textBoxAd7124Io2.ReadOnly = true;
            textBoxAd7124Io2.Size = new Size(119, 29);
            textBoxAd7124Io2.TabIndex = 19;
            textBoxAd7124Io2.Text = "????";
            textBoxAd7124Io2.TextAlign = HorizontalAlignment.Center;
            // 
            // label29
            // 
            label29.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label29.Location = new Point(7, 138);
            label29.Name = "label29";
            label29.Size = new Size(119, 21);
            label29.TabIndex = 18;
            label29.Text = "IO Control 2:";
            // 
            // textBoxAd7124Io1
            // 
            textBoxAd7124Io1.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Io1.Location = new Point(151, 100);
            textBoxAd7124Io1.Name = "textBoxAd7124Io1";
            textBoxAd7124Io1.ReadOnly = true;
            textBoxAd7124Io1.Size = new Size(119, 29);
            textBoxAd7124Io1.TabIndex = 17;
            textBoxAd7124Io1.Text = "????";
            textBoxAd7124Io1.TextAlign = HorizontalAlignment.Center;
            // 
            // label30
            // 
            label30.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label30.Location = new Point(7, 103);
            label30.Name = "label30";
            label30.Size = new Size(130, 21);
            label30.TabIndex = 16;
            label30.Text = "IO Control 1:";
            // 
            // textBoxAd7124Control
            // 
            textBoxAd7124Control.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Control.Location = new Point(151, 65);
            textBoxAd7124Control.Name = "textBoxAd7124Control";
            textBoxAd7124Control.ReadOnly = true;
            textBoxAd7124Control.Size = new Size(119, 29);
            textBoxAd7124Control.TabIndex = 15;
            textBoxAd7124Control.Text = "????";
            textBoxAd7124Control.TextAlign = HorizontalAlignment.Center;
            // 
            // label28
            // 
            label28.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label28.Location = new Point(7, 68);
            label28.Name = "label28";
            label28.Size = new Size(138, 21);
            label28.TabIndex = 14;
            label28.Text = "ADC Control:";
            // 
            // textBoxAd7124Status
            // 
            textBoxAd7124Status.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Status.Location = new Point(151, 30);
            textBoxAd7124Status.Name = "textBoxAd7124Status";
            textBoxAd7124Status.ReadOnly = true;
            textBoxAd7124Status.Size = new Size(119, 29);
            textBoxAd7124Status.TabIndex = 13;
            textBoxAd7124Status.Text = "????";
            textBoxAd7124Status.TextAlign = HorizontalAlignment.Center;
            // 
            // label13
            // 
            label13.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label13.Location = new Point(7, 33);
            label13.Name = "label13";
            label13.Size = new Size(97, 21);
            label13.TabIndex = 12;
            label13.Text = "Status:";
            // 
            // groupBox10
            // 
            groupBox10.Controls.Add(textBoxAd7124mmHg);
            groupBox10.Controls.Add(label40);
            groupBox10.Controls.Add(buttonAD7124Read);
            groupBox10.Controls.Add(textBoxAd7124Volts);
            groupBox10.Controls.Add(label12);
            groupBox10.Controls.Add(textBoxAd7124CountsDec);
            groupBox10.Controls.Add(label11);
            groupBox10.Controls.Add(textBoxAd7124CountsHex);
            groupBox10.Controls.Add(label7);
            groupBox10.Location = new Point(6, 6);
            groupBox10.Name = "groupBox10";
            groupBox10.Size = new Size(279, 416);
            groupBox10.TabIndex = 0;
            groupBox10.TabStop = false;
            groupBox10.Text = "AD7124";
            // 
            // textBoxAd7124mmHg
            // 
            textBoxAd7124mmHg.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124mmHg.Location = new Point(6, 127);
            textBoxAd7124mmHg.Name = "textBoxAd7124mmHg";
            textBoxAd7124mmHg.ReadOnly = true;
            textBoxAd7124mmHg.Size = new Size(162, 29);
            textBoxAd7124mmHg.TabIndex = 13;
            textBoxAd7124mmHg.TextAlign = HorizontalAlignment.Center;
            // 
            // label40
            // 
            label40.AutoSize = true;
            label40.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label40.Location = new Point(174, 135);
            label40.Name = "label40";
            label40.Size = new Size(58, 21);
            label40.TabIndex = 12;
            label40.Text = "mmHg";
            // 
            // buttonAD7124Read
            // 
            buttonAD7124Read.Font = new Font("Segoe UI", 12F);
            buttonAD7124Read.Location = new Point(6, 195);
            buttonAD7124Read.Name = "buttonAD7124Read";
            buttonAD7124Read.Size = new Size(162, 34);
            buttonAD7124Read.TabIndex = 11;
            buttonAD7124Read.Text = "READ";
            buttonAD7124Read.UseVisualStyleBackColor = true;
            buttonAD7124Read.Click += buttonAD7124Read_Click;
            // 
            // textBoxAd7124Volts
            // 
            textBoxAd7124Volts.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124Volts.Location = new Point(6, 92);
            textBoxAd7124Volts.Name = "textBoxAd7124Volts";
            textBoxAd7124Volts.ReadOnly = true;
            textBoxAd7124Volts.Size = new Size(162, 29);
            textBoxAd7124Volts.TabIndex = 10;
            textBoxAd7124Volts.TextAlign = HorizontalAlignment.Center;
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label12.Location = new Point(174, 100);
            label12.Name = "label12";
            label12.Size = new Size(34, 21);
            label12.TabIndex = 9;
            label12.Text = "mV";
            // 
            // textBoxAd7124CountsDec
            // 
            textBoxAd7124CountsDec.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124CountsDec.Location = new Point(6, 57);
            textBoxAd7124CountsDec.Name = "textBoxAd7124CountsDec";
            textBoxAd7124CountsDec.ReadOnly = true;
            textBoxAd7124CountsDec.Size = new Size(162, 29);
            textBoxAd7124CountsDec.TabIndex = 8;
            textBoxAd7124CountsDec.TextAlign = HorizontalAlignment.Center;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label11.Location = new Point(174, 65);
            label11.Name = "label11";
            label11.Size = new Size(97, 21);
            label11.TabIndex = 7;
            label11.Text = "Counts (dec)";
            // 
            // textBoxAd7124CountsHex
            // 
            textBoxAd7124CountsHex.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxAd7124CountsHex.Location = new Point(6, 22);
            textBoxAd7124CountsHex.Name = "textBoxAd7124CountsHex";
            textBoxAd7124CountsHex.ReadOnly = true;
            textBoxAd7124CountsHex.Size = new Size(162, 29);
            textBoxAd7124CountsHex.TabIndex = 6;
            textBoxAd7124CountsHex.TextAlign = HorizontalAlignment.Center;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label7.Location = new Point(174, 30);
            label7.Name = "label7";
            label7.Size = new Size(97, 21);
            label7.TabIndex = 5;
            label7.Text = "Counts (hex)";
            // 
            // tabPageFlash
            // 
            tabPageFlash.Controls.Add(groupBox15);
            tabPageFlash.Controls.Add(groupBox13);
            tabPageFlash.Controls.Add(groupBox12);
            tabPageFlash.Location = new Point(4, 24);
            tabPageFlash.Name = "tabPageFlash";
            tabPageFlash.Padding = new Padding(3);
            tabPageFlash.Size = new Size(1023, 522);
            tabPageFlash.TabIndex = 7;
            tabPageFlash.Text = "Flash";
            tabPageFlash.UseVisualStyleBackColor = true;
            // 
            // groupBox15
            // 
            groupBox15.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            groupBox15.Controls.Add(textBoxFlashReadData);
            groupBox15.Controls.Add(buttonFlashRead);
            groupBox15.Controls.Add(label46);
            groupBox15.Controls.Add(textBoxFlashReadAddress);
            groupBox15.Controls.Add(label45);
            groupBox15.Controls.Add(comboBoxFlashReadSlot);
            groupBox15.Location = new Point(6, 322);
            groupBox15.Name = "groupBox15";
            groupBox15.Size = new Size(1011, 194);
            groupBox15.TabIndex = 2;
            groupBox15.TabStop = false;
            groupBox15.Text = "Flash Read";
            // 
            // textBoxFlashReadData
            // 
            textBoxFlashReadData.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            textBoxFlashReadData.Font = new Font("Consolas", 9.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxFlashReadData.Location = new Point(6, 22);
            textBoxFlashReadData.Multiline = true;
            textBoxFlashReadData.Name = "textBoxFlashReadData";
            textBoxFlashReadData.ReadOnly = true;
            textBoxFlashReadData.ScrollBars = ScrollBars.Vertical;
            textBoxFlashReadData.Size = new Size(848, 166);
            textBoxFlashReadData.TabIndex = 22;
            // 
            // buttonFlashRead
            // 
            buttonFlashRead.Font = new Font("Segoe UI", 12F);
            buttonFlashRead.Location = new Point(874, 149);
            buttonFlashRead.Name = "buttonFlashRead";
            buttonFlashRead.Size = new Size(131, 39);
            buttonFlashRead.TabIndex = 21;
            buttonFlashRead.Text = "Read";
            buttonFlashRead.UseVisualStyleBackColor = true;
            buttonFlashRead.Click += buttonFlashRead_Click;
            // 
            // label46
            // 
            label46.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label46.Location = new Point(874, 80);
            label46.Name = "label46";
            label46.Size = new Size(131, 26);
            label46.TabIndex = 12;
            label46.Text = "Address";
            label46.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // textBoxFlashReadAddress
            // 
            textBoxFlashReadAddress.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxFlashReadAddress.Location = new Point(874, 109);
            textBoxFlashReadAddress.Name = "textBoxFlashReadAddress";
            textBoxFlashReadAddress.Size = new Size(131, 29);
            textBoxFlashReadAddress.TabIndex = 11;
            textBoxFlashReadAddress.Text = "0";
            // 
            // label45
            // 
            label45.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label45.Location = new Point(874, 13);
            label45.Name = "label45";
            label45.Size = new Size(131, 26);
            label45.TabIndex = 10;
            label45.Text = "Slot";
            label45.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // comboBoxFlashReadSlot
            // 
            comboBoxFlashReadSlot.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comboBoxFlashReadSlot.FormattingEnabled = true;
            comboBoxFlashReadSlot.Items.AddRange(new object[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" });
            comboBoxFlashReadSlot.Location = new Point(874, 42);
            comboBoxFlashReadSlot.Name = "comboBoxFlashReadSlot";
            comboBoxFlashReadSlot.Size = new Size(131, 29);
            comboBoxFlashReadSlot.TabIndex = 9;
            comboBoxFlashReadSlot.SelectedIndexChanged += comboBoxFlashReadSlot_SelectedIndexChanged;
            // 
            // groupBox13
            // 
            groupBox13.Controls.Add(buttonFlashTest);
            groupBox13.Controls.Add(buttonFlashClearProg);
            groupBox13.Controls.Add(buttonFlashReset);
            groupBox13.Location = new Point(690, 6);
            groupBox13.Name = "groupBox13";
            groupBox13.Size = new Size(146, 310);
            groupBox13.TabIndex = 1;
            groupBox13.TabStop = false;
            groupBox13.Text = "Operations";
            // 
            // buttonFlashTest
            // 
            buttonFlashTest.Font = new Font("Segoe UI", 12F);
            buttonFlashTest.Location = new Point(6, 109);
            buttonFlashTest.Name = "buttonFlashTest";
            buttonFlashTest.Size = new Size(131, 39);
            buttonFlashTest.TabIndex = 22;
            buttonFlashTest.Text = "Test";
            buttonFlashTest.UseVisualStyleBackColor = true;
            buttonFlashTest.Click += buttonFlashTest_Click;
            // 
            // buttonFlashClearProg
            // 
            buttonFlashClearProg.Font = new Font("Segoe UI", 12F);
            buttonFlashClearProg.Location = new Point(6, 64);
            buttonFlashClearProg.Name = "buttonFlashClearProg";
            buttonFlashClearProg.Size = new Size(131, 39);
            buttonFlashClearProg.TabIndex = 21;
            buttonFlashClearProg.Text = "Clear Prog";
            buttonFlashClearProg.UseVisualStyleBackColor = true;
            buttonFlashClearProg.Click += buttonFlashClearProg_Click;
            // 
            // buttonFlashReset
            // 
            buttonFlashReset.Font = new Font("Segoe UI", 12F);
            buttonFlashReset.Location = new Point(6, 19);
            buttonFlashReset.Name = "buttonFlashReset";
            buttonFlashReset.Size = new Size(131, 39);
            buttonFlashReset.TabIndex = 20;
            buttonFlashReset.Text = "RESET";
            buttonFlashReset.UseVisualStyleBackColor = true;
            buttonFlashReset.Click += buttonFlashReset_Click;
            // 
            // groupBox12
            // 
            groupBox12.Controls.Add(dataGridViewFlashIds);
            groupBox12.Controls.Add(buttonFlashGetStatus);
            groupBox12.Controls.Add(dataGridViewFlashRegisters);
            groupBox12.Controls.Add(textBoxFlashStatus2);
            groupBox12.Controls.Add(label39);
            groupBox12.Controls.Add(textBoxFlashStatus1);
            groupBox12.Controls.Add(label33);
            groupBox12.Location = new Point(6, 6);
            groupBox12.Name = "groupBox12";
            groupBox12.Size = new Size(678, 310);
            groupBox12.TabIndex = 0;
            groupBox12.TabStop = false;
            groupBox12.Text = "Flash Status";
            // 
            // dataGridViewFlashIds
            // 
            dataGridViewFlashIds.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewFlashIds.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewFlashIds.Columns.AddRange(new DataGridViewColumn[] { dataGridViewTextBoxColumn1, dataGridViewTextBoxColumn2 });
            dataGridViewFlashIds.Location = new Point(338, 99);
            dataGridViewFlashIds.Name = "dataGridViewFlashIds";
            dataGridViewFlashIds.ReadOnly = true;
            dataGridViewFlashIds.RowHeadersVisible = false;
            dataGridViewFlashIds.Size = new Size(326, 195);
            dataGridViewFlashIds.TabIndex = 20;
            // 
            // dataGridViewTextBoxColumn1
            // 
            dataGridViewTextBoxColumn1.HeaderText = "Register";
            dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
            dataGridViewTextBoxColumn1.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn2
            // 
            dataGridViewTextBoxColumn2.HeaderText = "Value";
            dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
            dataGridViewTextBoxColumn2.ReadOnly = true;
            // 
            // buttonFlashGetStatus
            // 
            buttonFlashGetStatus.Font = new Font("Segoe UI", 12F);
            buttonFlashGetStatus.Location = new Point(232, 19);
            buttonFlashGetStatus.Name = "buttonFlashGetStatus";
            buttonFlashGetStatus.Size = new Size(100, 69);
            buttonFlashGetStatus.TabIndex = 19;
            buttonFlashGetStatus.Text = "READ";
            buttonFlashGetStatus.UseVisualStyleBackColor = true;
            buttonFlashGetStatus.Click += buttonFlashGetStatus_Click;
            // 
            // dataGridViewFlashRegisters
            // 
            dataGridViewFlashRegisters.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewFlashRegisters.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewFlashRegisters.Columns.AddRange(new DataGridViewColumn[] { Register, RegValues });
            dataGridViewFlashRegisters.Location = new Point(6, 99);
            dataGridViewFlashRegisters.Name = "dataGridViewFlashRegisters";
            dataGridViewFlashRegisters.ReadOnly = true;
            dataGridViewFlashRegisters.RowHeadersVisible = false;
            dataGridViewFlashRegisters.Size = new Size(326, 195);
            dataGridViewFlashRegisters.TabIndex = 18;
            // 
            // Register
            // 
            Register.HeaderText = "Register";
            Register.Name = "Register";
            Register.ReadOnly = true;
            // 
            // RegValues
            // 
            RegValues.HeaderText = "Value";
            RegValues.Name = "RegValues";
            RegValues.ReadOnly = true;
            // 
            // textBoxFlashStatus2
            // 
            textBoxFlashStatus2.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxFlashStatus2.Location = new Point(92, 64);
            textBoxFlashStatus2.Name = "textBoxFlashStatus2";
            textBoxFlashStatus2.ReadOnly = true;
            textBoxFlashStatus2.Size = new Size(119, 29);
            textBoxFlashStatus2.TabIndex = 17;
            textBoxFlashStatus2.Text = "????";
            textBoxFlashStatus2.TextAlign = HorizontalAlignment.Center;
            // 
            // label39
            // 
            label39.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label39.Location = new Point(6, 67);
            label39.Name = "label39";
            label39.Size = new Size(80, 21);
            label39.TabIndex = 16;
            label39.Text = "Status 2:";
            // 
            // textBoxFlashStatus1
            // 
            textBoxFlashStatus1.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxFlashStatus1.Location = new Point(92, 29);
            textBoxFlashStatus1.Name = "textBoxFlashStatus1";
            textBoxFlashStatus1.ReadOnly = true;
            textBoxFlashStatus1.Size = new Size(119, 29);
            textBoxFlashStatus1.TabIndex = 15;
            textBoxFlashStatus1.Text = "????";
            textBoxFlashStatus1.TextAlign = HorizontalAlignment.Center;
            // 
            // label33
            // 
            label33.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label33.Location = new Point(6, 32);
            label33.Name = "label33";
            label33.Size = new Size(80, 21);
            label33.TabIndex = 14;
            label33.Text = "Status 1:";
            // 
            // tabPageAdc
            // 
            tabPageAdc.Controls.Add(groupBox14);
            tabPageAdc.Location = new Point(4, 24);
            tabPageAdc.Name = "tabPageAdc";
            tabPageAdc.Padding = new Padding(3);
            tabPageAdc.Size = new Size(1023, 522);
            tabPageAdc.TabIndex = 8;
            tabPageAdc.Text = "Adc";
            tabPageAdc.UseVisualStyleBackColor = true;
            // 
            // groupBox14
            // 
            groupBox14.Controls.Add(buttonBatRead);
            groupBox14.Controls.Add(textBoxBatVolts);
            groupBox14.Controls.Add(label42);
            groupBox14.Controls.Add(textBoxBatCountDec);
            groupBox14.Controls.Add(label43);
            groupBox14.Controls.Add(textBoxBatCountsHex);
            groupBox14.Controls.Add(label44);
            groupBox14.Location = new Point(6, 6);
            groupBox14.Name = "groupBox14";
            groupBox14.Size = new Size(279, 416);
            groupBox14.TabIndex = 1;
            groupBox14.TabStop = false;
            groupBox14.Text = "Battery";
            // 
            // buttonBatRead
            // 
            buttonBatRead.Font = new Font("Segoe UI", 12F);
            buttonBatRead.Location = new Point(6, 127);
            buttonBatRead.Name = "buttonBatRead";
            buttonBatRead.Size = new Size(162, 34);
            buttonBatRead.TabIndex = 11;
            buttonBatRead.Text = "READ";
            buttonBatRead.UseVisualStyleBackColor = true;
            buttonBatRead.Click += buttonBatRead_Click;
            // 
            // textBoxBatVolts
            // 
            textBoxBatVolts.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxBatVolts.Location = new Point(6, 92);
            textBoxBatVolts.Name = "textBoxBatVolts";
            textBoxBatVolts.ReadOnly = true;
            textBoxBatVolts.Size = new Size(162, 29);
            textBoxBatVolts.TabIndex = 10;
            textBoxBatVolts.TextAlign = HorizontalAlignment.Center;
            // 
            // label42
            // 
            label42.AutoSize = true;
            label42.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label42.Location = new Point(174, 100);
            label42.Name = "label42";
            label42.Size = new Size(34, 21);
            label42.TabIndex = 9;
            label42.Text = "mV";
            // 
            // textBoxBatCountDec
            // 
            textBoxBatCountDec.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxBatCountDec.Location = new Point(6, 57);
            textBoxBatCountDec.Name = "textBoxBatCountDec";
            textBoxBatCountDec.ReadOnly = true;
            textBoxBatCountDec.Size = new Size(162, 29);
            textBoxBatCountDec.TabIndex = 8;
            textBoxBatCountDec.TextAlign = HorizontalAlignment.Center;
            // 
            // label43
            // 
            label43.AutoSize = true;
            label43.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label43.Location = new Point(174, 65);
            label43.Name = "label43";
            label43.Size = new Size(97, 21);
            label43.TabIndex = 7;
            label43.Text = "Counts (dec)";
            // 
            // textBoxBatCountsHex
            // 
            textBoxBatCountsHex.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxBatCountsHex.Location = new Point(6, 22);
            textBoxBatCountsHex.Name = "textBoxBatCountsHex";
            textBoxBatCountsHex.ReadOnly = true;
            textBoxBatCountsHex.Size = new Size(162, 29);
            textBoxBatCountsHex.TabIndex = 6;
            textBoxBatCountsHex.TextAlign = HorizontalAlignment.Center;
            // 
            // label44
            // 
            label44.AutoSize = true;
            label44.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label44.Location = new Point(174, 30);
            label44.Name = "label44";
            label44.Size = new Size(97, 21);
            label44.TabIndex = 5;
            label44.Text = "Counts (hex)";
            // 
            // tabPageBarometric
            // 
            tabPageBarometric.Controls.Add(dataGridViewBarometric);
            tabPageBarometric.Location = new Point(4, 24);
            tabPageBarometric.Name = "tabPageBarometric";
            tabPageBarometric.Padding = new Padding(3);
            tabPageBarometric.Size = new Size(1023, 522);
            tabPageBarometric.TabIndex = 9;
            tabPageBarometric.Text = "Barometric";
            tabPageBarometric.UseVisualStyleBackColor = true;
            // 
            // dataGridViewBarometric
            // 
            dataGridViewBarometric.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewBarometric.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            dataGridViewBarometric.Columns.AddRange(new DataGridViewColumn[] { dataGridViewTextBoxColumn3, dataGridViewTextBoxColumn4 });
            dataGridViewBarometric.Location = new Point(6, 6);
            dataGridViewBarometric.Name = "dataGridViewBarometric";
            dataGridViewBarometric.ReadOnly = true;
            dataGridViewBarometric.RowHeadersVisible = false;
            dataGridViewBarometric.Size = new Size(422, 307);
            dataGridViewBarometric.TabIndex = 1;
            // 
            // dataGridViewTextBoxColumn3
            // 
            dataGridViewTextBoxColumn3.HeaderText = "Parameter";
            dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
            dataGridViewTextBoxColumn3.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn4
            // 
            dataGridViewTextBoxColumn4.HeaderText = "Value";
            dataGridViewTextBoxColumn4.Name = "dataGridViewTextBoxColumn4";
            dataGridViewTextBoxColumn4.ReadOnly = true;
            // 
            // tabPageDataLog
            // 
            tabPageDataLog.Controls.Add(groupBox18);
            tabPageDataLog.Controls.Add(groupBox17);
            tabPageDataLog.Location = new Point(4, 24);
            tabPageDataLog.Name = "tabPageDataLog";
            tabPageDataLog.Padding = new Padding(3);
            tabPageDataLog.Size = new Size(1023, 522);
            tabPageDataLog.TabIndex = 10;
            tabPageDataLog.Text = "Data Log";
            tabPageDataLog.UseVisualStyleBackColor = true;
            // 
            // groupBox18
            // 
            groupBox18.Controls.Add(progressBarDataDownload);
            groupBox18.Controls.Add(labelDownloadStatus);
            groupBox18.Controls.Add(buttonDownload);
            groupBox18.Controls.Add(textBoxStartSample);
            groupBox18.Controls.Add(label50);
            groupBox18.Location = new Point(280, 6);
            groupBox18.Name = "groupBox18";
            groupBox18.Size = new Size(737, 291);
            groupBox18.TabIndex = 1;
            groupBox18.TabStop = false;
            groupBox18.Text = "Export";
            // 
            // labelDownloadStatus
            // 
            labelDownloadStatus.AutoSize = true;
            labelDownloadStatus.Location = new Point(19, 197);
            labelDownloadStatus.Name = "labelDownloadStatus";
            labelDownloadStatus.Size = new Size(45, 15);
            labelDownloadStatus.TabIndex = 20;
            labelDownloadStatus.Text = "Status: ";
            // 
            // buttonDownload
            // 
            buttonDownload.Font = new Font("Segoe UI", 12F);
            buttonDownload.Location = new Point(19, 72);
            buttonDownload.Name = "buttonDownload";
            buttonDownload.Size = new Size(263, 63);
            buttonDownload.TabIndex = 19;
            buttonDownload.Text = "Download";
            buttonDownload.UseVisualStyleBackColor = true;
            buttonDownload.Click += buttonDownload_Click;
            // 
            // textBoxStartSample
            // 
            textBoxStartSample.Location = new Point(139, 37);
            textBoxStartSample.Name = "textBoxStartSample";
            textBoxStartSample.Size = new Size(143, 23);
            textBoxStartSample.TabIndex = 13;
            textBoxStartSample.Text = "0";
            textBoxStartSample.TextAlign = HorizontalAlignment.Center;
            // 
            // label50
            // 
            label50.AutoSize = true;
            label50.Font = new Font("Verdana", 12F);
            label50.Location = new Point(19, 42);
            label50.Name = "label50";
            label50.Size = new Size(114, 18);
            label50.TabIndex = 12;
            label50.Text = "Start Sample";
            // 
            // groupBox17
            // 
            groupBox17.Controls.Add(buttonDataLogReadEventLog);
            groupBox17.Controls.Add(textBoxDataLogSectorEnd);
            groupBox17.Controls.Add(label47);
            groupBox17.Controls.Add(textBoxDataLogSectorBegin);
            groupBox17.Controls.Add(label48);
            groupBox17.Controls.Add(textBoxDataLogSamples);
            groupBox17.Controls.Add(label49);
            groupBox17.Location = new Point(6, 6);
            groupBox17.Name = "groupBox17";
            groupBox17.Size = new Size(268, 291);
            groupBox17.TabIndex = 0;
            groupBox17.TabStop = false;
            groupBox17.Text = "Event Log";
            // 
            // buttonDataLogReadEventLog
            // 
            buttonDataLogReadEventLog.Font = new Font("Segoe UI", 12F);
            buttonDataLogReadEventLog.Location = new Point(117, 124);
            buttonDataLogReadEventLog.Name = "buttonDataLogReadEventLog";
            buttonDataLogReadEventLog.Size = new Size(143, 34);
            buttonDataLogReadEventLog.TabIndex = 18;
            buttonDataLogReadEventLog.Text = "READ";
            buttonDataLogReadEventLog.UseVisualStyleBackColor = true;
            buttonDataLogReadEventLog.Click += buttonDataLogReadEventLog_Click;
            // 
            // textBoxDataLogSectorEnd
            // 
            textBoxDataLogSectorEnd.Location = new Point(117, 95);
            textBoxDataLogSectorEnd.Name = "textBoxDataLogSectorEnd";
            textBoxDataLogSectorEnd.Size = new Size(143, 23);
            textBoxDataLogSectorEnd.TabIndex = 15;
            textBoxDataLogSectorEnd.TextAlign = HorizontalAlignment.Center;
            // 
            // label47
            // 
            label47.AutoSize = true;
            label47.Font = new Font("Verdana", 12F);
            label47.Location = new Point(6, 95);
            label47.Name = "label47";
            label47.Size = new Size(95, 18);
            label47.TabIndex = 14;
            label47.Text = "Sector End";
            // 
            // textBoxDataLogSectorBegin
            // 
            textBoxDataLogSectorBegin.Location = new Point(117, 66);
            textBoxDataLogSectorBegin.Name = "textBoxDataLogSectorBegin";
            textBoxDataLogSectorBegin.Size = new Size(143, 23);
            textBoxDataLogSectorBegin.TabIndex = 13;
            textBoxDataLogSectorBegin.TextAlign = HorizontalAlignment.Center;
            // 
            // label48
            // 
            label48.AutoSize = true;
            label48.Font = new Font("Verdana", 12F);
            label48.Location = new Point(6, 66);
            label48.Name = "label48";
            label48.Size = new Size(111, 18);
            label48.TabIndex = 12;
            label48.Text = "Sector Begin";
            // 
            // textBoxDataLogSamples
            // 
            textBoxDataLogSamples.Location = new Point(117, 37);
            textBoxDataLogSamples.Name = "textBoxDataLogSamples";
            textBoxDataLogSamples.Size = new Size(143, 23);
            textBoxDataLogSamples.TabIndex = 11;
            textBoxDataLogSamples.TextAlign = HorizontalAlignment.Center;
            // 
            // label49
            // 
            label49.AutoSize = true;
            label49.Font = new Font("Verdana", 12F);
            label49.Location = new Point(6, 37);
            label49.Name = "label49";
            label49.Size = new Size(77, 18);
            label49.TabIndex = 10;
            label49.Text = "Samples";
            // 
            // labelCOMStatus
            // 
            labelCOMStatus.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            labelCOMStatus.BackColor = Color.White;
            labelCOMStatus.BorderStyle = BorderStyle.FixedSingle;
            labelCOMStatus.Location = new Point(985, 7);
            labelCOMStatus.Name = "labelCOMStatus";
            labelCOMStatus.Size = new Size(63, 49);
            labelCOMStatus.TabIndex = 1;
            labelCOMStatus.Text = "COM";
            labelCOMStatus.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // buttonConnect
            // 
            buttonConnect.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            buttonConnect.Location = new Point(875, 7);
            buttonConnect.Name = "buttonConnect";
            buttonConnect.Size = new Size(100, 49);
            buttonConnect.TabIndex = 2;
            buttonConnect.Text = "Connect";
            buttonConnect.UseVisualStyleBackColor = true;
            buttonConnect.Click += buttonConnect_Click;
            // 
            // comboBoxCOMPort
            // 
            comboBoxCOMPort.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            comboBoxCOMPort.FormattingEnabled = true;
            comboBoxCOMPort.Location = new Point(763, 33);
            comboBoxCOMPort.Name = "comboBoxCOMPort";
            comboBoxCOMPort.Size = new Size(100, 23);
            comboBoxCOMPort.TabIndex = 3;
            comboBoxCOMPort.DropDown += comboBoxCOMPort_DropDown;
            // 
            // timerOneSecond
            // 
            timerOneSecond.Enabled = true;
            timerOneSecond.Interval = 1000;
            timerOneSecond.Tick += timerOneSecond_Tick;
            // 
            // comboBoxBaudRate
            // 
            comboBoxBaudRate.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            comboBoxBaudRate.FormattingEnabled = true;
            comboBoxBaudRate.Items.AddRange(new object[] { "230400", "460800", "921600" });
            comboBoxBaudRate.Location = new Point(763, 7);
            comboBoxBaudRate.Name = "comboBoxBaudRate";
            comboBoxBaudRate.Size = new Size(100, 23);
            comboBoxBaudRate.TabIndex = 4;
            // 
            // statusStrip1
            // 
            statusStrip1.Items.AddRange(new ToolStripItem[] { toolStripStatusLabel1 });
            statusStrip1.Location = new Point(0, 646);
            statusStrip1.Name = "statusStrip1";
            statusStrip1.Size = new Size(1055, 22);
            statusStrip1.TabIndex = 5;
            statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            toolStripStatusLabel1.Size = new Size(118, 17);
            toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            // 
            // groupBox1
            // 
            groupBox1.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            groupBox1.Controls.Add(labelRtc);
            groupBox1.Controls.Add(labelCatheter);
            groupBox1.Controls.Add(labelI2C);
            groupBox1.Controls.Add(labelSpi);
            groupBox1.Controls.Add(labelAccel);
            groupBox1.Controls.Add(labelStack);
            groupBox1.Controls.Add(labelLcd);
            groupBox1.Controls.Add(labelTouch);
            groupBox1.Controls.Add(label7124);
            groupBox1.Controls.Add(labelAdc);
            groupBox1.Controls.Add(labelFlash);
            groupBox1.Controls.Add(labelRam);
            groupBox1.Controls.Add(labelSys);
            groupBox1.Location = new Point(12, 7);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(745, 73);
            groupBox1.TabIndex = 6;
            groupBox1.TabStop = false;
            groupBox1.Text = "System Status";
            // 
            // labelRtc
            // 
            labelRtc.BackColor = SystemColors.ActiveBorder;
            labelRtc.BorderStyle = BorderStyle.FixedSingle;
            labelRtc.Font = new Font("Verdana", 8.25F);
            labelRtc.Location = new Point(654, 19);
            labelRtc.Name = "labelRtc";
            labelRtc.Size = new Size(48, 48);
            labelRtc.TabIndex = 12;
            labelRtc.Text = "RTC";
            labelRtc.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelCatheter
            // 
            labelCatheter.BackColor = SystemColors.ActiveBorder;
            labelCatheter.BorderStyle = BorderStyle.FixedSingle;
            labelCatheter.Font = new Font("Verdana", 8.25F);
            labelCatheter.Location = new Point(600, 19);
            labelCatheter.Name = "labelCatheter";
            labelCatheter.Size = new Size(48, 48);
            labelCatheter.TabIndex = 11;
            labelCatheter.Text = "CATH";
            labelCatheter.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelI2C
            // 
            labelI2C.BackColor = SystemColors.ActiveBorder;
            labelI2C.BorderStyle = BorderStyle.FixedSingle;
            labelI2C.Font = new Font("Verdana", 8.25F);
            labelI2C.Location = new Point(546, 19);
            labelI2C.Name = "labelI2C";
            labelI2C.Size = new Size(48, 48);
            labelI2C.TabIndex = 10;
            labelI2C.Text = "I2C";
            labelI2C.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelSpi
            // 
            labelSpi.BackColor = SystemColors.ActiveBorder;
            labelSpi.BorderStyle = BorderStyle.FixedSingle;
            labelSpi.Font = new Font("Verdana", 8.25F);
            labelSpi.Location = new Point(492, 19);
            labelSpi.Name = "labelSpi";
            labelSpi.Size = new Size(48, 48);
            labelSpi.TabIndex = 9;
            labelSpi.Text = "SPI";
            labelSpi.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelAccel
            // 
            labelAccel.BackColor = SystemColors.ActiveBorder;
            labelAccel.BorderStyle = BorderStyle.FixedSingle;
            labelAccel.Font = new Font("Verdana", 8.25F);
            labelAccel.Location = new Point(438, 19);
            labelAccel.Name = "labelAccel";
            labelAccel.Size = new Size(48, 48);
            labelAccel.TabIndex = 8;
            labelAccel.Text = "ACC";
            labelAccel.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelStack
            // 
            labelStack.BackColor = SystemColors.ActiveBorder;
            labelStack.BorderStyle = BorderStyle.FixedSingle;
            labelStack.Font = new Font("Verdana", 8.25F);
            labelStack.Location = new Point(384, 19);
            labelStack.Name = "labelStack";
            labelStack.Size = new Size(48, 48);
            labelStack.TabIndex = 7;
            labelStack.Text = "STK";
            labelStack.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelLcd
            // 
            labelLcd.BackColor = SystemColors.ActiveBorder;
            labelLcd.BorderStyle = BorderStyle.FixedSingle;
            labelLcd.Font = new Font("Verdana", 8.25F);
            labelLcd.Location = new Point(330, 19);
            labelLcd.Name = "labelLcd";
            labelLcd.Size = new Size(48, 48);
            labelLcd.TabIndex = 6;
            labelLcd.Text = "LCD";
            labelLcd.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelTouch
            // 
            labelTouch.BackColor = SystemColors.ActiveBorder;
            labelTouch.BorderStyle = BorderStyle.FixedSingle;
            labelTouch.Font = new Font("Verdana", 8.25F);
            labelTouch.Location = new Point(276, 19);
            labelTouch.Name = "labelTouch";
            labelTouch.Size = new Size(48, 48);
            labelTouch.TabIndex = 5;
            labelTouch.Text = "TCH";
            labelTouch.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label7124
            // 
            label7124.BackColor = SystemColors.ActiveBorder;
            label7124.BorderStyle = BorderStyle.FixedSingle;
            label7124.Font = new Font("Verdana", 8.25F);
            label7124.Location = new Point(222, 19);
            label7124.Name = "label7124";
            label7124.Size = new Size(48, 48);
            label7124.TabIndex = 4;
            label7124.Text = "7124";
            label7124.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelAdc
            // 
            labelAdc.BackColor = SystemColors.ActiveBorder;
            labelAdc.BorderStyle = BorderStyle.FixedSingle;
            labelAdc.Font = new Font("Verdana", 8.25F);
            labelAdc.Location = new Point(168, 19);
            labelAdc.Name = "labelAdc";
            labelAdc.Size = new Size(48, 48);
            labelAdc.TabIndex = 3;
            labelAdc.Text = "ADC";
            labelAdc.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelFlash
            // 
            labelFlash.BackColor = SystemColors.ActiveBorder;
            labelFlash.BorderStyle = BorderStyle.FixedSingle;
            labelFlash.Font = new Font("Verdana", 8.25F);
            labelFlash.Location = new Point(114, 19);
            labelFlash.Name = "labelFlash";
            labelFlash.Size = new Size(48, 48);
            labelFlash.TabIndex = 2;
            labelFlash.Text = "FLA";
            labelFlash.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelRam
            // 
            labelRam.BackColor = SystemColors.ActiveBorder;
            labelRam.BorderStyle = BorderStyle.FixedSingle;
            labelRam.Font = new Font("Verdana", 8.25F);
            labelRam.Location = new Point(60, 19);
            labelRam.Name = "labelRam";
            labelRam.Size = new Size(48, 48);
            labelRam.TabIndex = 1;
            labelRam.Text = "RAM";
            labelRam.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelSys
            // 
            labelSys.BackColor = SystemColors.ActiveBorder;
            labelSys.BorderStyle = BorderStyle.FixedSingle;
            labelSys.Font = new Font("Verdana", 8.25F);
            labelSys.Location = new Point(6, 19);
            labelSys.Name = "labelSys";
            labelSys.Size = new Size(48, 48);
            labelSys.TabIndex = 0;
            labelSys.Text = "SYS";
            labelSys.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // progressBarDataDownload
            // 
            progressBarDataDownload.Location = new Point(19, 141);
            progressBarDataDownload.Name = "progressBarDataDownload";
            progressBarDataDownload.Size = new Size(263, 42);
            progressBarDataDownload.TabIndex = 21;
            // 
            // GUIForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1055, 668);
            Controls.Add(groupBox1);
            Controls.Add(statusStrip1);
            Controls.Add(comboBoxBaudRate);
            Controls.Add(comboBoxCOMPort);
            Controls.Add(buttonConnect);
            Controls.Add(labelCOMStatus);
            Controls.Add(tabControl1);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "GUIForm";
            Text = "CUR Diagnostics";
            FormClosing += GUIForm_FormClosing;
            tabControl1.ResumeLayout(false);
            tabPageStatus.ResumeLayout(false);
            tabPageStatus.PerformLayout();
            groupBox16.ResumeLayout(false);
            groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dataGridViewStatusMsg).EndInit();
            tabPageDebug.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dataGridViewDebugStats).EndInit();
            tabPageLCD.ResumeLayout(false);
            groupBox5.ResumeLayout(false);
            groupBox5.PerformLayout();
            groupBox4.ResumeLayout(false);
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            tabPageTouch.ResumeLayout(false);
            groupBox9.ResumeLayout(false);
            groupBox9.PerformLayout();
            groupBox8.ResumeLayout(false);
            groupBox8.PerformLayout();
            tabPageAccel.ResumeLayout(false);
            groupBox6.ResumeLayout(false);
            groupBox6.PerformLayout();
            tabPageRtc.ResumeLayout(false);
            groupBox7.ResumeLayout(false);
            groupBox7.PerformLayout();
            tabPageAd7124.ResumeLayout(false);
            groupBox11.ResumeLayout(false);
            groupBox11.PerformLayout();
            groupBox10.ResumeLayout(false);
            groupBox10.PerformLayout();
            tabPageFlash.ResumeLayout(false);
            groupBox15.ResumeLayout(false);
            groupBox15.PerformLayout();
            groupBox13.ResumeLayout(false);
            groupBox12.ResumeLayout(false);
            groupBox12.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridViewFlashIds).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewFlashRegisters).EndInit();
            tabPageAdc.ResumeLayout(false);
            groupBox14.ResumeLayout(false);
            groupBox14.PerformLayout();
            tabPageBarometric.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dataGridViewBarometric).EndInit();
            tabPageDataLog.ResumeLayout(false);
            groupBox18.ResumeLayout(false);
            groupBox18.PerformLayout();
            groupBox17.ResumeLayout(false);
            groupBox17.PerformLayout();
            statusStrip1.ResumeLayout(false);
            statusStrip1.PerformLayout();
            groupBox1.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }


        #endregion

        private TabControl tabControl1;
        private TabPage tabPageStatus;
        private Label labelCOMStatus;
        private Button buttonConnect;
        private ComboBox comboBoxCOMPort;
        private System.Windows.Forms.Timer timerOneSecond;
        private ComboBox comboBoxBaudRate;
        private ListBox listBox1;
        private Label label1;
        private TabPage tabPageDebug;
        private ListBox listBoxDebugLogList;
        private Button buttonDebugClearList;
        private DataGridView dataGridViewDebugStats;
        private DataGridViewTextBoxColumn NameCol;
        private DataGridViewTextBoxColumn Value;
        private StatusStrip statusStrip1;
        private ToolStripStatusLabel toolStripStatusLabel1;
        private GroupBox groupBox1;
        private Label labelSys;
        private TabPage tabPageLCD;
        private TabPage tabPageTouch;
        private TabPage tabPageAccel;
        private GroupBox groupBox2;
        private DataGridView dataGridViewStatusMsg;
        private DataGridViewTextBoxColumn Parameter;
        private DataGridViewTextBoxColumn Value1;
        private GroupBox groupBox3;
        private Button buttonLoad;
        private ProgressBar progressBarLoading;
        private Label labelFileName;
        private Button buttonSelectFile;
        private Label label2;
        private ComboBox comboBoxWindow;
        private Label labelLoadStatus;
        private GroupBox groupBox4;
        private Button buttonLcdSetWindow;
        private Label label3;
        private ComboBox comboBoxDisplayWindow;
        private Button buttonDisplayDDown;
        private Button buttonDisplayUp;
        private GroupBox groupBox5;
        private Button buttonBackLightDown;
        private Button buttonBacklightUp;
        private TextBox textBoxBackLightValue;
        private Button buttonSetBacklight;
        private Button buttonBackLightOn;
        private Button buttonBackLightOff;
        private Label labelFlash;
        private Label labelRam;
        private Label labelCatheter;
        private Label labelI2C;
        private Label labelSpi;
        private Label labelAccel;
        private Label labelStack;
        private Label labelLcd;
        private Label labelTouch;
        private Label label7124;
        private Label labelAdc;
        private Label labelRtc;
        private Button buttonClearTouchEvents;
        private ListBox listBoxTouchEvents;
        private GroupBox groupBox9;
        private TextBox textBoxTouchVendorId;
        private Label label25;
        private TextBox textBoxTouchFirmwareId;
        private Label label24;
        private TextBox textBoxTouchVersionLow;
        private Label label23;
        private TextBox textBoxTouchVersionHigh;
        private Label label22;
        private Button buttonTouchInit;
        private Button buttonTouchStatus;
        private Button buttonTouchReadAdv;
        private GroupBox groupBox8;
        private Label label27;
        private Label label26;
        private Button buttonTouchRead;
        private Button buttonTouchClear;
        private TextBox textBoxTouchYMax;
        private TextBox textBoxTouchYMin;
        private Label label20;
        private TextBox textBoxTouchXMax;
        private TextBox textBoxTouchXMin;
        private Label label21;
        private TextBox textBoxTouchArea;
        private Label label18;
        private TextBox textBoxTouchWeight;
        private Label label19;
        private TextBox textBoxTouchYRaw;
        private TextBox textBoxTouchYPosition;
        private Label label17;
        private TextBox textBoxTouchXRaw;
        private TextBox textBoxTouchXPosition;
        private Label label16;
        private TextBox textBoxTouchEvent;
        private Label label15;
        private TextBox textBoxTouchPoints;
        private Label label14;
        private TabPage tabPageRtc;
        private GroupBox groupBox7;
        private TextBox textBoxRtcSecRead;
        private TextBox textBoxRtcSecWrite;
        private Label label10;
        private TextBox textBoxRtcMinRead;
        private TextBox textBoxRtcMinWrite;
        private Label label9;
        private TextBox textBoxRtcHourRead;
        private Button buttonRtcRead;
        private Button buttonRtcWrite;
        private TextBox textBoxRtcHourWrite;
        private Label label8;
        private GroupBox groupBox6;
        private TextBox textBoxAccelZ;
        private Label label4;
        private TextBox textBoxAccelY;
        private Label label5;
        private TextBox textBoxAccelX;
        private Label label6;
        private Button buttonAccelRead;
        private TabPage tabPageAd7124;
        private GroupBox groupBox10;
        private Button buttonAD7124Read;
        private TextBox textBoxAd7124Volts;
        private Label label12;
        private TextBox textBoxAd7124CountsDec;
        private Label label11;
        private TextBox textBoxAd7124CountsHex;
        private Label label7;
        private GroupBox groupBox11;
        private TextBox textBoxAd7124Status;
        private Label label13;
        private Button buttonAd7124Reset;
        private Button buttonAd7124StatusRead;
        private TextBox textBoxAd7124Channel;
        private Label label37;
        private TextBox textBoxAd7124ErrorEn;
        private Label label38;
        private TextBox textBoxAd7124Filter;
        private Label label35;
        private TextBox textBoxAd7124Config;
        private Label label36;
        private TextBox textBoxAd7124Offset;
        private Label label34;
        private TextBox textBoxAd7124Error;
        private Label label31;
        private TextBox textBoxAd7124Id;
        private Label label32;
        private TextBox textBoxAd7124Io2;
        private Label label29;
        private TextBox textBoxAd7124Io1;
        private Label label30;
        private TextBox textBoxAd7124Control;
        private Label label28;
        private TabPage tabPageFlash;
        private GroupBox groupBox12;
        private DataGridView dataGridViewFlashRegisters;
        private TextBox textBoxFlashStatus2;
        private Label label39;
        private TextBox textBoxFlashStatus1;
        private Label label33;
        private Button buttonFlashGetStatus;
        private DataGridViewTextBoxColumn Register;
        private DataGridViewTextBoxColumn RegValues;
        private DataGridView dataGridViewFlashIds;
        private DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
        private DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
        private GroupBox groupBox13;
        private Button buttonFlashClearProg;
        private Button buttonFlashReset;
        private TextBox textBoxAd7124mmHg;
        private Label label40;
        private TabPage tabPageAdc;
        private GroupBox groupBox14;
        private Button buttonBatRead;
        private TextBox textBoxBatVolts;
        private Label label42;
        private TextBox textBoxBatCountDec;
        private Label label43;
        private TextBox textBoxBatCountsHex;
        private Label label44;
        private Button buttonFlashTest;
        private Label label41;
        private ComboBox comboBoxSlot;
        private GroupBox groupBox15;
        private Label label46;
        private TextBox textBoxFlashReadAddress;
        private Label label45;
        private ComboBox comboBoxFlashReadSlot;
        private Button buttonFlashRead;
        private TextBox textBoxFlashReadData;
        private GroupBox groupBox16;
        private ComboBox comboBoxStateSelect;
        private Button buttonSetState;
        private Label labelSystemState;
        private Button buttonTouchDebug;
        private Button buttonTouchIdle;
        private TabPage tabPageBarometric;
        private DataGridView dataGridViewBarometric;
        private DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
        private DataGridViewTextBoxColumn dataGridViewTextBoxColumn4;
        private TabPage tabPageDataLog;
        private GroupBox groupBox18;
        private GroupBox groupBox17;
        private Button buttonDataLogReadEventLog;
        private TextBox textBoxDataLogSectorEnd;
        private Label label47;
        private TextBox textBoxDataLogSectorBegin;
        private Label label48;
        private TextBox textBoxDataLogSamples;
        private Label label49;
        private Label labelDownloadStatus;
        private Button buttonDownload;
        private TextBox textBoxStartSample;
        private Label label50;
        private ProgressBar progressBarDataDownload;
    }
}
