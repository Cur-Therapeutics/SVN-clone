using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CURDiags
{
    public partial class GUIForm : Form
    {
        /// <summary>
        /// Update a label text
        /// </summary>
        internal void UpdateLabel(Control l, string s)
        {
            if (l.InvokeRequired)
            {
                l.Invoke(new ThreadStart(delegate { UpdateLabel(l, s); }));
                return;
            }
            l.Text = s;
        }

        /// <summary>
        /// Update a progress bar
        /// </summary>
        internal void UpdateProgressBar(ProgressBar p, int current, int max)
        {
            if (p.InvokeRequired)
            {
                p.Invoke(new ThreadStart(delegate { UpdateProgressBar(p, current, max); }));
                return;
            }
            p.Maximum = max;
            p.Value = current;
            p.Minimum = 0;
        }

        /// <summary>
        /// Update the back color of a label, used as an indicator
        /// </summary>
        internal void UpdateLabelColor(Label l, Color c)
        {
            if (l.InvokeRequired)
            {
                l.Invoke(new ThreadStart(delegate { UpdateLabelColor(l, c); }));
                return;
            }
            l.BackColor = c;
        }

        /// <summary>
        /// Update the text of a textbox
        /// </summary>
        internal void UpdateTextBox(TextBox t, string s)
        {
            if (t.InvokeRequired)
            {
                t.Invoke(new ThreadStart(delegate { UpdateTextBox(t, s); }));
                return;
            }
            t.Text = s;
        }

    }  // end class
}  // end namespace
