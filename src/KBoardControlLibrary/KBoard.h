#pragma once
#include "stdafx.h"

class KBoard
{

public:

	typedef function<void(KBoard*, unsigned char, bool, void*)> KBoardButtonPressCallback;
	typedef function<void(KBoard*, unsigned char, void*)> KBoardBendChangedCallback;

	KBoard();
	~KBoard();

	bool GetIsRunning() { return isRunning; }
	bool Startup(KBoardButtonPressCallback buttonPressCallback, void* buttonPressCallbackUserState, KBoardBendChangedCallback bendChangedCallback, void* bendChangedCallbackUserState);
	void Shutdown();

	bool SetKey(unsigned char keyId, unsigned char value);

private:
	KBoardButtonPressCallback buttonPressCallback;
	KBoardBendChangedCallback bendChangedCallback;
	void* buttonPressCallbackUserState;
	void* bendChangedCallbackUserState;
	
	shared_ptr<RtMidiIn> midiIn;
	shared_ptr<RtMidiOut> midiOut;
	unsigned int inputDeviceID;
	unsigned int outputDeviceID;
	bool isRunning;
	
	static void OnMidiInput(double deltaTime, vector<unsigned char> *pMessage, void *userData);
};

