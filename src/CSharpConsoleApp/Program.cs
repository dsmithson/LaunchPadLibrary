using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Knightware.IO.LaunchPad;

namespace Knightware
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Starting Up...");
            LaunchPad launchPad = new LaunchPad();
            if(!launchPad.Startup())
            {
                Console.WriteLine("Failed to startup");
                return;
            }
            launchPad.KeyPressed += launchPad_KeyPressed;

            Console.WriteLine("Started.  Press any key on the launchpad, or press return to exit");
            Console.WriteLine();

            Console.ReadLine();
            Console.WriteLine("Shutting down...");
            launchPad.Shutdown();
        }

        static void launchPad_KeyPressed(object sender, LaunchPadKeyPressEventArgs e)
        {
            Console.WriteLine("Type: {0}\tKey ID: {1}\t{2}", e.KeyType, e.KeyId, e.IsPressed ? "Pressed" : "Released");
            LaunchPad launchPad = (LaunchPad)sender;
            if (e.IsPressed)
                launchPad.SetKeyColor(e.KeyType, e.KeyId, LaunchPadColor.Yellow);
            else
                launchPad.ClearKeyColor(e.KeyType, e.KeyId);
        }
    }
}
