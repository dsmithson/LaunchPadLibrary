using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Knightware.IO.LaunchPad
{
    public delegate void LaunchPadKeyPressHandler(object sender, LaunchPadKeyPressEventArgs e);

    public class LaunchPad : IDisposable
    {
        private delegate void KeyPressHandler(IntPtr launchPad, LaunchPadKeyType keyType, byte keyId, bool isPressed);
        private IntPtr launchPad;
        private bool isDisposed;

        public event LaunchPadKeyPressHandler KeyPressed;
        protected void OnKeyPressed(LaunchPadKeyPressEventArgs e)
        {
            if (KeyPressed != null)
                KeyPressed(this, e);
        }

        public bool IsRunning
        {
            get
            {
                if (launchPad == IntPtr.Zero)
                    return false;
                else
                    return LaunchPadIsRunning(launchPad);
            }
        }

        public LaunchPad()
        {
            launchPad = IntPtr.Zero;
        }

        public bool Startup()
        {
            Shutdown();

            Delegate d = new KeyPressHandler(OnButtonPressed);
            IntPtr buttonPressCallback = Marshal.GetFunctionPointerForDelegate(d);
            launchPad = LaunchPadStartup(buttonPressCallback);
            
            return launchPad != IntPtr.Zero;
        }

        public void Shutdown()
        {
            if(launchPad != IntPtr.Zero)
            {
                LaunchPadShutdown(launchPad);
                launchPad = IntPtr.Zero;
            }
        }


        private void OnButtonPressed(IntPtr launchPad, LaunchPadKeyType keyType, byte keyId, bool isPressed)
        {
            OnKeyPressed(new LaunchPadKeyPressEventArgs()
                {
                    KeyType = keyType,
                    KeyId = keyId,
                    IsPressed = isPressed
                });
        }

        public bool ClearKeyColor(LaunchPadKeyType keyType, byte keyId)
        {
            return SetKeyColor(keyType, keyId, LaunchPadColor.Off);
        }

        public bool SetKeyColor(LaunchPadKeyType keyType, byte keyId, LaunchPadColor color)
        {
            if (!IsRunning)
                return false;

            return LaunchPadSetKeyColor(launchPad, (byte)keyType, keyId, (byte)color.R, (byte)color.G);
        }

        ~LaunchPad()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected void Dispose(bool isDisposing)
        {
            if (isDisposed)
                return;

            if(isDisposing)
            {
                //Clean up any managed stuff
            }

            //Clean up unmanaged stuff here
            if(launchPad != IntPtr.Zero)
            {
                LaunchPadShutdown(launchPad);
                launchPad = IntPtr.Zero;
            }

            isDisposed = true;
        }

        [DllImport("LaunchPadWrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr LaunchPadStartup(IntPtr keyPressHandler);

        [DllImport("LaunchPadWrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void LaunchPadShutdown(IntPtr launchPad);

        [DllImport("LaunchPadWrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool LaunchPadIsRunning(IntPtr launchPad);

        [DllImport("LaunchPadWrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool LaunchPadSetKeyColor(IntPtr launchPad, byte keyType, byte keyId, byte red, byte green);
    }
}
