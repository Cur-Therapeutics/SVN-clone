/********************************************************************
*
*   BitmapConverter.cs
*
*   Description: Image file processor
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 04/20/2026| Walter Eykel      | Created.
*
********************************************************************/

using System.Drawing.Imaging;
using System.Runtime.InteropServices;

public static class BitmapConverter
{
    /// <summary>
    /// Reads a BMP image file and writes its RGB pixel data to a binary file,
    /// correcting the upside-down storage order inherent in the BMP format.
    /// </summary>
    /// <param name="inputFilename">Path to the input .bmp file</param>
    public static void BitmapToRgbBinary(string inputFilename, List<byte> bmpData)
    {
        if (!File.Exists(inputFilename))
            throw new FileNotFoundException("Input BMP file not found.", inputFilename);

        using (Bitmap bitmap = new Bitmap(inputFilename))
        {
            int width = bitmap.Width;
            int height = bitmap.Height;

            // Lock the bitmap bits for fast direct memory access
            Rectangle rect = new Rectangle(0, 0, width, height);
            BitmapData bitmapData = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);

            try
            {
                int stride = bitmapData.Stride;        // bytes per row (may include padding)
                int rowBytes = width * 3;                // exactly 3 bytes per pixel (R, G, B)
                byte[] pixelData = new byte[stride * height];

                // Copy all raw pixel data from unmanaged memory into a managed byte array
                Marshal.Copy(bitmapData.Scan0, pixelData, 0, pixelData.Length);
                {
                    // BMP stores rows bottom-to-top, so we iterate from the last row to the first
                    // to produce a correctly oriented top-to-bottom output.
                    for (int row = 0; row < height; row++)
                    {
                        int rowStart = row * stride;

                        // Write only the meaningful RGB bytes, skipping any stride padding
                        for (int col = 0; col < width; col++)
                        {
                            int offset = rowStart + col * 3;

                            // BMP stores channels in BGR order; swap to RGB for the output
                            byte blue = pixelData[offset+2];
                            byte green = pixelData[offset + 1];
                            byte red = pixelData[offset];

                            bmpData.Add(red);
                            bmpData.Add(green);
                            bmpData.Add(blue);
                            bmpData.Add(0xFF);      // Alpha
                        }
                    }
                }
            }
            finally
            {
                bitmap.UnlockBits(bitmapData);
            }
        }
    }  // end class
}  // end namespace