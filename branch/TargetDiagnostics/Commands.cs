/********************************************************************
*
*   Commands.cs
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

using System.Runtime.InteropServices;
using static CURDiags.Enums;

namespace CURDiags
{
    public sealed class Commands
    {
        public const byte START_BYTE = 0x46; // 43 Meira, 44 IPG, 45 CRYO, 46 CUR

        public static readonly ushort Sizeof_sCommandHeader = (ushort)Marshal.SizeOf<sCommandHeader>();
        public static readonly ushort MessageStartByteIndex = (ushort)sCommandHeaderIndicies.StartByte;
        public static readonly ushort MessageCommandIndex = (ushort)sCommandHeaderIndicies.Command;
        public static readonly ushort MessageSizeIndex = (ushort)sCommandHeaderIndicies.Size1;
        public static readonly ushort MessageChecksumIndex = (ushort)sCommandHeaderIndicies.Checksum;
        public static readonly ushort MessagePayloadStartIndex = Sizeof_sCommandHeader;

        private readonly Serial _serial;
        private byte _nextSeqId = 1;

        public Commands(Serial serial)
        {
            _serial = serial ?? throw new ArgumentNullException(nameof(serial));
        }

        /// <summary>
        /// Send a command with no payload.
        /// </summary>
        public bool SendCommand(eDiagnosticCommands cmdId)
        {
            sCommandHeader cmd = CreateHeader((byte)cmdId);
            byte[] message = SerializeMessage(cmd, ReadOnlySpan<byte>.Empty);
            return _serial.SendData(message, message.Length);
        }

        /// <summary>
        /// Send a request with payload.
        /// </summary>
        public bool SendCommand(sRequest cmd)
        {
            byte[] message = cmd.GetBytes();
            Logger.LogMessage($"Sending command: {(eDiagnosticCommands)cmd.header.command}");
            return _serial.SendData(message, message.Length);
        }

        internal sCommandHeader CreateHeader(byte command)
        {
            return new sCommandHeader
            {
                startByte = START_BYTE,
                seqId = _nextSeqId++,
                command = command,
                size = Sizeof_sCommandHeader,
                checksum = 0
            };
        }

        internal static byte[] SerializeMessage(sCommandHeader header, ReadOnlySpan<byte> payload)
        {
            ushort fullSize = checked((ushort)(Sizeof_sCommandHeader + payload.Length));
            byte[] sizeBytes = BitConverter.GetBytes(fullSize);
            byte[] message = new byte[fullSize];

            message[(int)sCommandHeaderIndicies.StartByte] = header.startByte;
            message[(int)sCommandHeaderIndicies.SeqId] = header.seqId;
            message[(int)sCommandHeaderIndicies.Command] = header.command;
            message[(int)sCommandHeaderIndicies.Size1] = sizeBytes[0];
            message[(int)sCommandHeaderIndicies.Size2] = sizeBytes[1];
            message[(int)sCommandHeaderIndicies.Checksum] = 0;

            for (int i = 0; i < payload.Length; i++)
            {
                message[MessagePayloadStartIndex + i] = payload[i];
            }

            message[(int)sCommandHeaderIndicies.Checksum] = ComputeChecksum(message, fullSize);
            return message;
        }

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

        public struct sRequest
        {
            private const int InitialPayloadCapacity = 64;

            public sCommandHeader header;
            private List<byte>? _data;

            public sRequest(Commands commands, eDiagnosticCommands eType)
            {
                if (commands == null)
                {
                    throw new ArgumentNullException(nameof(commands));
                }

                header = commands.CreateHeader((byte)eType);
                _data = new List<byte>(InitialPayloadCapacity);
            }

            public int PayloadLength => _data?.Count ?? 0;

            public void AddBytes(byte[] newData)
            {
                ArgumentNullException.ThrowIfNull(newData);
                EnsurePayloadList();
                _data!.AddRange(newData);
            }

            public void AddByte(byte newData)
            {
                EnsurePayloadList();
                _data!.Add(newData);
            }

            public byte[] GetBytes()
            {
                ReadOnlySpan<byte> payload = (_data ?? new List<byte>()).ToArray();
                return SerializeMessage(header, payload);
            }

            private void EnsurePayloadList()
            {
                _data ??= new List<byte>(InitialPayloadCapacity);
            }
        }
    }
}
