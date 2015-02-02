#include "stdafx.h"
#include "KBoardDevice.h"

using namespace Knightware::IO::Devices;
using namespace System::Runtime::InteropServices;
namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			void kBoardKeyPressed(KBoard* sender, unsigned char keyId, bool isPressed, void* userState)
			{
				auto e = gcnew KBoardKeyPressEventArgs();
				e->IsPressed = isPressed;
				e->KeyId = keyId;

				Type^ handlerType = KBoardKeyPressEventHandler::typeid;
				auto handler = (KBoardKeyPressEventHandler^)Marshal::GetDelegateForFunctionPointer(IntPtr(userState), handlerType);
				handler(nullptr, e);
			}

			void kBoardBendChanged(KBoard* sender, unsigned char bendValue, void* userState)
			{
				auto e = gcnew KBoardBendChangedEventArgs();
				e->BendValue = bendValue;

				Type^ handlerType = KBoardBendChangedEventHandler::typeid;
				auto handler = (KBoardBendChangedEventHandler^)Marshal::GetDelegateForFunctionPointer(IntPtr(userState), handlerType);
				handler(nullptr, e);
			}

			KBoardDevice::KBoardDevice()
			{
				kBoard = new KBoard();
				OnKeyPressedPointer = nullptr;
				OnKeyPressed = nullptr;
			}

			KBoardDevice::~KBoardDevice()
			{
				Shutdown();

				if (kBoard != nullptr)
				{
					kBoard->Shutdown();
					delete kBoard;
					kBoard = nullptr;
				}
			}

			bool KBoardDevice::Startup(KBoardKeyPressEventHandler^ onKeyPressed, KBoardBendChangedEventHandler^ onBendChanged)
			{
				GC::KeepAlive(onKeyPressed);
				GC::KeepAlive(onBendChanged);
				this->OnKeyPressed = onKeyPressed;
				this->OnBendChanged = onBendChanged;
				this->OnKeyPressedPointer = (void*)Marshal::GetFunctionPointerForDelegate(OnKeyPressed);
				this->OnBendChangedPointer = (void*)Marshal::GetFunctionPointerForDelegate(OnBendChanged);

				if (!kBoard->Startup(KBoard::KBoardButtonPressCallback(kBoardKeyPressed), OnKeyPressedPointer, KBoard::KBoardBendChangedCallback(kBoardBendChanged), OnBendChangedPointer))
				{
					Shutdown();
					return false;
				}
				return true;
			}

			void KBoardDevice::Shutdown()
			{
				if (kBoard != nullptr)
				{
					kBoard->Shutdown();
				}

				this->OnKeyPressedPointer = nullptr;
				this->OnKeyPressed = nullptr;
			}

			bool KBoardDevice::SetKey(unsigned char keyId, unsigned char value)
			{
				if (!IsRunning)
					return false;

				return kBoard->SetKey(keyId, value);
			}
		}
	}
}