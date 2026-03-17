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

using System.Text;

namespace Utilities
{
    public sealed class CsvFile
    {
        private readonly List<List<string>> _rows = new List<List<string>>();

        public CsvFile(string filePath)
        {
            if (string.IsNullOrWhiteSpace(filePath))
            {
                throw new ArgumentException("File path cannot be null or empty.", nameof(filePath));
            }

            FilePath = filePath;

            if (File.Exists(filePath))
            {
                Load(filePath);
            }
        }

        public string FilePath { get; }

        public int RowCount => _rows.Count;

        public IReadOnlyList<IReadOnlyList<string>> Rows =>
            _rows.Select(r => (IReadOnlyList<string>)r.AsReadOnly()).ToList().AsReadOnly();

        public IReadOnlyList<string> GetRow(int rowIndex)
        {
            if (rowIndex < 0 || rowIndex >= _rows.Count)
            {
                return Array.Empty<string>();
            }

            return _rows[rowIndex].AsReadOnly();
        }

        public string GetToken(int rowIndex, int columnIndex)
        {
            if (rowIndex < 0 || rowIndex >= _rows.Count)
            {
                return string.Empty;
            }

            if (columnIndex < 0 || columnIndex >= _rows[rowIndex].Count)
            {
                return string.Empty;
            }

            return _rows[rowIndex][columnIndex] ?? string.Empty;
        }

        public void SetToken(int rowIndex, int columnIndex, string value)
        {
            if (rowIndex < 0 || rowIndex >= _rows.Count || columnIndex < 0)
            {
                return;
            }

            while (_rows[rowIndex].Count <= columnIndex)
            {
                _rows[rowIndex].Add(string.Empty);
            }

            _rows[rowIndex][columnIndex] = value ?? string.Empty;
        }

        public bool ContainsKey(string key, StringComparison comparison = StringComparison.OrdinalIgnoreCase)
        {
            return FindRowIndexByFirstToken(key, comparison) >= 0;
        }

        public string[] GetValues(string key, StringComparison comparison = StringComparison.OrdinalIgnoreCase)
        {
            int rowIndex = FindRowIndexByFirstToken(key, comparison);
            if (rowIndex < 0)
            {
                return Array.Empty<string>();
            }

            return _rows[rowIndex].Skip(1).ToArray();
        }

        public string GetValue(string key, int valueIndex = 0, StringComparison comparison = StringComparison.OrdinalIgnoreCase)
        {
            string[] values = GetValues(key, comparison);

            if (valueIndex < 0 || valueIndex >= values.Length)
            {
                return string.Empty;
            }

            return values[valueIndex] ?? string.Empty;
        }

        public void SetValues(string key, IEnumerable<string> values, StringComparison comparison = StringComparison.OrdinalIgnoreCase)
        {
            if (key == null || values == null)
            {
                return;
            }

            List<string> newRow = new List<string> { key };
            newRow.AddRange(values.Select(v => v ?? string.Empty));

            int rowIndex = FindRowIndexByFirstToken(key, comparison);
            if (rowIndex >= 0)
            {
                _rows[rowIndex] = newRow;
            }
            else
            {
                _rows.Add(newRow);
            }
        }

        public void SetValue(string key, string value, StringComparison comparison = StringComparison.OrdinalIgnoreCase)
        {
            SetValues(key, new[] { value ?? string.Empty }, comparison);
        }

        public bool RemoveByKey(string key, StringComparison comparison = StringComparison.OrdinalIgnoreCase)
        {
            int rowIndex = FindRowIndexByFirstToken(key, comparison);
            if (rowIndex < 0)
            {
                return false;
            }

            _rows.RemoveAt(rowIndex);
            return true;
        }

        public void AddRow(IEnumerable<string> tokens)
        {
            if (tokens == null)
            {
                return;
            }

            _rows.Add(tokens.Select(t => t ?? string.Empty).ToList());
        }

        public void Clear()
        {
            _rows.Clear();
        }

        public void Save()
        {
            Save(FilePath);
        }

        public void Save(string filePath)
        {
            if (string.IsNullOrWhiteSpace(filePath))
            {
                return;
            }

            using StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8);

            foreach (List<string> row in _rows)
            {
                string line = string.Join(",", row.Select(EscapeCsvField));
                writer.WriteLine(line);
            }
        }

        private void Load(string filePath)
        {
            _rows.Clear();

            foreach (string line in File.ReadLines(filePath))
            {
                _rows.Add(ParseCsvLine(line));
            }
        }

        private int FindRowIndexByFirstToken(string key, StringComparison comparison)
        {
            if (key == null)
            {
                return -1;
            }

            for (int i = 0; i < _rows.Count; i++)
            {
                if (_rows[i].Count == 0)
                {
                    continue;
                }

                if (string.Equals(_rows[i][0], key, comparison))
                {
                    return i;
                }
            }

            return -1;
        }

        private static List<string> ParseCsvLine(string line)
        {
            List<string> tokens = new List<string>();

            if (line == null)
            {
                tokens.Add(string.Empty);
                return tokens;
            }

            StringBuilder current = new StringBuilder();
            bool inQuotes = false;

            for (int i = 0; i < line.Length; i++)
            {
                char c = line[i];

                if (c == '"')
                {
                    if (inQuotes && i + 1 < line.Length && line[i + 1] == '"')
                    {
                        current.Append('"');
                        i++;
                    }
                    else
                    {
                        inQuotes = !inQuotes;
                    }
                }
                else if (c == ',' && !inQuotes)
                {
                    tokens.Add(current.ToString());
                    current.Clear();
                }
                else
                {
                    current.Append(c);
                }
            }

            tokens.Add(current.ToString());
            return tokens;
        }

        private static string EscapeCsvField(string value)
        {
            value ??= string.Empty;

            bool mustQuote =
                value.Contains(',') ||
                value.Contains('"') ||
                value.Contains('\r') ||
                value.Contains('\n');

            if (value.Contains('"'))
            {
                value = value.Replace("\"", "\"\"");
            }

            return mustQuote ? $"\"{value}\"" : value;
        }
    }
}