#include "stdafx.h"
#include "LaunchPad.h"

LaunchPad::LaunchPad()
{	
	midiIn = nullptr;
	midiOut = nullptr;
}

LaunchPad::~LaunchPad()
{
	Shutdown();
}

bool LaunchPad::Startup(LaunchPadButtonPressCallback buttonPressCallback, void* buttonPressCallbackUserState)
{
	Shutdown();
	isRunning = true;

	this->buttonPressCallback = buttonPressCallback;
	this->buttonPressCallbackUserState = buttonPressCallbackUserState;

	try
	{
		inputDeviceID = -1;
		midiIn = make_shared<RtMidiIn>();
		int inPortCount = midiIn->getPortCount();
		for (int i = 0; i < inPortCount; i++)
		{
			string portName = midiIn->getPortName(i);
			if (portName.find("Launchpad") != string::npos)
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
			if (portName.find("Launchpad") != string::npos)
			{
				outputPortName = portName;
				outputDeviceID = i;
				break;
			}
		}
				
		if (inputDeviceID == -1 || outputDeviceID == -1)
		{
			//TODO:  throw an exception with an appropriate error message
			cout << "Failed to find a launchpad device to connect to.  Shutting down." << endl;
			Shutdown();
			return false;
		}

		//Now let's open our MIDI ports
		midiIn->openPort(inputDeviceID);
		midiIn->ignoreTypes(false, false, false);
		midiIn->setCallback(LaunchPad::OnMidiInput, this);
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

void LaunchPad::Shutdown()
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
	this->buttonPressCallbackUserState = nullptr;
}

//Callback handler for when a LaunchPad button is pressed
void LaunchPad::OnMidiInput(double deltaTime, vector<unsigned char> *pMessage, void *userData)
{
	if (pMessage != nullptr && pMessage->size() == 3 && (pMessage->at(0) == 144 || pMessage->at(0) == 176))
	{
		auto keyType = static_cast<LaunchPadKeyType>(pMessage->at(0));
		auto keyId = pMessage->at(1);
		bool isPressed = pMessage->at(2) == 0 ? false : true;
		auto *sender = static_cast<LaunchPad*>(userData);
		if (sender->buttonPressCallback != nullptr)
			sender->buttonPressCallback(sender, keyType, keyId, isPressed, sender->buttonPressCallbackUserState);
	}
}

bool LaunchPad::SetKeyColor(LaunchPadKeyType keyType, unsigned char keyId, LaunchPadLED red, LaunchPadLED green)
{
	if (!isRunning || midiOut == nullptr)
		return false;

	unsigned char velocity = 0x00;
	velocity |= (static_cast<unsigned char>(red) & 0x03);
	velocity |= ((static_cast<unsigned char>(green)& 0x03) << 4);
	velocity |= 0x04;	//Copy to both buffers in the Launchpad

	auto msg = make_unique<vector<unsigned char>>();
	msg->push_back(static_cast<unsigned char>(keyType));
	msg->push_back(keyId);
	msg->push_back(velocity);

	midiOut->sendMessage(msg.get());
	return true;
}

bool LaunchPad::SetKeyColors(vector < tuple<LaunchPadKeyType, unsigned char, LaunchPadLED, LaunchPadLED>>& colors)
{
	//TODO:  Look into using double-buffering and setting multiple keys simultaneously on the LaunchPad
	bool success = true;
	for (auto entry : colors)
	{
		if (!SetKeyColor(get<0>(entry), get<1>(entry), get<2>(entry), get<3>(entry)))
			success = false;
	}
	return success;
}


