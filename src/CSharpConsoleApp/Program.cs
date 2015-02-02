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
        static KBoardDevice KBoard;

        static void Main(string[] args)
        {
            Console.WriteLine("Starting Up...");
            KBoard = new KBoardDevice();
            if(!KBoard.Startup(KBoard_KeyPressed, KBoard_BendChanged))
            {
                Console.WriteLine("Failed to startup");
                return;
            }
            
            Console.WriteLine("Started.  Press any key on the KBoard, and press return to exit");
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

            KBoard.Shutdown();
            KBoard = null;
        }

        static void KBoard_KeyPressed(object sender, KBoardKeyPressEventArgs e)
        {
            //Note:  sender is null - haven't figure out how to get the reference into the even caller in c++/cli land
            //var KBoard = (KBoardDevice)sender;

            Console.WriteLine("Key ID: 0x{0:X2} ({0} Decimal)\t{1}", e.KeyId, e.IsPressed ? "Pressed" : "Released");

            if (e.IsPressed)
                KBoard.SetKey(e.KeyId, 0xff);
            else
                KBoard.SetKey(e.KeyId, 0x00);
        }

        static void KBoard_BendChanged(object sender, KBoardBendChangedEventArgs e)
        {
            Console.WriteLine("Bend changed to {0:X2} ({0} Decimal)", e.BendValue);
        }
    }
}
