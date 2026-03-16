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
            tabControl1 = new TabControl();
            tabPage1 = new TabPage();
            label1 = new Label();
            listBox2 = new ListBox();
            listBox1 = new ListBox();
            buttonHello = new Button();
            labelCOMStatus = new Label();
            buttonConnect = new Button();
            comboBoxCOMPort = new ComboBox();
            timerOneSecond = new System.Windows.Forms.Timer(components);
            comboBoxBaudRate = new ComboBox();
            tabControl1.SuspendLayout();
            tabPage1.SuspendLayout();
            SuspendLayout();
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(tabPage1);
            tabControl1.Location = new Point(12, 50);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(776, 377);
            tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            tabPage1.Controls.Add(label1);
            tabPage1.Controls.Add(listBox2);
            tabPage1.Controls.Add(listBox1);
            tabPage1.Controls.Add(buttonHello);
            tabPage1.Location = new Point(4, 24);
            tabPage1.Name = "tabPage1";
            tabPage1.Padding = new Padding(3);
            tabPage1.Size = new Size(768, 349);
            tabPage1.TabIndex = 0;
            tabPage1.Text = "Testing";
            tabPage1.UseVisualStyleBackColor = true;
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
            // listBox2
            // 
            listBox2.FormattingEnabled = true;
            listBox2.Location = new Point(147, 170);
            listBox2.Name = "listBox2";
            listBox2.Size = new Size(490, 94);
            listBox2.TabIndex = 1;
            // 
            // listBox1
            // 
            listBox1.FormattingEnabled = true;
            listBox1.Location = new Point(147, 36);
            listBox1.Name = "listBox1";
            listBox1.Size = new Size(490, 94);
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
            // labelCOMStatus
            // 
            labelCOMStatus.BackColor = Color.White;
            labelCOMStatus.BorderStyle = BorderStyle.FixedSingle;
            labelCOMStatus.Location = new Point(725, 7);
            labelCOMStatus.Name = "labelCOMStatus";
            labelCOMStatus.Size = new Size(63, 49);
            labelCOMStatus.TabIndex = 1;
            labelCOMStatus.Text = "COM";
            labelCOMStatus.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // buttonConnect
            // 
            buttonConnect.Location = new Point(615, 7);
            buttonConnect.Name = "buttonConnect";
            buttonConnect.Size = new Size(100, 49);
            buttonConnect.TabIndex = 2;
            buttonConnect.Text = "Connect";
            buttonConnect.UseVisualStyleBackColor = true;
            buttonConnect.Click += buttonConnect_Click;
            // 
            // comboBoxCOMPort
            // 
            comboBoxCOMPort.FormattingEnabled = true;
            comboBoxCOMPort.Location = new Point(503, 33);
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
            comboBoxBaudRate.FormattingEnabled = true;
            comboBoxBaudRate.Items.AddRange(new object[] { "115200", "230400", "460800", "921600" });
            comboBoxBaudRate.Location = new Point(503, 7);
            comboBoxBaudRate.Name = "comboBoxBaudRate";
            comboBoxBaudRate.Size = new Size(100, 23);
            comboBoxBaudRate.TabIndex = 4;
            // 
            // GUIForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(comboBoxBaudRate);
            Controls.Add(comboBoxCOMPort);
            Controls.Add(buttonConnect);
            Controls.Add(labelCOMStatus);
            Controls.Add(tabControl1);
            Name = "GUIForm";
            Text = "CUR Diagnostics";
            FormClosing += GUIForm_FormClosing;
            tabControl1.ResumeLayout(false);
            tabPage1.ResumeLayout(false);
            tabPage1.PerformLayout();
            ResumeLayout(false);
        }


        #endregion

        private TabControl tabControl1;
        private TabPage tabPage1;
        private Button buttonHello;
        private Label labelCOMStatus;
        private Button buttonConnect;
        private ComboBox comboBoxCOMPort;
        private System.Windows.Forms.Timer timerOneSecond;
        private ComboBox comboBoxBaudRate;
        private ListBox listBox1;
        private ListBox listBox2;
        private Label label1;
    }
}
