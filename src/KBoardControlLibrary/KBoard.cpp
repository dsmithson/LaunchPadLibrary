#include "stdafx.h"
#include "KBoard.h"

KBoard::KBoard()
{	
	midiIn = nullptr;
	midiOut = nullptr;
}

KBoard::~KBoard()
{
	Shutdown();
}

bool KBoard::Startup(KBoardButtonPressCallback buttonPressCallback, void* buttonPressCallbackUserState, KBoardBendChangedCallback bendChangedCallback, void* bendChangedCallbackUserState)
{
	Shutdown();
	isRunning = true;

	this->buttonPressCallback = buttonPressCallback;
	this->bendChangedCallback = bendChangedCallback;
	this->buttonPressCallbackUserState = buttonPressCallbackUserState;
	this->bendChangedCallbackUserState = bendChangedCallbackUserState;

	try
	{
		inputDeviceID = -1;
		midiIn = make_shared<RtMidiIn>();
		int inPortCount = midiIn->getPortCount();
		for (int i = 0; i < inPortCount; i++)
		{
			string portName = midiIn->getPortName(i);
			if (portName.find("K-Board") != string::npos)
			{
				inputDeviceID = i;
				break;
			}
		}

		outputDeviceID = -1;
		midiOut = make_shared<RtMidiOut>();
		int outPortCount = midiOut->getPortCount();
		string outputPortName = "";
		for (int i = 0; i < outPortCount; i++)
		{
			string portName = midiOut->getPortName(i);
			if (portName.find("K-Board") != string::npos)
			{
				outputPortName = portName;
				outputDeviceID = i;
				break;
			}
		}
				
		if (inputDeviceID == -1 || outputDeviceID == -1)
		{
			cout << "Failed to find a KBoard device to connect to.  Shutting down." << endl;
			Shutdown();
			return false;
		}

		//Now let's open our MIDI ports
		midiIn->openPort(inputDeviceID);
		midiIn->ignoreTypes(false, false, false);
		midiIn->setCallback(KBoard::OnMidiInput, this);
		midiOut->openPort(outputDeviceID, outputPortName);

		return true;
	}
	catch (RtMidiError &ex)
	{
		cout << "Startup exception occurred: " << ex.getMessage() << endl;
		Shutdown();
		return false;
	}
}

void KBoard::Shutdown()
{
	isRunning = false;
	
	if (midiIn != nullptr)
	{
		if(midiIn->isPortOpen())
			midiIn->closePort();

		this->midiIn = nullptr;
	}

	if (midiOut != nullptr)
	{
		if (midiOut->isPortOpen())
			midiOut->closePort();

		midiOut = nullptr;
	}

	this->buttonPressCallback = nullptr;
	this->bendChangedCallback = nullptr;
	this->buttonPressCallbackUserState = nullptr;
	this->bendChangedCallbackUserState = nullptr;
}

//Callback handler for when a KBoard button is pressed
void KBoard::OnMidiInput(double deltaTime, vector<unsigned char> *pMessage, void *userData)
{
	const unsigned char note_on = 0x90;
	const unsigned char note_off = 0x80;
	const unsigned char bend_change = 0xE0;

	if (pMessage != nullptr && pMessage->size() == 3)
	{
		if (pMessage->at(0) == note_on || pMessage->at(0) == note_off)
		{
			auto keyId = pMessage->at(1);
			bool isPressed = pMessage->at(0) == note_on ? true : false;
			auto *sender = static_cast<KBoard*>(userData);
			if (sender->buttonPressCallback != nullptr)
				sender->buttonPressCallback(sender, keyId, isPressed, sender->buttonPressCallbackUserState);
		}
		else if (pMessage->at(0) == bend_change)
		{
			auto bendValue = pMessage->at(2);
			auto *sender = static_cast<KBoard*>(userData);
			if (sender->bendChangedCallback != nullptr)
				sender->bendChangedCallback(sender, bendValue, sender->bendChangedCallbackUserState);
		}
	}
}

bool KBoard::SetKey(unsigned char keyId, unsigned char value)
{
	if (!isRunning || midiOut == nullptr)
		return false;

	unsigned char velocity = value;
	const unsigned char note_on = 0x90;
	const unsigned char note_off = 0x80;
	unsigned char status = (value == 0x00 ? note_off : note_on);

	auto msg = make_unique<vector<unsigned char>>();
	msg->push_back(status);
	msg->push_back(keyId);
	msg->push_back(velocity);

	midiOut->sendMessage(msg.get());
	return true;
}

