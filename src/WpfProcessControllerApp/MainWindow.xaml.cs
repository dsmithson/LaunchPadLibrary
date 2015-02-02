using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Knightware.IO.Devices;

namespace WpfProcessControllerApp
{
    public partial class MainWindow : Window
    {
        private KBoardDevice kBoard;
        private List<ButtonFunction> buttonFunctions;
        private readonly string configFile;

        public MainWindow()
        {
            InitializeComponent();

            //TODO:  Load from file
            buttonFunctions = new List<ButtonFunction>();

            kBoard = new KBoardDevice();
            if(!kBoard.Startup(OnKeyPressed, OnBendChanged))
            {
                MessageBox.Show(this, "Failed to initialize kBoard (maybe it's not plugged in?)", "Unable to Init Hardware", MessageBoxButton.OK, MessageBoxImage.Warning);
                kBoard.Shutdown();
                kBoard = null;
            }
        }

        private void OnKeyPressed(object sender, KBoardKeyPressEventArgs e)
        {
            kBoardControl.SetKeyPressed(e.KeyId, e.IsPressed);
            WriteLog("Physical Key {0} {1}", e.KeyId, (e.IsPressed ? "Pressed" : "Released"));

            if (e.IsPressed)
                ProcessButtonFunction(e.KeyId);
        }

        private void OnBendChanged(object sender, KBoardBendChangedEventArgs e)
        {
            WriteLog("Bend Changed to {0}", e.BendValue);
        }

        private void kBoardControl_ButtonPressed(object sender, int keyID, bool isPressed)
        {
            WriteLog("Logical Key {0} {1}", keyID, (isPressed ? "Pressed" : "Released"));

            if (isPressed)
                ProcessButtonFunction(keyID);
        }

        private void btnClearLogs_Clicked(object sender, RoutedEventArgs e)
        {
            logMessages.Items.Clear();
        }

        private void window_closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(kBoard != null)
            {
                kBoard.Shutdown();
                kBoard = null;
            }
        }

        private void WriteLog(string message, params object[] args)
        {
            //Process args (if any)
            if (args != null && args.Length > 0)
                message = string.Format(message, args);

            //Add time string
            message = string.Format("{0}\t{1}", DateTime.Now, message);

            Dispatcher.BeginInvoke((Action)(() =>
                {
                    logMessages.Items.Insert(0, message);

                    //Only allow 100 messages
                    while (logMessages.Items.Count > 100)
                        logMessages.Items.RemoveAt(logMessages.Items.Count - 1);
                }));
        }

        private void ProcessButtonFunction(int keyID)
        {
                Dispatcher.BeginInvoke((Action)(() =>
                {
                    ButtonFunction function = buttonFunctions.FirstOrDefault(b => b.KeyID == keyID);

                    if (rbConfigMode.IsChecked.GetValueOrDefault())
                    {
                        //In config mode - load options grid from button state
                        if(function == null)
                        {
                            function = new ButtonFunction() { KeyID = keyID };
                            buttonFunctions.Add(function);
                        }
                        configGrid.DataContext = function;
                    }
                    else
                    {
                        //Process key action here
                        if (function == null || string.IsNullOrEmpty(function.ProgramName))
                            return;

                        if (!function.StartNewInstanceIfAlreadyRunning)
                        {
                            //TODO:  Process check for function already running
                        }

                        //Fire off a new process
                        Task.Run(() =>
                            {
                                try
                                {
                                    WriteLog("Running process {0}...", function.ProgramName);
                                    Process.Start(function.ProgramName, function.ProgramArguments);
                                }
                                catch (Exception ex)
                                {
                                    WriteLog("{0} starting process: {1}", ex.GetType().Name, ex.Message);
                                }
                            });
                    }
                }));
        }
    }
}
