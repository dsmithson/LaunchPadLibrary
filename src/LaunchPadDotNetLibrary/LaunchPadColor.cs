using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Knightware.IO.LaunchPad
{
    public class LaunchPadColor
    {
        public LaunchPadLed R { get; set; }
        public LaunchPadLed G { get; set; }

        public LaunchPadColor()
        {

        }

        public LaunchPadColor(LaunchPadLed r, LaunchPadLed g)
        {
            this.R = r;
            this.G = g;
        }

        #region Static Colors

        public static LaunchPadColor Off { get { return new LaunchPadColor(); } }

        public static LaunchPadColor LightRed { get { return new LaunchPadColor(LaunchPadLed.Low, LaunchPadLed.Off); } }
        public static LaunchPadColor Red { get { return new LaunchPadColor(LaunchPadLed.Medium, LaunchPadLed.Off); } }
        public static LaunchPadColor BrightRed { get { return new LaunchPadColor(LaunchPadLed.Bright, LaunchPadLed.Off); } }

        public static LaunchPadColor LightGreen { get { return new LaunchPadColor(LaunchPadLed.Off, LaunchPadLed.Low); } }
        public static LaunchPadColor Green { get { return new LaunchPadColor(LaunchPadLed.Off, LaunchPadLed.Medium); } }
        public static LaunchPadColor BrightGreen { get { return new LaunchPadColor(LaunchPadLed.Off, LaunchPadLed.Bright); } }

        public static LaunchPadColor LightAmber { get { return new LaunchPadColor(LaunchPadLed.Low, LaunchPadLed.Low); } }
        public static LaunchPadColor BrightAmber { get { return new LaunchPadColor(LaunchPadLed.Bright, LaunchPadLed.Bright); } }

        public static LaunchPadColor Yellow { get { return new LaunchPadColor(LaunchPadLed.Medium, LaunchPadLed.Bright); } }


        #endregion
    }
}
