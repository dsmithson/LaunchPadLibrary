// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LAUNCHPADWRAPPER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LAUNCHPADWRAPPER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LAUNCHPADWRAPPER_EXPORTS
#define LAUNCHPADWRAPPER_API __declspec(dllexport)
#else
#define LAUNCHPADWRAPPER_API __declspec(dllimport)
#endif

//// This class is exported from the LaunchPadWrapper.dll
//class LAUNCHPADWRAPPER_API CLaunchPadWrapper {
//public:
//	CLaunchPadWrapper(void);
//	// TODO: add your methods here.
//};

//C-Style function pointer wrapper (key type, key id, is pressed)

extern LAUNCHPADWRAPPER_API int nLaunchPadWrapper;

extern "C" LAUNCHPADWRAPPER_API int fnLaunchPadWrapper(void);

extern "C" LAUNCHPADWRAPPER_API LaunchPad* LaunchPadStartup(void(*keyPressHandler)(LaunchPad*, unsigned char, unsigned char, bool));

extern "C" LAUNCHPADWRAPPER_API void LaunchPadShutdown(LaunchPad* launchPads);

extern "C" LAUNCHPADWRAPPER_API bool LaunchPadIsRunning(LaunchPad* launchPad);

extern "C" LAUNCHPADWRAPPER_API bool LaunchPadSetKeyColor(LaunchPad* launchPad, LaunchPadKeyType keyType, unsigned char keyId, LaunchPadLED red, LaunchPadLED green);