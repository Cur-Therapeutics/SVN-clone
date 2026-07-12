/********************************************************************
*
*   Utils.cs
*
*   Description: 
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 3/16/2026 | Brian Compter     | Created.
*
********************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CURDiags
{
    internal class Utils
    {
        /// <summary>
        /// Marshal pointer to a struct
        /// </summary>
        public static void MarshalPtrToStruct<T>(byte[] data, out T structure)
        {
            try
            {
                GCHandle h = GCHandle.Alloc(data, GCHandleType.Pinned);
                structure = (T)Marshal.PtrToStructure(h.AddrOfPinnedObject(), typeof(T));
                h.Free();
            }
            catch (Exception e)
            {
                Logger.LogMessage("Exception in MarshalPtrToStruct " + e.ToString());
                structure = Activator.CreateInstance<T>();
            }
        }

    }  // end class
}  // end namespace
