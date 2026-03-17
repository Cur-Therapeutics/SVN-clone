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
            tabPageTesting = new TabPage();
            label1 = new Label();
            listBox1 = new ListBox();
            buttonHello = new Button();
            tabPageDebug = new TabPage();
            dataGridViewDebugStats = new DataGridView();
            NameCol = new DataGridViewTextBoxColumn();
            Value = new DataGridViewTextBoxColumn();
            buttonDebugClearList = new Button();
            listBoxDebugLogList = new ListBox();
            labelCOMStatus = new Label();
            buttonConnect = new Button();
            comboBoxCOMPort = new ComboBox();
            timerOneSecond = new System.Windows.Forms.Timer(components);
            comboBoxBaudRate = new ComboBox();
            statusStrip1 = new StatusStrip();
            toolStripStatusLabel1 = new ToolStripStatusLabel();
            tabControl1.SuspendLayout();
            tabPageTesting.SuspendLayout();
            tabPageDebug.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridViewDebugStats).BeginInit();
            statusStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(tabPageTesting);
            tabControl1.Controls.Add(tabPageDebug);
            tabControl1.Location = new Point(12, 50);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(1031, 377);
            tabControl1.TabIndex = 0;
            // 
            // tabPageTesting
            // 
            tabPageTesting.Controls.Add(label1);
            tabPageTesting.Controls.Add(listBox1);
            tabPageTesting.Controls.Add(buttonHello);
            tabPageTesting.Location = new Point(4, 24);
            tabPageTesting.Name = "tabPageTesting";
            tabPageTesting.Padding = new Padding(3);
            tabPageTesting.Size = new Size(1023, 349);
            tabPageTesting.TabIndex = 0;
            tabPageTesting.Text = "Testing";
            tabPageTesting.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(150, 10);
            label1.Name = "label1";
            label1.Size = new Size(112, 15);
            label1.TabIndex = 2;
            label1.Text = "Incoming messages";
            // 
            // listBox1
            // 
            listBox1.FormattingEnabled = true;
            listBox1.Location = new Point(147, 36);
            listBox1.Name = "listBox1";
            listBox1.Size = new Size(490, 289);
            listBox1.TabIndex = 1;
            // 
            // buttonHello
            // 
            buttonHello.Location = new Point(20, 19);
            buttonHello.Name = "buttonHello";
            buttonHello.Size = new Size(75, 61);
            buttonHello.TabIndex = 0;
            buttonHello.Text = "Hello";
            buttonHello.UseVisualStyleBackColor = true;
            buttonHello.Click += buttonHello_Click;
            // 
            // tabPageDebug
            // 
            tabPageDebug.Controls.Add(dataGridViewDebugStats);
            tabPageDebug.Controls.Add(buttonDebugClearList);
            tabPageDebug.Controls.Add(listBoxDebugLogList);
            tabPageDebug.Location = new Point(4, 24);
            tabPageDebug.Name = "tabPageDebug";
            tabPageDebug.Size = new Size(1023, 349);
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
            dataGridViewDebugStats.Size = new Size(451, 248);
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
            listBoxDebugLogList.Size = new Size(443, 304);
            listBoxDebugLogList.TabIndex = 2;
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
            comboBoxBaudRate.Items.AddRange(new object[] { "115200", "230400", "460800", "921600" });
            comboBoxBaudRate.Location = new Point(763, 7);
            comboBoxBaudRate.Name = "comboBoxBaudRate";
            comboBoxBaudRate.Size = new Size(100, 23);
            comboBoxBaudRate.TabIndex = 4;
            // 
            // statusStrip1
            // 
            statusStrip1.Items.AddRange(new ToolStripItem[] { toolStripStatusLabel1 });
            statusStrip1.Location = new Point(0, 428);
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
            // GUIForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1055, 450);
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
            Load += GUIForm_Load;
            SizeChanged += GUIForm_SizeChanged;
            tabControl1.ResumeLayout(false);
            tabPageTesting.ResumeLayout(false);
            tabPageTesting.PerformLayout();
            tabPageDebug.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dataGridViewDebugStats).EndInit();
            statusStrip1.ResumeLayout(false);
            statusStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }


        #endregion

        private TabControl tabControl1;
        private TabPage tabPageTesting;
        private Button buttonHello;
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
    }
}
