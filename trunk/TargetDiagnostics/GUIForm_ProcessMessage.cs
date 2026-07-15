/********************************************************************
*
*   GUIForm_ProcessMessage.cs
*
*   Description: Handles routing of individual incoming messages to
*   the proper handler.
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

using static CURDiags.Commands;
using static CURDiags.Enums;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace CURDiags
{
    /// <summary>
    /// This source file contains the ProcessIncomingMessage() method to handle
    /// the routing of all incoming messages.
    /// </summary>
    public partial class GUIForm : Form
    {
        /// <summary>
        /// Track the time of our last message
        /// </summary>
        DateTime mLastMessageReceived = DateTime.MinValue;

        /// <summary>
        /// System state strings
        /// </summary>
        string[] mStateText = {
            "eSTATE_POST",
            "eSTATE_SPLASH",
            "eSTATE_READY_TO_CONNECT",
            "eSTATE_SELECT_UNITS",
            "eSTATE_MEASURING",
            "eSTATE_COMPLETE_SELECTED",
            "eSTATE_COMPLETE",
            "eSTATE_TEST",
            "eSTATE_ERROR"
        };

        /// <summary>
        /// Process a message from the diagnostics
        /// </summary>
        internal void ProcessIncomingMessage(byte[] data)
        {
            if (data.Length < Commands.Sizeof_sCommandHeader)
            {
                return;
            }

            Logger.LogMessage($"ProcessIncomingMessage() {(eDiagnosticCommands)data[Commands.MessageCommandIndex]}");
            eDiagnosticCommands command = (eDiagnosticCommands)data[(int)Commands.MessageCommandIndex];
            mLastMessageReceived = DateTime.Now;    // Update our last known message time

            switch (command)
            {
                case eDiagnosticCommands.eDIAG_HELLO:
                    AddToMessageListBox(data);
                    break;

                case eDiagnosticCommands.eDIAG_STATUS:
                    AddToMessageListBox(data);
                    Commands.sDIAG_Status status = new Commands.sDIAG_Status();
                    Utils.MarshalPtrToStruct(data, out status);
                    UpdateStatusMessage(status);
                    break;

                case eDiagnosticCommands.eDIAG_LCD_DATA_ACK:
                case eDiagnosticCommands.eDIAG_FLASH_ACK:

                    AddToMessageListBox(data);

                    Commands.sFlashAck ack = new Commands.sFlashAck();
                    Utils.MarshalPtrToStruct(data, out ack);
                    if (ack.status == 1)
                        autoEvent.Set();
                        break;

                case eDiagnosticCommands.eDIAG_AD7124_GET_STATUS:
                    Commands.sAD7124Status ad7124status = new Commands.sAD7124Status();
                    Utils.MarshalPtrToStruct(data, out ad7124status);
                    UpdateAD7124StatusMessage(ad7124status);
                    break;

                case eDiagnosticCommands.eDIAG_AD7124_READ_DATA:
                    Commands.sAD7124ReadData ad7124Read = new Commands.sAD7124ReadData();
                    Utils.MarshalPtrToStruct(data, out ad7124Read);
                    UpdateAD7124ReadData(ad7124Read);
                    break;

                case eDiagnosticCommands.eDIAG_ACCEL_READ:
                    Commands.sAccelReadData accelRead = new Commands.sAccelReadData();
                    Utils.MarshalPtrToStruct(data, out  accelRead);
                    UpdateAccelReadData(accelRead);
                    break;

                    case eDiagnosticCommands.eDIAG_RTC_STATUS:
                    Commands.sRtcReadData rtcRead = new Commands.sRtcReadData();
                    Utils.MarshalPtrToStruct(data, out  rtcRead);
                    UpdateRtcData(rtcRead);
                    break;

                case eDiagnosticCommands.eDIAG_FLASH_STATUS:
                    Commands.sFlashStatusData flashStatus = new Commands.sFlashStatusData();
                    Utils.MarshalPtrToStruct(data, out flashStatus);
                    UpdateFlashStatus(flashStatus);
                    break;

                case eDiagnosticCommands.eDIAG_FLASH_READ:
                    Commands.sFlashData flashRead = new Commands.sFlashData();
                    Utils.MarshalPtrToStruct(data, out flashRead);
                    UpdateFlashRead(flashRead);
                    break;

                case eDiagnosticCommands.eDIAG_ADC_READ:
                    Commands.sAdcReadData adcData = new Commands.sAdcReadData();
                    Utils.MarshalPtrToStruct(data, out adcData);
                    UpdateBattery(adcData);
                    break;

                case eDiagnosticCommands.eDIAG_TOUCH_READ:
                    Commands.sTouchReadData touchData = new Commands.sTouchReadData();
                    Utils.MarshalPtrToStruct(data, out touchData);
                    UpdateTouch(touchData);
                    break;

                case eDiagnosticCommands.eDIAG_READ_BAROMETRIC:
                    Commands.sBarometricData barometricData = new Commands.sBarometricData();
                    Utils.MarshalPtrToStruct(data, out barometricData);
                    UpdateBarometric(barometricData);
                    break;

                default:
                    Logger.LogError($"ProcessIncomingMessage() unhandled message {data[Commands.MessageCommandIndex]}");
                    break;
            }
        }

        private void AddToMessageListBox(byte[] data)
        {
            listBox1.Items.Insert(0, BitConverter.ToString(data.ToArray(), 0, data.Length));
        }

        /// <summary>
        /// Update the gui with new status data
        /// </summary>
        private void UpdateStatusMessage(Commands.sDIAG_Status status)
        {
            int r = 0;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.versionMajor + "." + status.versionMinor + "." + status.versionBuild;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.sysTicks;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.idleTicks;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.skippedTicks;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.minIdle;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.maxIdle;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = status.state;
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = "0x" + status.errors.ToString("X8");
            dataGridViewStatusMsg.Rows[r++].Cells[1].Value = "0x" + status.health.ToString("X8");

            // Update state label
            UpdateLabel(labelSystemState, status.state < mStateText.Length ? mStateText[status.state] : "UNKNOWN");

            // Update health labels
            UpdateLabelColor(labelSys, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemArm)) > 0) ? Color.Green : Color.Red);

            UpdateLabelColor(labelFlash, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemFlash)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelRam, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemRam)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelAdc, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemAdc)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(label7124, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystem7124)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelTouch, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemTouch)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelRtc, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemRtc)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelLcd, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemLcd)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelStack, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemStack)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelAccel, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemAccel)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelSpi, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemSpi)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelI2C, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemI2C)) > 0) ? Color.Green : Color.Red);
            UpdateLabelColor(labelCatheter, ((status.health & 0x1 << ((int)Enums.eSubsystems.eSystemCath)) > 0) ? Color.Green : Color.Red);
        }

        /// <summary>
        /// Update the AD7124 status
        /// </summary>
        private void UpdateAD7124StatusMessage(Commands.sAD7124Status status)
        {
            UpdateTextBox(textBoxAd7124Status, "0x" + status.status.ToString("X4"));
            UpdateTextBox(textBoxAd7124Control, "0x" + status.control.ToString("X4"));
            UpdateTextBox(textBoxAd7124Io1, "0x" + status.io1.ToString("X4"));
            UpdateTextBox(textBoxAd7124Io2, "0x" + status.io2.ToString("X4"));
            UpdateTextBox(textBoxAd7124Id, "0x" + status.id.ToString("X4"));
            UpdateTextBox(textBoxAd7124Error, "0x" + status.error.ToString("X4"));
            UpdateTextBox(textBoxAd7124ErrorEn, "0x" + status.error_en.ToString("X4"));
            UpdateTextBox(textBoxAd7124Channel, "0x" + status.channel.ToString("X4"));
            UpdateTextBox(textBoxAd7124Config, "0x" + status.config.ToString("X4"));
            UpdateTextBox(textBoxAd7124Filter, "0x" + status.filter.ToString("X4"));
            UpdateTextBox(textBoxAd7124Offset, "0x" + status.offset.ToString("X4"));
        }

        /// <summary>
        /// Update the AD7124 Data
        /// </summary>
        private void UpdateAD7124ReadData(Commands.sAD7124ReadData read)
        {
            UpdateTextBox(textBoxAd7124CountsHex, "0x" + read.counts.ToString("X4"));
            UpdateTextBox(textBoxAd7124CountsDec, read.counts.ToString());
            float mV = read.mLastVoltage * 1000;    // Convert to mV
            UpdateTextBox(textBoxAd7124Volts, mV.ToString("F4"));
            UpdateTextBox(textBoxAd7124mmHg, read.engValue.ToString("F1"));
        }

        /// <summary>
        /// Update the Accelerometer data
        /// </summary>
        private void UpdateAccelReadData(Commands.sAccelReadData read)
        {
            UpdateTextBox(textBoxAccelX, read.x.ToString());
            UpdateTextBox(textBoxAccelY, read.y.ToString());
            UpdateTextBox(textBoxAccelZ, read.z.ToString());
        }

        /// <summary>
        /// Update the RTC data
        /// </summary>
        private void UpdateRtcData(Commands.sRtcReadData read)
        {
            UpdateTextBox(textBoxRtcHourRead, read.hour.ToString());
            UpdateTextBox(textBoxRtcMinRead, read.min.ToString());
            UpdateTextBox(textBoxRtcSecRead, read.second.ToString());
        }

        /// <summary>
        /// Update flash status
        /// </summary>
        private void UpdateFlashStatus(Commands.sFlashStatusData status)
        {
            UpdateTextBox(textBoxFlashStatus1, "0x" + status.statusReg1.ToString("X2"));
            UpdateTextBox(textBoxFlashStatus2, "0x" + status.statusReg2.ToString("X2"));

            int r = 0;
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "0x" + status.configReg1.ToString("X2");
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "0x" + status.configReg2.ToString("X2");
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "0x" + status.configReg3.ToString("X2");
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "0x" + status.configReg4.ToString("X2");
            dataGridViewFlashRegisters.Rows[r++].Cells[1].Value = "0x" + status.configReg5.ToString("X2");

            r = 0;
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.manufactureId.ToString("X2");
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.memInterface.ToString("X2");
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.density.ToString("X2");
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.idLen.ToString("X2");
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.config.ToString("X2");
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.family.ToString("X2");
            dataGridViewFlashIds.Rows[r++].Cells[1].Value = "0x" + status.uniqueId.ToString("X8");
        }

        /// <summary>
        /// Update flash read data
        /// </summary>
        private void UpdateFlashRead(Commands.sFlashData data)
        {
            string str = "";
            int count = 1;
            foreach (byte b in data.data)
            {
                str += "0x" + b.ToString("X2") + " ";
                if (count % 8 == 0) str += "   ";
                if (count % 16 == 0) str += System.Environment.NewLine;
                count++;
            }
            UpdateTextBox(textBoxFlashReadData, str);
        }

        /// <summary>
        /// Update the battery counts and volts
        /// </summary>
        private void UpdateBattery(Commands.sAdcReadData data)
        {
            UpdateTextBox(textBoxBatCountsHex, "0x" + data.counts.ToString("X4"));
            UpdateTextBox(textBoxBatCountDec, data.counts.ToString());
            UpdateTextBox(textBoxBatVolts, data.volts.ToString("F2"));

            // Log data for evaluation
            DateTime now = DateTime.Now;
            string filename = "" + now.Month.ToString() + now.Day.ToString() + now.Year.ToString() + "_BatteryLog.txt";
            string str = now.ToLongTimeString() + ", " + data.counts.ToString() + ", " + data.volts.ToString("F2") + System.Environment.NewLine;
            File.AppendAllText(filename, str);
        }

        /// <summary>
        /// Update the touch data
        /// </summary>
        private void UpdateTouch(Commands.sTouchReadData data)
        {
            UpdateTextBox(textBoxTouchXPosition, data.xPos.ToString());
            UpdateTextBox(textBoxTouchYPosition, data.yPos.ToString());
            UpdateTextBox(textBoxTouchXRaw, data.xPosRaw.ToString());
            UpdateTextBox(textBoxTouchYRaw, data.yPosRaw.ToString());
        }

        /// <summary>
        /// Update the Barometric data
        /// </summary>
        private void UpdateBarometric(Commands.sBarometricData data)
        {
            int r = 0;
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.lastPressure.ToString("F1");
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.lastTemperature.ToString("F1");
            dataGridViewBarometric.Rows[r++].Cells[1].Value = "0x" + data.prom.ToString();
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.sensitivity.ToString();
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.offset.ToString();
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.tcoeffSens.ToString();
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.tcoeffOffset.ToString();
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.tref.ToString();
            dataGridViewBarometric.Rows[r++].Cells[1].Value = data.tempSens.ToString();
        }

    }  // end class
}  // end namespace
