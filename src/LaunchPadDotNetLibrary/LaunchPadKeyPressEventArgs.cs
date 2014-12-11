using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Knightware.IO.LaunchPad
{
    public class LaunchPadKeyPressEventArgs : EventArgs
    {
        public LaunchPadKeyType KeyType { get; set; }
        public byte KeyId { get; set; }
        public bool IsPressed { get; set; }
    }
}
