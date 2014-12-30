#pragma once

#include "LaunchPadKeyPressEventArgs.h"
#include "LaunchPadColor.h"
#include "LaunchPadKeyType.h"

using namespace System::Collections::Generic;

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			public ref class LaunchPadDevice
			{
			private:
				LaunchPad *launchPad;
				LaunchPadKeyPressEventHandler^ OnKeyPressed;
				void* OnKeyPressedPointer;

			public:
				LaunchPadDevice();
				~LaunchPadDevice();

				property bool IsRunning
				{
					bool get()
					{
						if (launchPad == nullptr)
							return false;
						else
							return launchPad->GetIsRunning();
					}
				}

				bool Startup(LaunchPadKeyPressEventHandler^ onKeyPressed);
				void Shutdown();

				bool ClearKeyColor(LaunchPadKeyType keyType, unsigned char keyId);
				bool SetKeyColor(LaunchPadKeyType keyType, unsigned char keyId, LaunchPadColor^ color);

				event LaunchPadKeyPressEventHandler^ KeyPressed;
			};
		}
	}
}