#pragma once
#include "stdafx.h"

enum class LaunchPadLED : unsigned char
{
	Off = 0,
	Low = 1,
	Medium = 2,
	Bright = 3
};

enum class LaunchPadKeyType : unsigned char
{
	MainArea = 144,
	TopMenu = 176
};

class LaunchPad
{

public:

	typedef function<void(LaunchPad*, LaunchPadKeyType, unsigned char, bool)> LaunchPadButtonPressCallback;

	LaunchPad();
	~LaunchPad();

	bool GetIsRunning() { return isRunning; }
	bool Startup(LaunchPadButtonPressCallback buttonPressCallback);
	void Shutdown();

	bool SetKeyColor(LaunchPadKeyType, unsigned char keyId, LaunchPadLED red, LaunchPadLED green);

private:
	LaunchPadButtonPressCallback buttonPressCallback;
	
	shared_ptr<RtMidiIn> midiIn;
	shared_ptr<RtMidiOut> midiOut;
	unsigned int inputDeviceID;
	unsigned int outputDeviceID;
	bool isRunning;
	
	static void OnMidiInput(double deltaTime, vector<unsigned char> *pMessage, void *userData);
};

