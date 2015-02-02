#pragma once

#include "KBoardKeyPressEventArgs.h"
#include "KBoardBendChangedEventArgs.h"

using namespace System::Collections::Generic;

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			public ref class KBoardDevice
			{
			private:
				KBoard *kBoard;
				KBoardKeyPressEventHandler^ OnKeyPressed;
				KBoardBendChangedEventHandler^ OnBendChanged;
				void* OnKeyPressedPointer;
				void* OnBendChangedPointer;

			public:
				KBoardDevice();
				~KBoardDevice();

				property bool IsRunning
				{
					bool get()
					{
						if (kBoard == nullptr)
							return false;
						else
							return kBoard->GetIsRunning();
					}
				}

				bool Startup(KBoardKeyPressEventHandler^ onKeyPressed, KBoardBendChangedEventHandler^ onBendChanged);
				void Shutdown();

				bool SetKey(unsigned char keyId, unsigned char value);

				event KBoardKeyPressEventHandler^ KeyPressed;
			};
		}
	}
}