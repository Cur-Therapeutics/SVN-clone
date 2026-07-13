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

using System;
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
        /// Status message
        /// </summary>
         
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sDIAG_Status
        {
            public sCommandHeader header;
            public byte versionMajor;
            public byte versionMinor;
            public byte versionBuild;
            public byte reserved;
            public UInt32 sysTicks;
            public UInt32 idleTicks;
            public UInt32 skippedTicks;
            public UInt32 minIdle;
            public UInt32 maxIdle;
            public UInt32 state;
            public UInt32 health;
            public UInt64 errors;
        }

        /// <summary>
        /// Create an instance of the Commands class with the indicated
        /// communications protocol.
        /// </summary>
        public static void Init(Serial? serial)
        {
            _serial = serial;
        }

        /// <summary>
        /// LCD Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public unsafe struct sLcdData
        {
            public sCommandHeader header;
            public UInt32 address;
            public UInt32 count;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
            public byte[] data;
        }

        /// <summary>
        /// Flash Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public unsafe struct sFlashData
        {
            public sCommandHeader header;
            public UInt32 address;
            public UInt32 count;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
            public byte[] data;
        }

        /// <summary>
        /// AD7124 Status
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sAD7124Status
        {
            public sCommandHeader header;
            public byte chipId;
            public byte status;
            public UInt16 control;
            public UInt32 io1;
            public UInt32 io2;
            public byte id;
            public UInt32 error;
            public UInt32 error_en;
            public UInt16 channel;
            public UInt16 config;
            public UInt32 filter;
            public UInt32 offset;
            public UInt32 gain;
        }

        /// <summary>
        /// AD7124 Read Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sAD7124ReadData
        {
            public sCommandHeader header;
            public byte chipId;
            public UInt32 counts;
            public float engValue;
            public float mLastVoltage;
            public float mFilterAvg;
        }

        /// <summary>
        /// Accel Read Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sAccelReadData
        {
            public sCommandHeader header;
            public UInt32 x;
            public UInt32 y;
            public UInt32 z;
        }

        /// <summary>
        /// RTC Read Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sRtcReadData
        {
            public sCommandHeader header;
            public UInt32 status;
            public byte hour;
            public byte min;
            public byte second;
            public byte month;
            public byte day;
            public byte year;
        }

        /// <summary>
        /// Flash Status Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sFlashStatusData
        {
            public sCommandHeader header;
            public byte statusReg1;
            public byte statusReg2;

            public byte configReg1;
            public byte configReg2;
            public byte configReg3;
            public byte configReg4;
            public byte configReg5;

            public byte manufactureId;
            public byte memInterface;
            public byte density;
            public byte idLen;
            public byte config;
            public byte family;
            public UInt64 uniqueId;
        }

        /// <summary>
        /// ADC Read Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sAdcReadData
        {
            public sCommandHeader header;
            public UInt32 counts;
            public float volts;
        }

        /// <summary>
        /// Touch Read Data
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sTouchReadData
        {
            public sCommandHeader header;
            public UInt16 xPos;
            public UInt16 yPos;
            public byte mode;
            public UInt16 xPosRaw;
            public UInt16 yPosRaw;
        }

        /// <summary>
        /// LCD and Flash ACK / Nack
        /// </summary>
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct sFlashAck
        {
            public sCommandHeader header;
            public UInt32 address;
            public UInt32 status;
        }

        /// <summary>
        /// Send a command with no payload.
        /// </summary>
        public static bool SendCommand(eDiagnosticCommands cmdId)
        {
            sCommandHeader cmd = CreateHeader(cmdId);
            byte[] message = SerializeMessage(cmd, ReadOnlySpan<byte>.Empty);

            return IsOpen ? _serial!.SendData(message, message.Length) : false;
        }

        /// <summary>
        /// Send a request with payload.
        /// </summary>
        public static bool SendCommand(sRequest cmd)
        {
            byte[] message = cmd.GetBytes();
            Logger.LogMessage($"Sending command: {(eDiagnosticCommands)cmd.header.command}");

            return IsOpen ? _serial!.SendData(message, message.Length) : false;
        }

        /// <summary>
        /// Create a sCommandHeader instance with the indicated 
        /// </summary>
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
