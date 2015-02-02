using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace WpfProcessControllerApp
{
    public class ViewModelBase : PropertyChangedBase
    {
        private static bool? isInDesignMode;
        public bool IsInDesignMode
        {
            get
            {
                if(isInDesignMode == null)
                {
                    var prop = DesignerProperties.IsInDesignModeProperty;
                    isInDesignMode = (bool)DependencyPropertyDescriptor
                        .FromProperty(prop, typeof(FrameworkElement))
                        .Metadata
                        .DefaultValue;
                }
                return isInDesignMode.Value;
            }
        }
    }
}
