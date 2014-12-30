#pragma once

#include "LaunchPadColor.h"

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			static public ref class LaunchPadColors
			{
			public:
				static property LaunchPadColor^ Off { LaunchPadColor^ get() { return gcnew LaunchPadColor(); } }

				static property LaunchPadColor^ LightRed { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Low, LaunchPadLED::Off); } }
				static property LaunchPadColor^ Red { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Medium, LaunchPadLED::Off); } }
				static property LaunchPadColor^ BrightRed { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Bright, LaunchPadLED::Off); } }

				static property LaunchPadColor^ LightGreen { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Off, LaunchPadLED::Low); } }
				static property LaunchPadColor^ Green { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Off, LaunchPadLED::Medium); } }
				static property LaunchPadColor^ BrightGreen { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Off, LaunchPadLED::Bright); } }

				static property LaunchPadColor^ LightAmber { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Low, LaunchPadLED::Low); } }
				static property LaunchPadColor^ BrightAmber { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Bright, LaunchPadLED::Bright); } }

				static property LaunchPadColor^ Yellow { LaunchPadColor^get() { return gcnew LaunchPadColor(LaunchPadLED::Medium, LaunchPadLED::Bright); } }
			};
		}
	}
}