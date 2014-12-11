// LaunchPadWrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LaunchPadWrapper.h"


//// This is an example of an exported variable
//LAUNCHPADWRAPPER_API int nLaunchPadWrapper=0;
//
//// This is an example of an exported function.
//LAUNCHPADWRAPPER_API int fnLaunchPadWrapper(void)
//{
//	return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see LaunchPadWrapper.h for the class definition
//CLaunchPadWrapper::CLaunchPadWrapper()
//{
//	return;
//}

//C-Style function pointer wrapper
void(*keyCallback)(
	LaunchPad*, //LaunchPad
	unsigned char, //Key type 
	unsigned char, //Key Id
	bool); //Is Pressed

void OnButtonPressed(LaunchPad* launchPad, LaunchPadKeyType keyType, unsigned char keyId, bool isPressed)
{
	keyCallback(launchPad, static_cast<unsigned char>(keyType), keyId, isPressed);
}

LAUNCHPADWRAPPER_API LaunchPad* LaunchPadStartup(void(*keyPressHandler)(LaunchPad*, unsigned char, unsigned char, bool))
{
	LaunchPad* response = new LaunchPad();

	if (!response->Startup(LaunchPad::LaunchPadButtonPressCallback(OnButtonPressed)))
	{
		delete response;
		return nullptr;
	}
	keyCallback = keyPressHandler;
	return response;
}

LAUNCHPADWRAPPER_API void LaunchPadShutdown(LaunchPad* launchPad)
{
	if (launchPad != nullptr)
	{
		launchPad->Shutdown();
		delete launchPad;
	}
}

LAUNCHPADWRAPPER_API bool LaunchPadIsRunning(LaunchPad* launchPad)
{
	if (launchPad == nullptr)
		return false;
	else
		return launchPad->GetIsRunning();
}

LAUNCHPADWRAPPER_API bool LaunchPadSetKeyColor(LaunchPad* launchPad, LaunchPadKeyType keyType, unsigned char keyId, LaunchPadLED red, LaunchPadLED green)
{
	if (launchPad == nullptr)
		return false;
	else
		return launchPad->SetKeyColor(keyType, keyId, red, green);
}
