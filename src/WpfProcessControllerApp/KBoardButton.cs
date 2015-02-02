using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace WpfProcessControllerApp
{
    public class KBoardButton : PropertyChangedBase
    {
        private int keyID;
        public int KeyID
        {
            get { return keyID; }
            set
            {
                if(keyID != value)
                {
                    keyID = value;
                    OnPropertyChanged();
                }
            }
        }

        private int ledValue;
        public int LEDValue
        {
            get { return ledValue; }
            set
            {
                if (ledValue != value)
                {
                    ledValue = value;
                    OnPropertyChanged();
                }
            }
        }

        private bool pressedOnPhysicalBoard;
        public bool PressedOnPhysicalBoard
        {
            get { return pressedOnPhysicalBoard; }
            set
            {
                if(pressedOnPhysicalBoard != value)
                {
                    pressedOnPhysicalBoard = value;
                    LEDValue = (pressedOnPhysicalBoard || pressedInUI ? 255 : 0);
                    OnPropertyChanged();
                }
            }
        }

        private bool pressedInUI;
        public bool PressedInUI
        {
            get { return pressedInUI; }
            set
            {
                if(pressedInUI != value)
                {
                    pressedInUI = value;
                    LEDValue = (pressedOnPhysicalBoard || pressedInUI ? 255 : 0);
                    OnPropertyChanged();
                }
            }
        }

        public KBoardButton()
        {

        }

        public KBoardButton(int keyID)
        {
            this.keyID = keyID;
        }
    }
}
