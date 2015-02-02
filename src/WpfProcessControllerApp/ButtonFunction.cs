using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfProcessControllerApp
{
    [Serializable]
    public class ButtonFunction : PropertyChangedBase
    {
        private bool startNewInstanceIfAlreadyRunning;
        public bool StartNewInstanceIfAlreadyRunning
        {
            get { return startNewInstanceIfAlreadyRunning; }
            set
            {
                if (startNewInstanceIfAlreadyRunning != value)
                {
                    startNewInstanceIfAlreadyRunning = value;
                    OnPropertyChanged();
                }
            }
        }

        private int keyid;
        public int KeyID
        {
            get { return keyid; }
            set
            {
                if(keyid != value)
                {
                    keyid = value;
                    OnPropertyChanged();
                }
            }
        }

        private string programName;
        public string ProgramName
        {
            get { return programName; }
            set
            {
                if(programName != value)
                {
                    programName = value;
                    OnPropertyChanged();
                }
            }
        }

        private string programArguments;
        public string ProgramArguments
        {
            get { return programArguments; }
            set
            {
                if(programArguments != value)
                {
                    programArguments = value;
                    OnPropertyChanged();
                }
            }
        }

    }
}
