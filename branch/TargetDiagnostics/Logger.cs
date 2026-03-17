/********************************************************************
*
*   Logger.cs
*
*   Description: Diagnostic logger
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

using System.Diagnostics;
using System.Text;

namespace CURDiags
{
    public class LoggerEventArgs : EventArgs
    {
        public readonly string Message;

        public LoggerEventArgs(string message) { Message = message; }
    }


    internal static class Logger
    {
        /// <summary>
        /// Publish an event indicating a new message should be logged.
        /// </summary>
        public static event EventHandler<LoggerEventArgs>? LoggedMessage;

        private static void OnLoggedMessage(LoggerEventArgs ex)
        {
            LoggedMessage?.Invoke(null, ex);
        }

        private static readonly object _logLock = new object();

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
            string suffix = string.IsNullOrWhiteSpace(description) ? string.Empty : $", {e.Message}";
            _LogIt("ERROR", $"{description} {e.Message}{suffix}");
        }

        internal static void LogMessage(string description)
        {
            _LogIt("INFO", description);
        }

        internal static void LogVerbose(string description)
        {
            _LogIt("VERBOSE", description);
        }

        private static void _LogIt(string level, string message)
        {
            string line = $"{DateTime.Now:HH:mm:ss.fff} [{level}] {message}";

            lock (_logLock)
            {
                OnLoggedMessage(new LoggerEventArgs(line));
                Debug.WriteLine(line);
            }
        }
    }
}
