#pragma once

#include "LaunchPadLED.h"

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			public ref class LaunchPadColor
			{
			private:
				unsigned char r;
				unsigned char g;

			public:
				property unsigned char R
				{
					unsigned char get() { return r; }
					void set(unsigned char r) { this->r = r; }
				}

				property unsigned char G
				{
					unsigned char get() { return g; }
					void set(unsigned char g) { this->g = g; }
				}

				LaunchPadColor()
				{

				}

				LaunchPadColor(LaunchPadLED r, LaunchPadLED g)
				{
					this->r = r;
					this->g = g;
				}

				LaunchPadColor(const LaunchPadColor %copyFrom)
				{
					this->r = copyFrom.r;
					this->g = copyFrom.g;
				}
			};
		}
	}
}