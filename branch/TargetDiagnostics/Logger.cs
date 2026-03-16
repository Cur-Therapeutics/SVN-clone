/********************************************************************
*
*   Logger.cs
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

using System.Diagnostics;
using System.Text;

namespace CURDiags
{
    internal static class Logger
    {
        private static readonly object _logLock = new object();

        private static void _LogIt(string level, string message)
        {
            string line = $"{DateTime.Now:HH:mm:ss.fff} [{level}] {message}";

            lock (_logLock)
            {
                Debug.WriteLine(line);
            }
        }

        internal static void LogBuffer(byte[] data, int count, string description = "")
        {
            if (data == null)
            {
                _LogIt("ERROR", $"{description} <null buffer>");
                return;
            }

            int safeCount = Math.Max(0, Math.Min(count, data.Length));
            StringBuilder sb = new StringBuilder(safeCount * 3);

            for (int i = 0; i < safeCount; i++)
            {
                if (i > 0)
                {
                    sb.Append('-');
                }

                sb.Append(data[i].ToString("X2"));
            }

            string prefix = string.IsNullOrWhiteSpace(description) ? "Buffer" : description.Trim();
            _LogIt("BUFFER", $"{prefix}: {sb}");
        }

        internal static void LogError(string message)
        {
            _LogIt("ERROR", message);
        }

        internal static void LogMessage(Exception e, string description = "")
        {
            string suffix = string.IsNullOrWhiteSpace(description) ? string.Empty : $", {description}";
            _LogIt("ERROR", $"{e.Message}{suffix}");
        }

        internal static void LogMessage(string description)
        {
            _LogIt("INFO", description);
        }

        internal static void LogVerbose(string description)
        {
            _LogIt("VERBOSE", description);
        }
    }
}
