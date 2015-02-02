#pragma once

using namespace System;

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			public ref class KBoardKeyPressEventArgs : EventArgs
			{
			public:
				KBoardKeyPressEventArgs() { };
				unsigned char KeyId;
				bool IsPressed;

			};

			public delegate void KBoardKeyPressEventHandler(Object^ sender, KBoardKeyPressEventArgs^ e);
		}
	}
}