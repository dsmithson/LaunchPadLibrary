using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Knightware.IO.Devices;
using System.Threading;

namespace Knightware
{
    class Program
    {
        static LaunchPadDevice launchPad;

        static void Main(string[] args)
        {
            Console.WriteLine("Starting Up...");
            launchPad = new LaunchPadDevice();
            if(!launchPad.Startup(launchPad_KeyPressed))
            {
                Console.WriteLine("Failed to startup");
                return;
            }
            
            Console.WriteLine("Writing Red to LaunchPad...");
            SetColorForAllMainButtons(launchPad, LaunchPadColors.Red);
            Thread.Sleep(1000);

            Console.WriteLine("Writing Green to LaunchPad...");
            SetColorForAllMainButtons(launchPad, LaunchPadColors.Green);
            Thread.Sleep(1000);

            SetColorForAllMainButtons(launchPad, LaunchPadColors.Off);

            Console.WriteLine("Started.  Press any key on the launchpad, and press return to exit");
            Console.WriteLine();

            //TEST FOR gc ISSUES
            ThreadPool.QueueUserWorkItem((state) =>
                {
                    while (true)
                    {
                        Thread.Sleep(1000);
                        GC.Collect();
                    }
                });

            Console.ReadLine();
            Console.WriteLine("Shutting down...");

            launchPad.Shutdown();
            launchPad = null;
        }

        static void SetColorForAllMainButtons(LaunchPadDevice launchPad, LaunchPadColor color)
        {
            for(int row = 0; row < 8; row++)
            {
                int rowOffset = 0x10 * row;
                for(int column = 0; column < 8 ; column++)
                {
                    int keyId = rowOffset + column;
                    launchPad.SetKeyColor(LaunchPadKeyType.MainArea, (byte)keyId, color);
                }
            }
        }

        static void launchPad_KeyPressed(object sender, LaunchPadKeyPressEventArgs e)
        {
            //Note:  sender is null - haven't figure out how to get the reference into the even caller in c++/cli land
            //var launchPad = (LaunchPadDevice)sender;

            Console.WriteLine("Type: {0}\tKey ID: 0x{1:X2} ({1} Decimal)\t{2}", e.KeyType, e.KeyId, e.IsPressed ? "Pressed" : "Released");
            
            if (e.IsPressed)
                launchPad.SetKeyColor(e.KeyType, e.KeyId, LaunchPadColors.Yellow);
            else
                launchPad.ClearKeyColor(e.KeyType, e.KeyId);
        }
    }
}
