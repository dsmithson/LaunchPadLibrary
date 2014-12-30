#include "stdafx.h"
#include "LaunchPadDevice.h"
#include "LaunchPadColors.h"

using namespace Knightware::IO::Devices;
using namespace System::Runtime::InteropServices;
namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			void launchPadKeyPressed(LaunchPad* sender, unsigned char keyType, unsigned char keyId, bool isPressed, void* userState)
			{
				auto e = gcnew LaunchPadKeyPressEventArgs();
				e->IsPressed = isPressed;
				e->KeyType = static_cast<LaunchPadKeyType>(static_cast<LaunchPadKeyType>(keyType));
				e->KeyId = keyId;

				Type^ handlerType = LaunchPadKeyPressEventHandler::typeid;
				auto handler = (LaunchPadKeyPressEventHandler^)Marshal::GetDelegateForFunctionPointer(IntPtr(userState), handlerType);
				handler(nullptr, e);
			}

			LaunchPadDevice::LaunchPadDevice()
			{
				launchPad = new LaunchPad();
				OnKeyPressedPointer = nullptr;
				OnKeyPressed = nullptr;
			}

			LaunchPadDevice::~LaunchPadDevice()
			{
				Shutdown();

				if (launchPad != nullptr)
				{
					launchPad->Shutdown();
					delete launchPad;
					launchPad = nullptr;
				}
			}

			bool LaunchPadDevice::Startup(LaunchPadKeyPressEventHandler^ onKeyPressed)
			{
				GC::KeepAlive(onKeyPressed);
				this->OnKeyPressed = onKeyPressed;
				this->OnKeyPressedPointer = (void*)Marshal::GetFunctionPointerForDelegate(OnKeyPressed);

				if (!launchPad->Startup(LaunchPad::LaunchPadButtonPressCallback(launchPadKeyPressed), OnKeyPressedPointer))
				{
					Shutdown();
					return false;
				}
				return true;
			}

			void LaunchPadDevice::Shutdown()
			{
				if (launchPad != nullptr)
				{
					launchPad->Shutdown();
				}

				this->OnKeyPressedPointer = nullptr;
				this->OnKeyPressed = nullptr;
			}

			bool LaunchPadDevice::ClearKeyColor(LaunchPadKeyType keyType, unsigned char keyId)
			{
				if (!IsRunning)
					return false;

				auto type = static_cast<unsigned char>(keyType);
				return launchPad->SetKeyColor(type, keyId, LaunchPadLED::Off, LaunchPadLED::Off);
			}

			bool LaunchPadDevice::SetKeyColor(LaunchPadKeyType keyType, unsigned char keyId, LaunchPadColor^ color)
			{
				if (!IsRunning)
					return false;

				auto type = static_cast<unsigned char>(keyType);
				return launchPad->SetKeyColor(type, keyId, color->R, color->G);
			}
		}
	}
}