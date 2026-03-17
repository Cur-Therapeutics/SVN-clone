/********************************************************************
*
*   Commands.cs
*
*   Description: Contains data structures and methods to communicate
*   with the target instrument.
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

using System.Runtime.InteropServices;
using static CURDiags.Enums;

namespace CURDiags
{
    /// <summary>
    /// Commands contains the structures that define the messages exchanged with the
    /// target instrument and variations on the SendCommand() method to send
    /// messages to the instrument. (Don't call the Serial object from elsewhere in
    /// the code)
    /// </summary>
    public sealed class Commands
    {
        public const byte START_BYTE = 0x43;

        public static readonly ushort Sizeof_sCommandHeader = (ushort)Marshal.SizeOf<sCommandHeader>();
        public static readonly ushort MessageStartByteIndex = 0;
        public static readonly ushort MessageSeqIdIndex = 1;
        public static readonly ushort MessageCommandIndex = 2;
        public static readonly ushort MessageSizeIndex = 3;
        public static readonly ushort MessageChecksumIndex = 5;
        public static readonly ushort MessagePayloadStartIndex = Sizeof_sCommandHeader;

        private static Serial? _serial { get; set; } = null;
        private static byte _nextSeqId = 1;

        public static bool IsOpen => _serial != null && _serial.IsOpen;

        /// <summary>
        /// Create an instance of the Commands class with the indicated
        /// communications protocol.
        /// </summary>
        /// <param name="serial"></param>
        public static void Init(Serial serial)
        {
            _serial = serial;
        }

        /// <summary>
        /// Send a command with no payload.
        /// </summary>
        public static bool SendCommand(eDiagnosticCommands cmdId)
        {
            sCommandHeader cmd = CreateHeader(cmdId);
            byte[] message = SerializeMessage(cmd, ReadOnlySpan<byte>.Empty);
            if (IsOpen)
                return _serial.SendData(message, message.Length);
            else
                return false;
        }

        /// <summary>
        /// Send a request with payload.
        /// </summary>
        public static bool SendCommand(sRequest cmd)
        {
            byte[] message = cmd.GetBytes();
            Logger.LogMessage($"Sending command: {(eDiagnosticCommands)cmd.header.command}");
            if (IsOpen)
                return _serial.SendData(message, message.Length);
            else
                return false;
        }

        /// <summary>
        /// Create a sCommandHeader instance with the indicated 
        /// </summary>
        /// <param name="command"></param>
        /// <returns></returns>
        internal static sCommandHeader CreateHeader(eDiagnosticCommands command)
        {
            return new sCommandHeader
            {
                startByte = START_BYTE,
                seqId = _nextSeqId++,
                command = (byte) command,
                size = Sizeof_sCommandHeader,
                checksum = 0
            };
        }

        /// <summary>
        /// Return the indicated message as a byte array after appending the indicated
        /// payload data to the sCommandHeader
        /// </summary>
        /// <param name="header"></param>
        /// <param name="payload"></param>
        /// <returns></returns>
        internal static byte[] SerializeMessage(sCommandHeader header, ReadOnlySpan<byte> payload)
        {
            ushort fullSize = checked((ushort)(Sizeof_sCommandHeader + payload.Length));
            byte[] sizeBytes = BitConverter.GetBytes(fullSize);
            byte[] message = new byte[fullSize];

            message[(int)MessageStartByteIndex] = header.startByte;
            message[(int)MessageSeqIdIndex] = header.seqId;
            message[(int)MessageCommandIndex] = header.command;
            message[(int)MessageSizeIndex] = sizeBytes[0];
            message[(int)MessageSizeIndex + 1] = sizeBytes[1];
            message[(int)MessageChecksumIndex] = 0;

            for (int i = 0; i < payload.Length; i++)
            {
                message[MessagePayloadStartIndex + i] = payload[i];
            }

            message[(int)MessageChecksumIndex] = ComputeChecksum(message, fullSize);
            return message;
        }

        /// <summary>
        /// Calculate the checksum of the indicated list of bytes, interpreted as
        /// sCommandHeader instance.
        /// </summary>
        /// <param name="data"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        internal static byte ComputeChecksum(IReadOnlyList<byte> data, int count)
        {
            byte checksum = 0;

            for (int i = 0; i < count; i++)
            {
                if (i == MessageChecksumIndex)
                {
                    continue;
                }

                checksum += data[i];
            }

            return checksum;
        }

        //
        /// ////////////////////////////////  Messages ////////////////////////////////////////////
        // 

        /// <summary>
        /// sCommandHeader. Header for all messages
        /// </summary>
        [Serializable, StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sCommandHeader
        {
            public byte startByte;
            public byte seqId;
            public byte command;
            public ushort size;
            public byte checksum;

            public sCommandHeader(byte inCommand)
            {
                startByte = START_BYTE;
                seqId = 0;
                command = inCommand;
                size = Sizeof_sCommandHeader;
                checksum = 0;
            }

            public byte[] GetBytes()
            {
                return SerializeMessage(this, ReadOnlySpan<byte>.Empty);
            }
        }

        /// <summary>
        /// sRequest. sCommandHeader + payload data structure.
        /// </summary>
        public struct sRequest
        {
            private const int InitialPayloadCapacity = 64;

            public sCommandHeader header;
            private List<byte>? _data;

            public int PayloadLength => _data?.Count ?? 0;

            /// <summary>
            /// Construct a sRequest for the indicated eDiagnosticCommands.
            /// </summary>
            /// <param name="eType"></param>
            /// <exception cref="ArgumentNullException"></exception>
            public sRequest(eDiagnosticCommands eType)
            {
                header = Commands.CreateHeader(eType);
                _data = new List<byte>(InitialPayloadCapacity);
            }

            /// <summary>
            /// Add the indicated byte array to the header as payload.
            /// </summary>
            /// <param name="newData"></param>
            public void AddBytes(byte[] newData)
            {
                ArgumentNullException.ThrowIfNull(newData);
                EnsurePayloadList();
                _data!.AddRange(newData);
            }

            /// <summary>
            /// Add the indicated byte to the header as payload.
            /// </summary>
            /// <param name="newData"></param>
            public void AddByte(byte newData)
            {
                EnsurePayloadList();
                _data!.Add(newData);
            }

            /// <summary>
            /// Get the bytes for the completed message. (header + payload)
            /// </summary>
            /// <returns></returns>
            public byte[] GetBytes()
            {
                ReadOnlySpan<byte> payload = (_data ?? new List<byte>()).ToArray();
                return SerializeMessage(header, payload);
            }

            /// <summary>
            /// Make sure _data is initialized.
            /// </summary>
            private void EnsurePayloadList()
            {
                _data ??= new List<byte>(InitialPayloadCapacity);
            }
        }
    }
}
