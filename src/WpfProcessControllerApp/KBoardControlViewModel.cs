using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfProcessControllerApp
{
    public class KBoardControlViewModel : ViewModelBase
    {
        private readonly List<KBoardButton> topRowButtons;
        public List<KBoardButton> TopRowButtons { get { return topRowButtons; } }

        private readonly List<KBoardButton> bottomRowButtons;
        public List<KBoardButton> BottomRowButtons { get { return bottomRowButtons; } }

        public KBoardControlViewModel()
        {
            topRowButtons = FromIDs(-1, 37, 39, -1, 42, 44, 46, -1, 49, 51, -1, 54, 56, 58, -1, -1);
            bottomRowButtons = FromIDs(36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60);

            if(IsInDesignMode)
            {
                for(int i=0 ; i<topRowButtons.Count ; i++)
                {
                    if (i % 2 == 0)
                        topRowButtons[i].LEDValue = 255;
                }

                for(int i=0 ; i<bottomRowButtons.Count ; i++)
                {
                    if (i % 2 == 0)
                        bottomRowButtons[i].LEDValue = 255;
                }
            }
        }

        private List<KBoardButton> FromIDs(params int[] buttonIDs)
        {
            var response = new List<KBoardButton>();
            foreach (int buttonID in buttonIDs)
                response.Add(new KBoardButton(buttonID));

            return response;
        }

        public void SetButtonPressedInUI(int keyID, bool isPressed)
        {
            var button = GetButton(keyID);
            if (button != null)
                button.PressedInUI = isPressed;
        }

        public void SetButtonPressedOnPhysicalBoard(int keyID, bool isPressed)
        {
            var button = GetButton(keyID);
            if (button != null)
                button.PressedOnPhysicalBoard = isPressed;
        }

        private KBoardButton GetButton(int keyID)
        {
            foreach(var button in topRowButtons)
            {
                if (button.KeyID == keyID)
                    return button;
            }
            foreach(var button in bottomRowButtons)
            {
                if (button.KeyID == keyID)
                    return button;
            }
            return null;

            //return topRowButtons
            //    .Concat(bottomRowButtons)
            //    .FirstOrDefault(b => b.KeyID == keyID);
        }
    }
}
