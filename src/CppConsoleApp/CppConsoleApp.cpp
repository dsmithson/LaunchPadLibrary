#include "stdafx.h"

using namespace std;

void OnButtonPressed(LaunchPad* sender, LaunchPadKeyType type, unsigned char keyId, bool isPressed)
{
	cout << (type == LaunchPadKeyType::MainArea ? "Main " : "Top ") << " button " << keyId << (isPressed ? " pressed" : " released") << endl;
	if (isPressed)
		sender->SetKeyColor(type, keyId, LaunchPadLED::Bright, LaunchPadLED::Off);
	else
		sender->SetKeyColor(type, keyId, LaunchPadLED::Off, LaunchPadLED::Off);
}

int main(int argc, char* argv[])
{
	auto launchPad = make_unique<LaunchPad>();
	if (!launchPad->Startup(LaunchPad::LaunchPadButtonPressCallback(OnButtonPressed)))
	{
		cout << "Error starting up." << endl;
		return -1;
	}

	cout << "Initialized.  Press keys on the LaunchPad to light them up" << endl;
	getchar();

	cout << "Shutting down..." << endl;
	launchPad->Shutdown();
	return 0;
}