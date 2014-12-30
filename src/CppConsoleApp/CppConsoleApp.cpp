#include "stdafx.h"

using namespace std;

void OnButtonPressed(LaunchPad* sender, LaunchPadKeyType type, unsigned char keyId, bool isPressed, void* userState)
{
	cout << (type == LaunchPadKeyType_MainArea ? "Main" : "Top") << " button 0x";
	printf("%.2X", keyId);
	cout << (isPressed ? ": pressed" : ": released") << endl;

	if (isPressed)
		sender->SetKeyColor(type, keyId, LaunchPadLED_Bright, LaunchPadLED_Off);
	else
		sender->SetKeyColor(type, keyId, LaunchPadLED_Off, LaunchPadLED_Off);
}

void SetColorForAllMainButtons(shared_ptr<LaunchPad> launchPad, LaunchPadLED red, LaunchPadLED green)
{
	for (int row = 0; row < 8; row++)
	{
		unsigned char rowPrefix = (0x10 * row);
		for (unsigned char column = 0; column < 8; column++)
		{
			unsigned char keyId = rowPrefix + column;
			launchPad->SetKeyColor(LaunchPadKeyType_MainArea, keyId, red, green);
		}
	}
}

int main(int argc, char* argv[])
{
	auto launchPad = make_shared<LaunchPad>();
	if (!launchPad->Startup(LaunchPad::LaunchPadButtonPressCallback(OnButtonPressed), nullptr))
	{
		cout << "Error starting up." << endl;
		return -1;
	}

	cout << "Writing Red to LaunchPad..." << endl;
	SetColorForAllMainButtons(launchPad, LaunchPadLED_Bright, LaunchPadLED_Off);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cout << "Writing Green to LaunchPad..." << endl;
	SetColorForAllMainButtons(launchPad, LaunchPadLED_Off, LaunchPadLED_Bright);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	SetColorForAllMainButtons(launchPad, LaunchPadLED_Off, LaunchPadLED_Off);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cout << "Started.  Press any key on the launchpad, and press return to exit" << endl;
	getchar();

	cout << "Shutting down..." << endl;
	launchPad->Shutdown();
	return 0;
}