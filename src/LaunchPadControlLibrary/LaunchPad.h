#pragma once
#include "stdafx.h"

typedef unsigned char LaunchPadLED;
#define LaunchPadLED_Off 0
#define LaunchPadLED_Low 1
#define LaunchPadLED_Medium 2
#define LaunchPadLED_Bright 3

typedef unsigned char LaunchPadKeyType;
#define LaunchPadKeyType_MainArea 144
#define LaunchPadKeyType_TopMenu 176

class LaunchPad
{

public:

	typedef function<void(LaunchPad*, LaunchPadKeyType, unsigned char, bool, void*)> LaunchPadButtonPressCallback;

	LaunchPad();
	~LaunchPad();

	bool GetIsRunning() { return isRunning; }
	bool Startup(LaunchPadButtonPressCallback buttonPressCallback, void* buttonPressCallbackUserState);
	void Shutdown();

	bool SetKeyColor(LaunchPadKeyType, unsigned char keyId, LaunchPadLED red, LaunchPadLED green);
	bool SetKeyColors(vector < tuple<LaunchPadKeyType, unsigned char, LaunchPadLED, LaunchPadLED>> &colors);

private:
	LaunchPadButtonPressCallback buttonPressCallback;
	void* buttonPressCallbackUserState;
	
	shared_ptr<RtMidiIn> midiIn;
	shared_ptr<RtMidiOut> midiOut;
	unsigned int inputDeviceID;
	unsigned int outputDeviceID;
	bool isRunning;
	
	static void OnMidiInput(double deltaTime, vector<unsigned char> *pMessage, void *userData);
};

