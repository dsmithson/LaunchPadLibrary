#pragma once

#include "LaunchPadKeyType.h"

using namespace System;

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			public ref class LaunchPadKeyPressEventArgs : EventArgs
			{
			public:
				LaunchPadKeyPressEventArgs() { };
				LaunchPadKeyType KeyType;
				unsigned char KeyId;
				bool IsPressed;

			};

			public delegate void LaunchPadKeyPressEventHandler(Object^ sender, LaunchPadKeyPressEventArgs^ e);
		}
	}
}