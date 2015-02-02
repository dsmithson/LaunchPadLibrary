#include "stdafx.h"

using namespace std;

void OnButtonPressed(KBoard* sender, unsigned char keyId, bool isPressed, void* userState)
{
	cout << (isPressed ? ": pressed" : ": released") << endl;

	if (isPressed)
		sender->SetKey(keyId, 0xFF);
	else
		sender->SetKey(keyId, 0x00);
}

void OnBendChanged(KBoard* sender, unsigned char bendValue, void* userState)
{
	cout << "Bend Changed to 0x";
	printf("%.2X", bendValue);
	cout << endl;
}

int main(int argc, char* argv[])
{
	auto kBoard = make_shared<KBoard>();
	if (!kBoard->Startup(KBoard::KBoardButtonPressCallback(OnButtonPressed), nullptr, KBoard::KBoardBendChangedCallback(OnBendChanged), nullptr))
	{
		cout << "Error starting up." << endl;
		return -1;
	}

	cout << "Started.  Press any key on the KBoard, and press return to exit" << endl;
	getchar();

	cout << "Shutting down..." << endl;
	kBoard->Shutdown();
	return 0;
}