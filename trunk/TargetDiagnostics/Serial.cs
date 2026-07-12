/********************************************************************
*
*   Serial.cs
*
*   Description: SerialPort wrapper.
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
using static CURDiags.Enums;

namespace CURDiags
{
    public class IncomingMessageEventArgs : EventArgs
    {
        public byte[] data;

        public IncomingMessageEventArgs(byte[] data) { this.data = data; }
    }


    /// <summary>
    /// Provides access to the serial port for diagnostics.
    /// </summary>
    public class Serial
    {
        /// <summary>
        /// Publish an event indicating a new message has been received.
        /// </summary>
        public event EventHandler<IncomingMessageEventArgs>? IncomingMessage;

        protected virtual void OnIncomingMessage(IncomingMessageEventArgs ex)
        {
            IncomingMessage?.Invoke(this, ex);
        }


        private const int MaxRememberedSentMessages = 100;
        private const int MaxIncomingMessageSize = 1000;
        private const int IncomingMessageTimeoutMs = 500;
        private const int SerialResetDelayMs = 50;

        /// <summary>
        /// Our serial port object.
        /// </summary>
        private SerialPort? _SerialPort;

        /// <summary>
        /// RX buffer.
        /// </summary>
        private readonly List<byte> _rxBuffer = new List<byte>();

        private readonly object _SerialPortLock = new object();
        private readonly object _rxLock = new object();

        public bool IsLoggingBuffers = false;

        /// <summary>
        /// Receive state variables.
        /// </summary>
        private const byte RX_START_BYTE = Commands.START_BYTE;

        /// <summary>
        /// Comms timeout tracker.
        /// </summary>
        public DateTime LastDataTime { get; private set; } = DateTime.MinValue;

        public Serial()
        {
        }

        public bool IsOpen => _SerialPort != null && _SerialPort.IsOpen;

        public bool IsClosing { get; private set; }

        public int BytesToRead => IsOpen ? _SerialPort!.BytesToRead : 0;

        public bool OpenPort(string portName, int baudRate)
        {
            try
            {
                Close();

                IsClosing = false;

                SerialPort port = new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One);
                port.DataReceived += Port_DataReceived;
                port.Open();
                _ = port.ReadExisting();
                port.DiscardInBuffer();

                lock (_SerialPortLock)
                {
                    _SerialPort = port;
                }

                return true;
            }
            catch (Exception e)
            {
                Logger.LogMessage(e, "OpenPort()");
                return false;
            }
        }

        public void Close()
        {
            IsClosing = true;

            SerialPort? port;

            lock (_SerialPortLock)
            {
                port = _SerialPort;
                _SerialPort = null;
            }

            if (port == null)
            {
                return;
            }

            try
            {
                port.DataReceived -= Port_DataReceived;
            }
            catch (Exception ex)
            {
                Logger.LogMessage(ex, "Close() detach DataReceived");
            }

            try
            {
                if (port.IsOpen)
                {
                    port.Close();
                }
            }
            catch (Exception ex)
            {
                Logger.LogMessage(ex, "Close() port.Close");
            }

            try
            {
                port.Dispose();
            }
            catch (Exception ex)
            {
                Logger.LogMessage(ex, "Close() port.Dispose");
            }
        }

        internal static readonly List<Tuple<int, byte[], int, DateTime>> _sentMessages = new List<Tuple<int, byte[], int, DateTime>>();

        internal bool SendData(byte[] data, int count)
        {
            try
            {
                return _SendData(data, count);
            }
            catch (Exception ex)
            {
                Logger.LogMessage(ex, "SendData()");
                return false;
            }
        }

        private bool _SendData(byte[] data, int count)
        {
            if (!IsOpen)
            {
                Logger.LogError("SendData() called while port is closed.");
                return false;
            }

            if (data == null)
            {
                throw new ArgumentNullException(nameof(data));
            }

            if (count <= 0 || count > data.Length)
            {
                throw new ArgumentOutOfRangeException(nameof(count));
            }

            eDiagnosticCommands command = (eDiagnosticCommands)data[Commands.MessageCommandIndex];

            lock (_sentMessages)
            {
                _sentMessages.Insert(0, new Tuple<int, byte[], int, DateTime>(data[(int)Commands.MessageSeqIdIndex], data.Take(count).ToArray(), count, DateTime.Now));
                while (_sentMessages.Count > MaxRememberedSentMessages)
                {
                    _sentMessages.RemoveAt(_sentMessages.Count - 1);
                }
            }

            //lock (_SerialPortLock)
            {
                if (_SerialPort == null || !_SerialPort.IsOpen)
                {
                    Logger.LogError("SendData() lost the COM port before write.");
                    return false;
                }

                try
                {
                    if (IsLoggingBuffers)
                    {
                        Logger.LogBuffer(data, count, $"TX {(eDiagnosticCommands)data[Commands.MessageCommandIndex]}");
                        byte checksum = Commands.ComputeChecksum(data, count);
                        Logger.LogMessage($"TX checksum: {checksum:X2}");
                    }
                    else
                    {
                        Logger.LogVerbose($"SendData: {command}");
                    }

                    _SerialPort.Write(data, 0, count);

                    CommsData._outgoingMessageCount++;
                    return true;
                }
                catch (Exception e)
                {
                    Logger.LogMessage(e, $"_SendData() command={command}");
                    return false;
                }
            }
        }

        private void ResetSerialComms()
        {
            try
            {
                Logger.LogError("*** COMMS Reset ***");
                Logger.LogBuffer(_rxBuffer.ToArray(), _rxBuffer.Count, "RX partial");

                _rxBuffer.Clear();

                SerialPort? port = _SerialPort;
                if (port == null || !port.IsOpen || IsClosing)
                {
                    return;
                }

                try
                {
                    port.DataReceived -= Port_DataReceived;
                }
                catch (Exception ex)
                {
                    Logger.LogMessage(ex, "ResetSerialComms() detach DataReceived");
                }

                try
                {
                    port.DiscardInBuffer();
                    Thread.Sleep(SerialResetDelayMs);
                    port.DiscardInBuffer();

                    while (port.IsOpen && port.ReadExisting().Length > 0)
                    {
                    }
                }
                catch (Exception ex)
                {
                    Logger.LogMessage(ex, "ResetSerialComms() discard input");
                }
                finally
                {
                    try
                    {
                        port.DataReceived += Port_DataReceived;
                    }
                    catch (Exception ex)
                    {
                        Logger.LogMessage(ex, "ResetSerialComms() attach DataReceived");
                    }
                }

                CommsData._commsResetCount++;
            }
            catch (Exception ex)
            {
                Logger.LogMessage(ex, "ResetSerialComms()");
            }
        }

        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            CommsData._Port_DataReceivedEventCount++;

            lock (_rxLock)
            {
                try
                {
                    SerialPort? port = _SerialPort;
                    if (port == null || !port.IsOpen || IsClosing)
                    {
                        return;
                    }

                    while (!IsClosing && port.IsOpen && port.BytesToRead > 0)
                    {
                        int rb = port.ReadByte();
                        if (rb < 0)
                        {
                            break;
                        }

                        byte input = (byte)rb;
                        DateTime now = DateTime.Now;

                        if (_rxBuffer.Count == 0)
                        {
                            if (input != RX_START_BYTE)
                            {
                                CommsData._badStartByteCount++;
                                continue;
                            }
                        }
                        else if (now > LastDataTime.AddMilliseconds(IncomingMessageTimeoutMs))
                        {
                            ResetSerialComms();
                            return;
                        }

                        LastDataTime = now;
                        _rxBuffer.Add(input);

                        if (_rxBuffer.Count >= Commands.Sizeof_sCommandHeader)
                        {
                            ushort size = (ushort)(_rxBuffer[Commands.MessageSizeIndex] | (_rxBuffer[Commands.MessageSizeIndex + 1] << 8));

                            if (size < Commands.Sizeof_sCommandHeader || size > MaxIncomingMessageSize)
                            {
                                ResetSerialComms();
                                Logger.LogError($"Bad incoming size {size}");
                                CommsData._badIncomingSizeCount++;
                                return;
                            }

                            if (_rxBuffer.Count == size)
                            {
                                byte checksum = Commands.ComputeChecksum(_rxBuffer, _rxBuffer.Count);
                                byte expectedChecksum = _rxBuffer[Commands.MessageChecksumIndex];

                                if (checksum == expectedChecksum)
                                {
                                    CommsData._incomingMessageCount++;

                                    if (IsLoggingBuffers)
                                    {
                                        Logger.LogBuffer(_rxBuffer.ToArray(), _rxBuffer.Count, $"RX {(eDiagnosticCommands)_rxBuffer[(int)Commands.MessageCommandIndex]}");
                                    }

                                    ProcessIncomingMessage(_rxBuffer);
                                }
                                else
                                {
                                    Logger.LogError($"Checksum failed! [2] = {(eDiagnosticCommands)_rxBuffer[2]} ({checksum:X2} / {expectedChecksum:X2})");
                                    CommsData._badIncomingCRCCount++;
                                }

                                _rxBuffer.Clear();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    Logger.LogMessage(ex, "Port_DataReceived()");
                }
            }
        }

        private void ProcessIncomingMessage(List<byte> data)
        {
            try
            {
                if (OnIncomingMessage != null)
                    OnIncomingMessage(new IncomingMessageEventArgs(data.ToArray()));
            }
            catch (Exception ex)
            {
                Logger.LogMessage(ex, "ProcessIncomingMessage()");
            }
        }
    }
}
