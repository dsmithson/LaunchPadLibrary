using System;
using System.Collections.Generic;
using System.ComponentModel;
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

namespace WpfProcessControllerApp
{
    public delegate void KBoardButtonPressHandler(object sender, int keyID, bool isPressed);

    [DefaultEvent("ButtonPressed")]
    public partial class KBoardControl : UserControl
    {
        private readonly KBoardControlViewModel viewModel;

        public event KBoardButtonPressHandler ButtonPressed;
        protected void OnButtonPressed(int keyID, bool isPressed)
        {
            if (ButtonPressed != null)
                ButtonPressed(this, keyID, isPressed);
        }

        public KBoardControl()
        {
            InitializeComponent();

            viewModel = (KBoardControlViewModel)this.DataContext;
        }

        public void SetKeyPressed(int keyID, bool isPressed)
        {
            viewModel.SetButtonPressedOnPhysicalBoard(keyID, isPressed);
        }
        
        private void Button_MouseDown(object sender, MouseButtonEventArgs e)
        {
            var button = (KBoardButton)((Button)sender).DataContext;
            viewModel.SetButtonPressedInUI(button.KeyID, true);
            OnButtonPressed(button.KeyID, true);
        }

        private void Button_MouseUp(object sender, MouseButtonEventArgs e)
        {
            var button = (KBoardButton)((Button)sender).DataContext;
            viewModel.SetButtonPressedInUI(button.KeyID, false);
            OnButtonPressed(button.KeyID, false);
        }
    }
}
