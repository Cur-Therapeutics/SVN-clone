/********************************************************************
*
*   FormResizer.cs
*
*   Description: Handle resizing of a Form.
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

namespace MeiraDiagnostics
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.Linq;
    using System.Windows.Forms;

    public class FormResizer
    {
        private readonly Control _root;
        private Size _originalFormSize;
        private readonly Dictionary<Control, Rectangle> _originalBounds = new Dictionary<Control, Rectangle>();
        private readonly Dictionary<Control, float> _originalFontSizes = new Dictionary<Control, float>();

        public FormResizer(Form form)
        {
            _root = form;
            _originalFormSize = form.ClientSize;
            CacheControlLayouts(form);
        }

        private void CacheControlLayouts(Control parent)
        {
            foreach (Control ctrl in parent.Controls)
            {
                _originalBounds[ctrl] = ctrl.Bounds;
                _originalFontSizes[ctrl] = ctrl.Font.Size;

                if (ctrl.HasChildren)
                    CacheControlLayouts(ctrl);
            }
        }

        public void ResizeControls()
        {
            if (_originalFormSize.Width == 0 || _originalFormSize.Height == 0)
                return;

            float xRatio = (float)_root.ClientSize.Width / _originalFormSize.Width;
            float yRatio = (float)_root.ClientSize.Height / _originalFormSize.Height;

            ResizeControlList(_root, xRatio, yRatio);
        }

        private void ResizeControlList(Control parent, float xRatio, float yRatio)
        {
            foreach (Control ctrl in parent.Controls)
            {
                if (_originalBounds.TryGetValue(ctrl, out var originalBounds))
                {
                    ctrl.Bounds = new Rectangle(
                        (int)(originalBounds.X * xRatio),
                        (int)(originalBounds.Y * yRatio),
                        (int)(originalBounds.Width * xRatio),
                        (int)(originalBounds.Height * yRatio)
                    );
                }

                if (_originalFontSizes.TryGetValue(ctrl, out var originalFontSize))
                {
                    float scale = (xRatio + yRatio) / 2f;
                    float newFontSize = Math.Max(6f, originalFontSize * scale);
                    ctrl.Font = new Font(ctrl.Font.FontFamily, newFontSize, ctrl.Font.Style);
                }

                if (ctrl.HasChildren)
                    ResizeControlList(ctrl, xRatio, yRatio);
            }
        }

        public static bool IsFormPartiallyOrFullyOffScreen(Form form)
        {
            if (form == null) return false;

            Rectangle formBounds = form.Bounds;

            // Get the union of all screen working areas
            Rectangle allScreensBounds = Screen.AllScreens
                .Select(screen => screen.WorkingArea)
                .Aggregate(Rectangle.Union);

            // If the form bounds are not fully contained in the total screen area
            return !allScreensBounds.Contains(formBounds);
        }
    }
}
